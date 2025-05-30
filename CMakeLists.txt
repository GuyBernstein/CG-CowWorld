cmake_minimum_required(VERSION 3.30)
project(maman16)

set(CMAKE_CXX_STANDARD 14)

add_executable(maman16
        main.cpp
        Constants.h
        Button.h
        Button.cpp
        House.cpp
        House.h
        SceneObject.cpp
        SceneObject.h
        MenuBase.cpp
        MenuBase.h
        HelpMenu.cpp
        HelpMenu.h
        MenuManager.h
        CowComponent.h
        CowHead.h
        Movement.h
        CowController.h
        Movement.cpp
        ResourceManager.h
        QuadricRenderer.h
        DisplayListBuilder.h
        ResourceManager.cpp
        SceneManager.h
        WcPt3D.h
        RGBColor.h
        WcVector3D.h
)

target_link_libraries(maman16
        "-framework OpenGL"
        "-framework GLUT"
)