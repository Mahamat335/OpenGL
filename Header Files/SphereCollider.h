#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include <Collider.h>

class SphereCollider : public Collider
{

public:
    float radius;
    SphereCollider(Entity *parent, glm::vec3 center, float radius);
    virtual bool CheckForCollision(SphereCollider *collision);
};

#endif
