#ifndef ENEMY_H
#define ENEMY_H

#include <glm/glm.hpp>
#include "Model.h"

class Enemy {
public:
    Enemy(glm::vec3 position, Model* model);
    void update(glm::vec3 playerPosition, float deltaTime);
    void render(Shader& shader);

private:
    glm::vec3 position;
    Model* model;
};

#endif
