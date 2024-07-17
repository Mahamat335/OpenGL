#ifndef Transform_H
#define Transform_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{

    /*SPACE INFORMATION*/
    // Local space information
public:
    glm::vec3 pos;
    glm::vec3 eulerRot;
    glm::vec3 scale;

    glm::mat4 modelMatrix;

    Transform(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
              glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f),
              glm::vec3 sc = glm::vec3(1.0f, 1.0f, 1.0f))
        : pos(position), eulerRot(rotation), scale(sc), modelMatrix(glm::mat4(1.0f))
    {
    }
};

#endif