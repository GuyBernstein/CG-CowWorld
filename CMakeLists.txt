cmake_minimum_required(VERSION 3.30)
project(CG-CowGL)

set(CMAKE_CXX_STANDARD 14)

add_executable(CG-CowGL
        Main.cpp
        Cow.cpp
        Cow.h
        MainScene.cpp
        Menus.cpp
        Menus.h
        RGBColor.h
        SceneObjects.h
        SceneObjects.cpp
        WcPt3D.h
        WcVector3D.h
        Button.cpp
        Button.h
)

target_link_libraries(CG-CowGL
        "-framework OpenGL"
        "-framework GLUT"
)