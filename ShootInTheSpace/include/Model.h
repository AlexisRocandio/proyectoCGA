#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <string>
#include "Shader.h"

class Model {
public:
    Model(const std::string& path);
    void Draw(Shader& shader);
private:
    // Model data
    void loadModel(const std::string& path);
    // Render data
};

#endif
