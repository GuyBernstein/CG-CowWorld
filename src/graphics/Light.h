//==============================================================================
// File: graphics/Light.h
// Purpose: Light class for scene lighting
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#ifndef LIGHT_H
#define LIGHT_H


#include "utils/Math.h"

namespace CowGL {
    class Light {
    public:
        enum class Type {
            Directional,
            Point,
            Spot
        };

        Light(Type type = Type::Directional);

        ~Light() = default;

        void setType(Type type) { m_type = type; }
        Type getType() const { return m_type; }

        void setPosition(const glm::vec4 &position) { m_position = position; }
        const glm::vec4 &getPosition() const { return m_position; }

        void setAmbient(const glm::vec4 &ambient) { m_ambient = ambient; }
        const glm::vec4 &getAmbient() const { return m_ambient; }

        void setDiffuse(const glm::vec4 &diffuse) { m_diffuse = diffuse; }
        const glm::vec4 &getDiffuse() const { return m_diffuse; }

        void setSpecular(const glm::vec4 &specular) { m_specular = specular; }
        const glm::vec4 &getSpecular() const { return m_specular; }

        void setAttenuation(float constant, float linear, float quadratic);

        void apply(int lightIndex);

    private:
        Type m_type;
        glm::vec4 m_position;
        glm::vec4 m_ambient;
        glm::vec4 m_diffuse;
        glm::vec4 m_specular;

        float m_constantAttenuation;
        float m_linearAttenuation;
        float m_quadraticAttenuation;
    };
} // namespace CowGL


#endif //LIGHT_H
