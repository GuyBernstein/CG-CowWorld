//==============================================================================
// File: graphics/Mesh.h
// Purpose: Mesh class for 3D model data
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#ifndef MESH_H
#define MESH_H

#include <vector>
#include "utils/Math.h"

namespace CowGL {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    class Mesh {
    public:
        Mesh() = default;

        ~Mesh() = default;

        void addVertex(const Vertex &vertex) { m_vertices.push_back(vertex); }
        void addIndex(unsigned int index) { m_indices.push_back(index); }

        void clear() {
            m_vertices.clear();
            m_indices.clear();
        }

        const std::vector<Vertex> &getVertices() const { return m_vertices; }
        const std::vector<unsigned int> &getIndices() const { return m_indices; }

    private:
        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
    };
} // namespace CowGL


#endif //MESH_H
