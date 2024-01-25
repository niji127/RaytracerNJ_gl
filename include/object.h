#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

enum ObjectType
{
    SPHERE,
    QUAD,
    CUBE,
    PLANE
};

class Object
{
public:
    unsigned int VAO, VBO, EBO;
    unsigned int indices_count = 0;
    ObjectType object_type;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    bool has_initiated = false;

    Object(ObjectType type) : object_type(type)
    {
        if (type == SPHERE)
            sphereInit();
        else if (type == QUAD)
            quadInit();
        else if (type == CUBE)
            cubeInit();
        else if (type == PLANE)
            planeInit();
    }
    ~Object()
    {
        glDeleteVertexArrays(1, &VAO);
    }

    void sphereInit();
    void quadInit();
    void planeInit();
    void cubeInit();

    void draw();

    void drawSphere();
    void drawQuad();
    void drawCube();
    void drawPlane();
};

#endif