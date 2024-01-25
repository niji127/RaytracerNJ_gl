#include "BVH.h"
#include <algorithm>

void BVH::resize()
{
    glm::vec3 min_pos = glm::vec3(1.0e6f, 1.0e6f, 1.0e6f);
    glm::vec3 max_pos = -min_pos;
    for (auto triangle : triangle_list)
    {
        for (int i = 0; i < 3; i++)
        {
            glm::vec3 pos = triangle.point[i].position;
            min_pos.x = std::min(pos.x, min_pos.x);
            min_pos.y = std::min(pos.y, min_pos.y);
            min_pos.z = std::min(pos.z, min_pos.z);

            max_pos.x = std::max(pos.x, max_pos.x);
            max_pos.y = std::max(pos.y, max_pos.y);
            max_pos.z = std::max(pos.z, max_pos.z);
        }
    }
    pos_max = max_pos;
    pos_min = min_pos;
}

int BVH::count = 0;
void BVH::split_BVH()
{
    id = count++;
    if (triangle_list.size() <= BVH_MAX_TRI)
        return;

    // 确定划分维度
    int dim;
    int size = triangle_list.size();
    glm::vec3 dim_length = pos_max - pos_min;
    if (dim_length.x > dim_length.y && dim_length.x > dim_length.z)
        dim = 0;
    else if (dim_length.y > dim_length.z)
        dim = 1;
    else
        dim = 2;

    // 取重心坐标中位数
    std::vector<float> coord_list;
    coord_list.reserve(size);
    for (auto triangle : triangle_list)
    {
        glm::vec3 center = triangle.getCenter();
        switch (dim)
        {
        case 0:
            coord_list.push_back(center.x);
            break;
        case 1:
            coord_list.push_back(center.y);
            break;
        case 2:
            coord_list.push_back(center.z);
            break;
        }
    }

    std::sort(coord_list.begin(), coord_list.end());
    float split = coord_list[(int)(size / 2)];
    if (split == coord_list[0])
        split += 0.01;

    // 生成子块
    left = new BVH(pos_min, pos_max, this);
    right = new BVH(pos_min, pos_max, this);

    for (auto triangle : triangle_list)
    {
        glm::vec3 center = triangle.getCenter();
        switch (dim)
        {
        case 0:
            if (center.x < split)
                left->triangle_list.push_back(triangle);
            else
                right->triangle_list.push_back(triangle);
            break;
        case 1:
            if (center.y < split)
                left->triangle_list.push_back(triangle);
            else
                right->triangle_list.push_back(triangle);
            break;
        case 2:
            if (center.z < split)
                left->triangle_list.push_back(triangle);
            else
                right->triangle_list.push_back(triangle);
            break;
        }
    }

    left->resize();
    right->resize();
    clear_triangles();

    left->split_BVH();
    right->split_BVH();
}

unsigned int BVH_List::getBVHsize(BVH *root)
{
    if (root == nullptr)
        return 0;
    else
        return 1 + getBVHsize(root->left) + getBVHsize(root->right);
}

void BVH_List::buffer_build(BVH *bvh, BVH *root)
{
    if (bvh == nullptr)
        return;

    BVH_Buffer buffer;
    buffer.pos_max = bvh->pos_max;
    buffer.pos_min = bvh->pos_min;

    // miss id
    BVH *next = bvh;
    while (next->parent->right == next || next->parent->right == nullptr)
    {
        if (next->parent->right == next && next->parent == root)
            break;
        next = next->parent;
    }
    if (next->parent->right == next && next->parent == root)
        buffer.miss_id = -1;
    else
        buffer.miss_id = next->parent->right->id;

    // hit id
    if (bvh->left)
        buffer.hit_id = bvh->left->id;
    else if (bvh->right)
        buffer.hit_id = bvh->right->id;
    else
    {
        buffer.hit_id = buffer.miss_id;
        for (int i = 0; i < bvh->triangle_list.size(); i++)
            buffer.triangle_list[i] = bvh->triangle_list[i].id;
        buffer.triangle_num = bvh->triangle_list.size();
    }
    BVH_buffer.push_back(buffer);
    buffer_build(bvh->left, root);
    buffer_build(bvh->right, root);
}