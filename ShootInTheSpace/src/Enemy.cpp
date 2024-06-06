#include "Enemy.h"

Enemy::Enemy(glm::vec3 position, Model* model) : position(position), model(model) {}

void Enemy::update(glm::vec3 playerPosition, float deltaTime) {
    glm::vec3 direction = glm::normalize(playerPosition - position);
    position += direction * deltaTime * 2.0f; // Move towards player
}

void Enemy::render(Shader& shader) {
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    shader.setMat4("model", modelMatrix);
    model->Draw(shader);
}
