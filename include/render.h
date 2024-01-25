#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "screen.h"
#include "material.h"
#include "triangle.h"
#include "BVH.h"

unsigned int generateTexture(Screen_Size size);
unsigned int generateTriangleBuffer(const Triangle_List &triangle_list);
unsigned int generateLightBuffer(const Triangle_List &triangle_list);
unsigned int generateMaterialBuffer(const Material_List &material_list);
unsigned int generateBVHBuffer(const BVH_List &bvh_list);

#endif