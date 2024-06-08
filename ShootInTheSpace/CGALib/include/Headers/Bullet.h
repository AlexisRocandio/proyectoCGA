#include <string>
#include <vector>
#include <map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// GL Includes
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Bullet {
public:
    glm::vec3 position;
    glm::vec3 initialPosition;
    glm::vec3 direction;
    float speed;
    bool active;

    AbstractModel bulletModel; // Modelo de la bala

    Bullet(const glm::vec3 &pos, const glm::vec3 &dir, float spd, const AbstractModel &model)
        : position(pos), initialPosition(pos), direction(dir), speed(spd), active(true), bulletModel(model) {}

    void update(float deltaTime) {
        if (active) {
            position += direction * speed * deltaTime;
            // Desactivar si la bala se aleja más de 100 unidades
            if (glm::length(position - initialPosition) > 100.0f) {
                active = false;
            }
        }
    }

    void render() {
        if (active) {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::translate(modelMatrix, position);
            bulletModel.render(modelMatrix);
        }
    }
};
