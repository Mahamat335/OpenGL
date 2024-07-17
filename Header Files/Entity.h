#ifndef Entity_H
#define Entity_H

#include <glad/glad.h>
#include <Transform.h>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity
{

public:
    Transform transform;
    // std::vector<std::unique_ptr<Entity>> children;
    std::vector<Entity *> children;
    Transform *parent = nullptr;
    Entity *parentPtr = nullptr;
    bool isEnable = true;
    bool isStatic = false;

    Entity(Transform t = Transform()) : transform(t)
    {
    }
    ~Entity()
    {
        if (parent)
        {
            auto it = std::find(parentPtr->children.begin(), parentPtr->children.end(), this);
            if (it != parentPtr->children.end())
            {
                parentPtr->children.erase(it);
            }
            for (auto *child : children)
                delete child;
        }
    }
    void AddChild(Entity *child)
    {
        child->parent = &this->transform;
        child->parentPtr = this;
        child->UpdateTransform();
        children.emplace_back(child);
    }
    void UpdateTransform()
    {
        transform.modelMatrix = glm::translate(parent->modelMatrix, transform.pos);
        transform.modelMatrix = glm::rotate(transform.modelMatrix, glm::radians(transform.eulerRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
        transform.modelMatrix = glm::rotate(transform.modelMatrix, glm::radians(transform.eulerRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
        transform.modelMatrix = glm::rotate(transform.modelMatrix, glm::radians(transform.eulerRot.z), glm::vec3(0.0f, 0.0f, 1.0f));
        transform.modelMatrix = glm::scale(transform.modelMatrix, transform.scale);
        for (auto &child : children)
        {
            child->UpdateTransform();
        }
    }
    void DrawMesh(unsigned int modelLoc)
    {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform.modelMatrix));
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    void Move(glm::vec3 newPosition)
    {
        if (isStatic)
        {
            std::cerr << "You Can't move a static object!" << std::endl;
        }
        else
        {

            transform.pos = newPosition;
            UpdateTransform();
        }
    }
    void Rotate(glm::vec3 newRotation)
    {
        if (isStatic)
        {
            std::cerr << "You Can't rotate a static object!" << std::endl;
        }
        else
        {

            transform.eulerRot = newRotation;
            UpdateTransform();
        }
    }
    void Scale(glm::vec3 newScale)
    {
        if (isStatic)
        {
            std::cerr << "You Can't scale a static object!" << std::endl;
        }
        else
        {

            transform.scale = newScale;
            UpdateTransform();
        }
    }
    void SetAsStatic()
    {
        isStatic = true;
    }
    void SetAsDynamic()
    {
        isStatic = false;
    }
};
#endif