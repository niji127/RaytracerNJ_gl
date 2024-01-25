#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "glm/glm.hpp"
#include "material.h"
#include <string>

class Point
{
public:
    glm::vec3 position;
    float a;
    glm::vec3 normal;
    float b;
    Point(const glm::vec3 pos, const glm::vec3 norm) : position(pos), normal(norm) {}
    Point()
    {
        position = glm::vec3(0.0f);
        normal = glm::vec3(0.0f);
    }
};

class Triangle
{
public:
    Point point[3];
    glm::vec3 normal;
    Material_Type material_type;
    glm::vec3 e1;
    float id;
    glm::vec3 e2;
    float a;
    Triangle(const Point p[], Material_Type m_type)
    {
        for (int i = 0; i < 3; i++)
            point[i] = p[i];
        e1 = point[1].position - point[0].position;
        e2 = point[2].position - point[0].position;
        normal = glm::cross(e1, e2);
        normal = glm::normalize(normal);
        material_type = m_type;
    }
    Triangle()
    {
        normal = glm::vec3(0.0f);
        material_type = WHITE;
    }
    glm::vec3 getCenter();
};

class Triangle_List
{
public:
    std::vector<Triangle> triangles;
    std::vector<int> light;
    float light_area = 0.0f;
    void loadObject(const std::string &object_path, Material_Type material_type,const glm::mat4 &model=glm::mat4(1.0f));
};
#endif