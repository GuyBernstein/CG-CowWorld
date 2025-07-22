//==============================================================================
// File: utils/Math.h
// Purpose: Math utilities and GLM includes
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#ifndef MATH_H
#define MATH_H


#include <cmath>
#include <algorithm>

namespace glm {
    struct vec2 {
        float x, y;

        vec2() : x(0), y(0) {
        }

        vec2(float x, float y) : x(x), y(y) {
        }

        vec2 operator-(const vec2 &other) const { return vec2(x - other.x, y - other.y); }
    };

    struct vec3 {
        float x, y, z;

        vec3() : x(0), y(0), z(0) {
        }

        vec3(float x, float y, float z) : x(x), y(y), z(z) {
        }

        vec3(float v) : x(v), y(v), z(v) {
        }

        vec3 operator+(const vec3 &other) const { return vec3(x + other.x, y + other.y, z + other.z); }
        vec3 operator-(const vec3 &other) const { return vec3(x - other.x, y - other.y, z - other.z); }
        vec3 operator*(float scalar) const { return vec3(x * scalar, y * scalar, z * scalar); }

        float length() const { return std::sqrt(x * x + y * y + z * z); }

        vec3 normalized() const {
            float len = length();
            return len > 0 ? vec3(x / len, y / len, z / len) : vec3(0, 0, 0);
        }

        static vec3 cross(const vec3 &a, const vec3 &b) {
            return vec3(
                a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x
            );
        }
    };

    struct vec4 {
        float x, y, z, w;

        vec4() : x(0), y(0), z(0), w(1) {
        }

        vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {
        }

        vec4(const vec3 &v, float w) : x(v.x), y(v.y), z(v.z), w(w) {
        }
    };

    struct mat4 {
        float m[16];

        mat4() {
            for (int i = 0; i < 16; ++i) m[i] = 0;
            m[0] = m[5] = m[10] = m[15] = 1.0f;
        }

        static mat4 translate(const vec3 &v) {
            mat4 result;
            result.m[12] = v.x;
            result.m[13] = v.y;
            result.m[14] = v.z;
            return result;
        }

        static mat4 rotate(float angle, const vec3 &axis) {
            mat4 result;
            float c = std::cos(angle);
            float s = std::sin(angle);
            float t = 1.0f - c;
            vec3 a = axis.normalized();

            result.m[0] = t * a.x * a.x + c;
            result.m[1] = t * a.x * a.y + s * a.z;
            result.m[2] = t * a.x * a.z - s * a.y;

            result.m[4] = t * a.x * a.y - s * a.z;
            result.m[5] = t * a.y * a.y + c;
            result.m[6] = t * a.y * a.z + s * a.x;

            result.m[8] = t * a.x * a.z + s * a.y;
            result.m[9] = t * a.y * a.z - s * a.x;
            result.m[10] = t * a.z * a.z + c;

            return result;
        }

        static mat4 scale(const vec3 &s) {
            mat4 result;
            result.m[0] = s.x;
            result.m[5] = s.y;
            result.m[10] = s.z;
            return result;
        }
    };

    inline float radians(float degrees) {
        return degrees * 0.01745329251f;
    }
} // namespace glm

namespace CowGL {
    constexpr float PI = 3.14159265359f;
    constexpr float TWO_PI = 6.28318530718f;
    constexpr float HALF_PI = 1.57079632679f;

    inline float clamp(float value, float min, float max) {
        return std::max(min, std::min(max, value));
    }

    inline float lerp(float a, float b, float t) {
        return a + (b - a) * t;
    }
} // namespace CowGL

#endif //MATH_H
