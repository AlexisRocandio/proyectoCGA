class Bullet {
public:
    glm::vec3 position;
    glm::vec3 initialPosition;
    glm::vec3 direction;
    float speed;
    bool active;

    Bullet(const glm::vec3 &pos, const glm::vec3 &dir, float spd)
        : position(pos), initialPosition(pos), direction(dir), speed(spd), active(true) {}

    void update(float deltaTime) {
        if (active) {
            position += direction * speed * deltaTime;
            // Desactivar si la bala se aleja más de 100 unidades
            if (glm::length(position - initialPosition) > 100.0f) {
                active = false;
            }
        }
    }
};
