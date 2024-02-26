#include "initiate.h"
#include "screen.h"
#include "shader.h"
#include "object.h"
#include "triangle.h"
#include "render.h"
#include "BVH.h"

int main()
{
    initiate_glfw(4, 6, 4);

    Screen screen(1280,720);
    screen.createWindow();
    Camera *camera = screen.getCamera();
    GLFWwindow *window = screen.window;
    glm::vec3 position = glm::vec3(278.0f, 274.35f, -800.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
    camera->setCamera(position, up, front);

    initiate_glad();

    Compute_Shader compute_shader("../shaders", "compute.comp");
    Compute_Shader denoise_shader("../shaders", "denoise.comp");
    Compute_Shader copy_shader("../shaders", "copy.comp");
    Shader display_shader("../shaders", "quad.vert", "display.frag");

    Object quad(QUAD);
    Material_List material_list;

    // triangles
    Triangle_List triangle_list;

    triangle_list.loadObject("../model/light.obj", LIGHT);
    triangle_list.loadObject("../model/wall.obj", MIRROR);
    triangle_list.loadObject("../model/left.obj", BLUE);
    triangle_list.loadObject("../model/right.obj", ORANGE);
    // triangle_list.loadObject("../model/tallbox.obj", GOLD);
    // triangle_list.loadObject("../model/shortbox.obj", GOLD);
    triangle_list.loadObject("../model/floor.obj", WHITE);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(80.0f, -10.0f, 279.6f));
    model = glm::scale(model, glm::vec3(900.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    triangle_list.loadObject("../model/bunny.obj", BROWN, model);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(250.0f, -10.0f, 279.6f));
    model = glm::scale(model, glm::vec3(900.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    triangle_list.loadObject("../model/bunny.obj", GREEN, model);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(420.0f, -10.0f, 279.6f));
    model = glm::scale(model, glm::vec3(900.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    triangle_list.loadObject("../model/bunny.obj", GOLD, model);

    // textures
    unsigned int output = generateTexture(screen.size);
    unsigned int color_temp = generateTexture(screen.size);
    unsigned int normal_temp = generateTexture(screen.size);
    unsigned int position_temp = generateTexture(screen.size);
    unsigned int previous_color = generateTexture(screen.size);
    unsigned int previous_position = generateTexture(screen.size);
    unsigned int previous_normal = generateTexture(screen.size);

    // BVH
    BVH *bvh_root = new BVH(triangle_list.triangles);
    bvh_root->split_BVH();
    BVH_List bvh_list = BVH_List(bvh_root);

    // data buffer
    unsigned int triangle_buffer = generateTriangleBuffer(triangle_list);
    unsigned int light_buffer = generateLightBuffer(triangle_list);
    unsigned int material_buffer = generateMaterialBuffer(material_list);
    unsigned int BVH_buffer = generateBVHBuffer(bvh_list);

    compute_shader.use();
    glBindImageTexture(0, output, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
    glBindImageTexture(1, normal_temp, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
    glBindImageTexture(2, position_temp, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

    int N = 10000;
    srand(time(NULL));
    unsigned int seed = rand();
    compute_shader.setUint("time_seed", seed);

    glm::uvec2 screen_size = glm::uvec2(screen.size.width, screen.size.height);
    compute_shader.setUint2("dims", screen_size);

    glm::mat4 view = camera->GetViewMatrix();
    compute_shader.setVec3("camera_position", camera->Position);
    compute_shader.setMat4("view", view);
    compute_shader.setFloat("FOV", glm::radians(camera->zoom));

    glDispatchCompute(screen.size.width / 16 + 1, screen.size.height / 16 + 1, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    float znear = 1.0f;
    float zfar = 10000.0f;
    glm::mat4 projection = glm::perspective(glm::radians(camera->zoom), screen.aspect_ratio, znear, zfar);
    glm::mat4 transform = projection * view;

    while (!glfwWindowShouldClose(window))
    {
        transform = projection * view; // last frame
        view = camera->GetViewMatrix();
        projection = glm::perspective(glm::radians(camera->zoom), screen.aspect_ratio, znear, zfar);
        seed = rand();
        compute_shader.use();
        compute_shader.setUint("time_seed", seed);
        glBindImageTexture(0, color_temp, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glBindImageTexture(1, normal_temp, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glBindImageTexture(2, position_temp, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        compute_shader.setVec3("camera_position", camera->Position);
        compute_shader.setMat4("view", glm::transpose(view));
        compute_shader.setFloat("FOV", glm::radians(camera->zoom));
        glDispatchCompute(screen.size.width / 16 + 1, screen.size.height / 16 + 1, 1);
        glMemoryBarrier(GL_ALL_BARRIER_BITS);

        denoise_shader.use();
        glBindImageTexture(0, color_temp, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glBindImageTexture(1, normal_temp, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glBindImageTexture(2, position_temp, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glBindImageTexture(3, previous_color, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glBindImageTexture(4, previous_position, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glBindImageTexture(5, previous_normal, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glBindImageTexture(6, output, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

        denoise_shader.setMat4("transform", transform);
        denoise_shader.setUint("iter", screen.camera.moving_frames);
        denoise_shader.setBool("camera_move", screen.camera.camera_move);
        glDispatchCompute(screen.size.width / 16 + 1, screen.size.height / 16 + 1, 1);
        glMemoryBarrier(GL_ALL_BARRIER_BITS);

        copy_shader.use();
        glBindImageTexture(0, output, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glBindImageTexture(1, previous_color, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glDispatchCompute(screen.size.width / 16 + 1, screen.size.height / 16 + 1, 1);
        glMemoryBarrier(GL_ALL_BARRIER_BITS);

        copy_shader.use();
        glBindImageTexture(0, position_temp, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glBindImageTexture(1, previous_position, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glDispatchCompute(screen.size.width / 16 + 1, screen.size.height / 16 + 1, 1);
        glMemoryBarrier(GL_ALL_BARRIER_BITS);

        copy_shader.use();
        glBindImageTexture(0, normal_temp, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glBindImageTexture(1, previous_normal, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
        glDispatchCompute(screen.size.width / 16 + 1, screen.size.height / 16 + 1, 1);
        glMemoryBarrier(GL_ALL_BARRIER_BITS);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        display_shader.use();
        glViewport(0, 0, screen.size.width, screen.size.height);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, output);
        quad.draw();

        screen.processInput();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
