#include "render.h"
#include "BVH.h"
#include <fstream>
#include <iostream>

unsigned int generateTexture(Screen_Size size)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, size.width, size.height);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return texture;
}
unsigned int generateTriangleBuffer(const Triangle_List &triangle_list)
{
    unsigned int triangle_buffer;
    int triangle_size = triangle_list.triangles.size();
    glGenBuffers(1, &triangle_buffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, triangle_buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, triangle_size * sizeof(Triangle) + sizeof(glm::vec4), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(int), &triangle_size);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec4), triangle_size * sizeof(Triangle), triangle_list.triangles.data());
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
    return triangle_buffer;
}
unsigned int generateLightBuffer(const Triangle_List &triangle_list)
{
    unsigned int light_buffer;
    int light_size = triangle_list.light.size();
    glGenBuffers(1, &light_buffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, light_buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, light_size * sizeof(int) + sizeof(int) + sizeof(float), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(int), &light_size);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(int), sizeof(float), &(triangle_list.light_area));
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(int) + sizeof(float), light_size * sizeof(int), triangle_list.light.data());
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
    return light_buffer;
}
unsigned int generateMaterialBuffer(const Material_List &material_list)
{
    unsigned int material_buffer;
    int material_size = material_list.materials.size();
    glGenBuffers(1, &material_buffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, material_buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, material_size * sizeof(Material) + sizeof(glm::vec4), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(int), &material_size);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec4), material_size * sizeof(Material), material_list.materials.data());
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
    return material_buffer;
}
unsigned int generateBVHBuffer(const BVH_List &bvh_list)
{
    unsigned int bvh_buffer;
    int bvh_size = bvh_list.BVH_buffer.size();
    glGenBuffers(1, &bvh_buffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, bvh_buffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, bvh_size * sizeof(BVH_Buffer), bvh_list.BVH_buffer.data(), GL_STATIC_DRAW);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
    return bvh_buffer;
}
