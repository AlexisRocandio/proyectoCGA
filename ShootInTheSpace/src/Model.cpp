#include "Model.h"

Model::Model(const std::string& path) {
    loadModel(path);
}

void Model::Draw(Shader& shader) {
    // Render the model
}

void Model::loadModel(const std::string& path) {
    // Load the model using Assimp or any other model loader
}
