#ifndef BVH_H
#define BVH_H

#include <vector>
#include <glm/glm.hpp>
#include "triangle.h"

const unsigned int BVH_MAX_TRI = 3;

class BVH
{
public:
    glm::vec3 pos_max;
    glm::vec3 pos_min;
    BVH *left;
    BVH *right;
    BVH *parent;
    int id;
    static int count;
    std::vector<Triangle> triangle_list;
    BVH(const std::vector<Triangle> &triangles)
    {
        triangle_list = triangles;
        resize();
        left = nullptr;
        right = nullptr;
    }
    BVH(const glm::vec3 &min, const glm::vec3 &max, BVH *p)
        : pos_min(min), pos_max(max), parent(p)
    {
        left = nullptr;
        right = nullptr;
        id = -1;
    }
    BVH()
    {
        pos_min = glm::vec3(0.0f);
        pos_max = glm::vec3(0.0f);
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        id = -1;
    }
    void split_BVH();
    void resize();
    void clear_triangles() { std::vector<Triangle>().swap(triangle_list); }
};

class BVH_Buffer
{
public:
    glm::vec3 pos_max;
    int triangle_num;
    glm::vec3 pos_min;
    int hit_id;
    int miss_id;
    int triangle_list[BVH_MAX_TRI];

    BVH_Buffer()
    {
        pos_max = glm::vec3(0.0f);
        pos_min = glm::vec3(0.0f);
        hit_id = -1;
        miss_id = -1;
        triangle_num = 0;
        for (int i = 0; i < BVH_MAX_TRI; i++)
            triangle_list[i] = -1;
    }
};

class BVH_List
{
public:
    std::vector<BVH_Buffer> BVH_buffer;
    BVH_List(BVH *root)
    {
        unsigned int size = getBVHsize(root);
        BVH_buffer.reserve(size);
        BVH_Buffer buffer;
        buffer.pos_max = root->pos_max;
        buffer.pos_min = root->pos_min;
        buffer.hit_id = 1;
        buffer.miss_id = -1;
        BVH_buffer.push_back(buffer);
        buffer_build(root->left, root);
        buffer_build(root->right, root);
    }
    BVH_List() {}
    unsigned int getBVHsize(BVH *root);
    void buffer_build(BVH *bvh, BVH *root);
};

#endif