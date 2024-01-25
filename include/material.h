#ifndef MATERIAL_H
#define MATERIAL_H
#include "glm/glm.hpp"

enum Material_Type
{
    LIGHT,
    WHITE,
    BLUE,
    ORANGE,
    GOLD,
    TITAN
};

class Material
{
public:
    glm::vec3 albedo;
    float metallic;
    float roughness;
    float a[3];
    Material()
    {
        albedo = glm::vec3(0.0f);
        metallic = 0.0f;
        roughness = 0.0f;
    }
    Material(const glm::vec3&color,float metal,float rough)
    :albedo(color),metallic(metal),roughness(rough){}
};

class Material_List
{
public:
    std::vector<Material> materials;
    Material_List()
    {
        glm::vec3 light;
        light.x = 8.0f * (0.747f + 0.058f) + 15.6f * (0.740f + 0.287f) + 18.4f * (0.737f + 0.642f);
        light.y = 8.0f * (0.747f + 0.258f) + 15.6f * (0.740f + 0.160f) + 18.4f * (0.737f + 0.159f);
        light.z = 8.0f * 0.747f + 15.6f * 0.740f + 18.4f * 0.737f;
        glm::vec3 white = glm::vec3(0.725f, 0.71f, 0.68f);
        glm::vec3 blue = glm::vec3(0.075f, 0.404f, 1.0f);
        glm::vec3 orange = glm::vec3(1.0f, 0.125f, 0.0f);
        glm::vec3 gold = glm::vec3(1.0f, 0.766f, 0.336f);
        glm::vec3 titan = glm::vec3(0.542f, 0.497f, 0.449f);

        materials.push_back(Material(light, 0.0f, 1.0f));
        materials.push_back(Material(white, 0.0f, 0.1f));
        materials.push_back(Material(blue, 0.0f, 1.0f));
        materials.push_back(Material(orange, 0.0f, 1.0f));
        materials.push_back(Material(gold, 1.0f, 0.3f));
        materials.push_back(Material(titan, 1.0f, 0.1f));
    }
};

#endif