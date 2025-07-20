//==============================================================================
// File: graphics/Shader.h
// Purpose: Shader class (placeholder for future shader support)
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================


#ifndef SHADER_H
#define SHADER_H


#include <string>
#include "utils/Math.h"

namespace CowGL {
    // Placeholder for future shader implementation
    // Currently using fixed-function pipeline
    class Shader {
    public:
        Shader() = default;

        ~Shader() = default;

        void use() {
        }

        void setMat4(const std::string &name, const glm::mat4 &mat) {
        }

        void setVec3(const std::string &name, const glm::vec3 &vec) {
        }

        void setFloat(const std::string &name, float value) {
        }
    };
} // namespace CowGL


#endif //SHADER_H
