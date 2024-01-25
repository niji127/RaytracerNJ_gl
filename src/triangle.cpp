// #define OBJL_CONSOLE_OUTPUT
#include "OBJ_Loader.h"
#include "triangle.h"

void Triangle_List::loadObject(const std::string &object_path, Material_Type material_type,const glm::mat4& model)
{
    objl::Loader loader;
    loader.LoadFile(object_path);
    assert(loader.LoadedMeshes.size() == 1);
    objl::Mesh mesh = loader.LoadedMeshes[0];

    for (int i = 0; i < mesh.Vertices.size(); i += 3)
    {
        Point point[3];
        for (int j = 0; j < 3; j++)
        {
            point[j].position = glm::vec3(mesh.Vertices[i + j].Position.X,
                                          mesh.Vertices[i + j].Position.Y,
                                          mesh.Vertices[i + j].Position.Z);
            point[j].normal = glm::normalize(glm::vec3(mesh.Vertices[i + j].Normal.X,
                                                       mesh.Vertices[i + j].Normal.Y,
                                                       mesh.Vertices[i + j].Normal.Z));

            point[j].position = glm::vec3(model * glm::vec4(point[j].position,1.0f));
            point[j].normal = glm::vec3(glm::inverse(glm::transpose(model)) * glm::vec4(point[j].normal,1.0f));
            point[j].normal = glm::normalize(point[j].normal);
        }
        Triangle triangle = Triangle(point, material_type);
        if (triangle.material_type == LIGHT)
        {
            light.push_back(triangles.size());
            float area = 0.5f * length(cross(point[1].position - point[0].position, point[2].position - point[0].position));
            light_area += area;
        }
        triangle.id = triangles.size();
        this->triangles.push_back(triangle);
    }
}

glm::vec3 Triangle::getCenter()
{
    glm::vec3 center = glm::vec3(0.0f);
    for (int i = 0; i < 3; i++)
        center += point[i].position;
    return center / 3.0f;
}