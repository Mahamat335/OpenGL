#ifndef CUBE_COLLIDER_H
#define CUBE_COLLIDER_H

#include <Collider.h>

class CubeCollider : public Collider
{

public:
    glm::vec3 size;
    glm::vec3 halfSize;
    CubeCollider(Entity *parent, glm::vec3 center, glm::vec3 size);
    bool CheckForCollision(Collider *collision);
    bool CheckForCollision(CubeCollider *collision);
    //   bool CubeCollider::CheckForCollision(SphereCollider *collision);
};

#endif
