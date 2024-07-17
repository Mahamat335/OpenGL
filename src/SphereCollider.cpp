#include <SphereCollider.h>

SphereCollider::SphereCollider(Entity *parent, glm::vec3 center, float radius) : Collider(parent, center), radius(radius)
{
}

bool SphereCollider::CheckForCollision(SphereCollider *collision)
{
    // if (typeid(collision) == typeid(this))
    // {
    return glm::distance(center, collision->center) < radius + collision->radius;
    // }
    // else
    // {
    // return glm::distance(glm::clamp(center - collision->center, -dynamic_cast<CubeCollider *>(collision)->halfSize, dynamic_cast<CubeCollider *>(collision)->halfSize) + collision->center, center) < radius;
    //  }
}