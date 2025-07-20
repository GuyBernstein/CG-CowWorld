//==============================================================================
// File: graphics/Light.cpp
// Purpose: Light implementation
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#include "graphics/Light.h"
#include <OpenGL/gl.h>

namespace CowGL {
    Light::Light(Type type)
        : m_type(type)
          , m_position(0.0f, 0.0f, 1.0f, 0.0f) // Default directional light from above
          , m_ambient(0.2f, 0.2f, 0.2f, 1.0f)
          , m_diffuse(1.0f, 1.0f, 1.0f, 1.0f)
          , m_specular(1.0f, 1.0f, 1.0f, 1.0f)
          , m_constantAttenuation(1.0f)
          , m_linearAttenuation(0.0f)
          , m_quadraticAttenuation(0.0f) {
    }

    void Light::setAttenuation(float constant, float linear, float quadratic) {
        m_constantAttenuation = constant;
        m_linearAttenuation = linear;
        m_quadraticAttenuation = quadratic;
    }

    void Light::apply(int lightIndex) {
        GLenum light = GL_LIGHT0 + lightIndex;

        float position[4] = {m_position.x, m_position.y, m_position.z, m_position.w};
        float ambient[4] = {m_ambient.x, m_ambient.y, m_ambient.z, m_ambient.w};
        float diffuse[4] = {m_diffuse.x, m_diffuse.y, m_diffuse.z, m_diffuse.w};
        float specular[4] = {m_specular.x, m_specular.y, m_specular.z, m_specular.w};

        glLightfv(light, GL_POSITION, position);
        glLightfv(light, GL_AMBIENT, ambient);
        glLightfv(light, GL_DIFFUSE, diffuse);
        glLightfv(light, GL_SPECULAR, specular);

        if (m_type != Type::Directional) {
            glLightf(light, GL_CONSTANT_ATTENUATION, m_constantAttenuation);
            glLightf(light, GL_LINEAR_ATTENUATION, m_linearAttenuation);
            glLightf(light, GL_QUADRATIC_ATTENUATION, m_quadraticAttenuation);
        }

        glEnable(light);
    }
} // namespace CowGL
