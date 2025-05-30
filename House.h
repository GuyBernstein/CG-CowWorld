//
// Created by Guy Bernstein on 29/05/2025.
// House object derived from SceneObject base class.

#ifndef HOUSE_H
#define HOUSE_H

#include "SceneObject.h"
#include "Constants.h"
#include "RGBColor.h"

#include "WcVector3D.h"

class House final : public SceneObject
{
public:
    explicit House(const WcPt3D& position = WcPt3D(), GLfloat rotation = 0.0f);

protected:
    void doRender() override;

private:
    void renderWalls();
    void renderDoor();
    // void renderRoof();
    // void renderWindows();
    // void renderWindow(GLfloat x, GLfloat y);

    // Material colors
    static constexpr GLfloat WALL_COLOR[] = {RGB_COLOR_CREAM, 1.0f};
    static constexpr GLfloat ROOF_COLOR[] = {RGB_COLOR_CLAY, 1.0f};
    static constexpr GLfloat DOOR_COLOR[] = {RGB_COLOR_BROWN, 1.0f};
    static constexpr GLfloat WINDOW_COLOR[] = {RGB_COLOR_LIGHT_BLUE, 1.0f};

    // Cached roof normals
    mutable bool m_roofNormalsCalculated{false};
    mutable WcVector3D m_roofNormal1;
    mutable WcVector3D m_roofNormal2;
};


#endif //HOUSE_H
