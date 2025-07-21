cmake_minimum_required(VERSION 3.30)
project(CG-CowGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


# Include directories
include_directories(
        ${OPENGL_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIRS}
        src
)

add_executable(CG-CowGL
        src/main.cpp
        src/core/Application.cpp
        src/core/Application.h
        src/core/Window.cpp
        src/core/Window.h
        src/core/Input.cpp
        src/core/Input.h
        src/graphics/Renderer.cpp
        src/graphics/Renderer.h
        src/graphics/Mesh.cpp
        src/graphics/Mesh.h
        src/graphics/Camera.cpp
        src/graphics/Camera.h
        src/graphics/Light.cpp
        src/graphics/Light.h
        src/scene/Scene.cpp
        src/scene/Scene.h
        src/scene/GameObject.cpp
        src/scene/GameObject.h
        src/scene/Transform.cpp
        src/scene/Transform.h
        src/entities/Cow.cpp
        src/entities/Cow.h
        src/entities/Environment.cpp
        src/entities/Environment.h
        src/ui/UIManager.cpp
        src/ui/UIManager.h
        src/ui/Button.cpp
        src/ui/Button.h
        src/utils/Math.h
)

target_link_libraries(CG-CowGL
        "-framework OpenGL"
        "-framework GLUT"
)