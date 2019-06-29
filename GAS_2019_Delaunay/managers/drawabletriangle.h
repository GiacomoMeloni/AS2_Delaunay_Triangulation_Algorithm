#ifndef DRAWABLEPOLYGON2D_H
#define DRAWABLEPOLYGON2D_H

#include <cg3/viewer/interfaces/drawable_object.h>

#include "../data_structures/triangle.h"

/**
 * @brief Class for representing a drawable Triangle
 */
class DrawableTriangle : public Triangle, public cg3::DrawableObject
{

public:

    /* --- Constructors --- */

    DrawableTriangle();
    DrawableTriangle(const cg3::Point2Dd& v1,const cg3::Point2Dd& v2,const cg3::Point2Dd& v3);

    /* --- Methods --- */

    void setColor(const QColor &value);

    /* --- DrawableObject interface --- */

    void draw() const;
    cg3::Pointd sceneCenter() const;
    double sceneRadius() const;

    void drawPoints() const;
    void drawEdges() const;

private:
    QColor color; //Color of the edges
};

#endif // DRAWABLEPOLYGON2D_H
