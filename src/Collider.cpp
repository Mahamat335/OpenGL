#include <Collider.h>

Collider::Collider(Entity *parent, glm::vec3 center) //: parent(parent), center(parent->transform.pos)
{
}

void Collider::OnCollisionEnter(Collider *collision)
{
    collisions.emplace_back(collision);
}

void Collider::OnCollisionExit(Collider *collision)
{
    auto it = std::find(collisions.begin(), collisions.end(), collision);
    if (it != collisions.end())
    {
        collisions.erase(it);
    }
}