#ifndef MATERIAL_H
#define MATERIAL_H
#include "glm/glm.hpp"

enum Material_Type
{
    LIGHT,
    WHITE,
    BLUE,
    ORANGE,
    BROWN,
    GOLD,
    GREEN,
    MIRROR
};

class Material
{
public:
    glm::vec3 baseColor;
    float subsurface;

    float metallic;
    float specular;
    float specularTint;
    float roughness;

    float anistropic;
    float sheen;
    float sheenTint;
    float clearcoat;

    float clearcoatGloss;
    float offset[3];
    Material()
    {
        baseColor = glm::vec3(1.0f);
        subsurface = 0.0f;

        metallic = 0.0f;
        specular = 0.5f;
        specularTint = 0.0f;
        roughness = 0.5f;

        anistropic = 0.0f;
        sheen = 0.0f;
        sheenTint = 0.5f;
        clearcoat = 0.0f;

        clearcoatGloss = 1.0f;
    }
    Material(const glm::vec3 &color)
        : baseColor(color)
    {
        metallic = 0.0f;

        subsurface = 0.0f;
        specular = 0.5f;
        specularTint = 0.0f;
        roughness = 0.5f;

        anistropic = 0.0f;
        sheen = 0.0f;
        sheenTint = 0.5f;
        clearcoat = 0.0f;

        clearcoatGloss = 1.0f;
    }
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
        glm::vec3 brown = glm::vec3(0.196f, 0.122f, 0.125f);
        glm::vec3 gold = glm::vec3(1.0f, 0.766f, 0.336f);
        glm::vec3 green = glm::vec3(0.333f, 0.420f, 0.184f);
        glm::vec3 mirror = glm::vec3(1.0f, 1.0f, 1.0f);

        Material light_material(light);
        materials.push_back(light_material);

        Material white_material(white);
        white_material.roughness = 1.0f;
        materials.push_back(white_material);

        Material blue_material(blue);
        blue_material.roughness = 1.0f;
        materials.push_back(blue_material);

        Material orange_material(orange);
        orange_material.roughness = 1.0f;
        materials.push_back(orange_material);

        Material brown_material(brown);
        brown_material.subsurface = 1.0f;
        brown_material.specular = 0.0f;
        brown_material.roughness = 1.0f;
        brown_material.sheen = 1.0f;
        brown_material.sheenTint = 1.0f;
        materials.push_back(brown_material);

        Material gold_material(gold);
        gold_material.metallic = 1.0f;
        gold_material.specular = 1.0f;
        gold_material.roughness = 0.2f;
        gold_material.anistropic = 1.0f;
        materials.push_back(gold_material);

        Material green_material(green);
        green_material.specular = 1.0f;
        green_material.roughness = 0.3f;
        green_material.clearcoat = 1.0f;
        materials.push_back(green_material);

        Material mirror_material(mirror);
        mirror_material.metallic = 1.0f;
        mirror_material.specular = 1.0f;
        mirror_material.roughness = 0.1f;
        materials.push_back(mirror_material);
    }
};

#endif
