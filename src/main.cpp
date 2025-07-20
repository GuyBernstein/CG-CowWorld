//==============================================================================
// File: main.cpp
// Purpose: Entry point for the CowGL application
// Created by Guy Bernstein on 20/07/2025.
//==============================================================================

#include "core/Application.h"
#include <iostream>
#include <exception>

int main(int argc, char **argv) {
    try {
        CowGL::Application app(argc, argv);
        return app.run();
    } catch (const std::exception &e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
