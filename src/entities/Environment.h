//==============================================================================
// File: entities/Environment.h
// Purpose: Environment objects (house, trees, etc.)
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


#include "scene/GameObject.h"

namespace CowGL {
    namespace Environment {
        class Ground : public GameObject {
        public:
            Ground();

        protected:
            void onRender() override;
        };

        class House : public GameObject {
        public:
            House();

        protected:
            void onRender() override;
        };

        class Shed : public GameObject {
        public:
            Shed();

        protected:
            void onRender() override;
        };

        class Tree : public GameObject {
        public:
            Tree();

        protected:
            void onRender() override;
        };

        class WaterTank : public GameObject {
        public:
            WaterTank();

        protected:
            void onRender() override;
        };
    } // namespace Environment
} // namespace CowGL


#endif //ENVIRONMENT_H
