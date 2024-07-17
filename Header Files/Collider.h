#ifndef COLLIDER_H
#define COLLIDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stack>
#include <vector>
#include <Entity.h>
#include <Transform.h>
#include <glm/glm.hpp>

class Collider
{

public:
    glm::vec3 center;
    std::vector<Collider *> collisions;
    Entity *parent;
    Collider(Entity *parent, glm::vec3 center);
    virtual bool CheckForCollision(Collider *collision) = 0;
    // virtual bool CheckForCollision(SphereCollider *collision) = 0;
    void OnCollisionEnter(Collider *collision);
    void OnCollisionExit(Collider *collision);
};

#endif
