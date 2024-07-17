#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stack>
#include <Entity.h>
#include <Transform.h>
#include <glm/glm.hpp>
#include <Collider.h>

class Game
{
    struct GameData
    {
        glm::vec3 playerVel;
        float playerAngularSpeed = 0.0f;
        float playerSpeed = 5.0f;
        bool polygonMode = false;
        unsigned int modelLoc;
    };

public:
    static GameData data;
    Game();
    bool Start();
    bool Update(float deltaTime);
    void End();
    void RenderEntities(Entity root, unsigned int modelLoc);
};

#endif // GAME_H
