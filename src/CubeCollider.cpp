#include <CubeCollider.h>

CubeCollider::CubeCollider(Entity *parent, glm::vec3 center, glm::vec3 size) : Collider(parent, center), size(size)
{
    halfSize = size *= 0.5f;
}

bool CubeCollider::CheckForCollision(CubeCollider *collision)
{
    bool collisionX = center.x + halfSize.x >= collision->center.x - collision->halfSize.x && collision->center.x + collision->halfSize.x >= center.x - halfSize.x;
    bool collisionY = center.y + halfSize.y >= collision->center.y - collision->halfSize.y && collision->center.y + collision->halfSize.y >= center.y - halfSize.y;
    bool collisionZ = center.z + halfSize.z >= collision->center.z - collision->halfSize.z && collision->center.z + collision->halfSize.z >= center.z - halfSize.z;
    // std::cout << center.x << " " << halfSize.x << " " << collision->center.x << " " << collision->halfSize.x << std::endl;
    return collisionX && collisionY && collisionZ;
}
bool CubeCollider::CheckForCollision(Collider *collision)
{
    return false;
}
/* bool CubeCollider::CheckForCollision(SphereCollider *collision)
{
    return glm::distance(glm::clamp(collision->center - center, -halfSize, halfSize) + center, collision->center) < collision->radius;
} */