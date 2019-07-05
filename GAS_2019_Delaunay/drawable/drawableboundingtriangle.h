#ifndef DRAWABLEBOUNDINGTRIANGLE_H
#define DRAWABLEBOUNDINGTRIANGLE_H

#include <cg3/utilities/color.h>
#include "cg3/viewer/interfaces/drawable_object.h"
#include "cg3/viewer/renderable_objects/2d/renderable_objects2d.h"
#include "../data_structures/triangle.h"

/**
 * @brief Class representing the drawable bounding triangle. This class inherit to cg3::DrawableObject and from Triangle.
 * It permit to draw the bounding triangle knowning its vertices.
 * This class contains the features of the geometric objects that will be draw.
 */
class DrawableBoundingTriangle : public cg3::DrawableObject, public Triangle {
    public:
        /* --- Constructor --- */
        inline DrawableBoundingTriangle();
        inline DrawableBoundingTriangle(const cg3::Point2Dd &v1, const cg3::Point2Dd &v2, const cg3::Point2Dd &v3);

        void draw() const;
        inline cg3::Pointd sceneCenter() const;
        inline double sceneRadius() const;

        /* --- Setter ---*/
        inline void setEdgeColor(const QColor& c);
        inline void setPointColor(const QColor& c);
        inline void setEdgeWidth(const int &w);
        inline void setPointSize(const int &s);

    protected:
        void drawEdges() const;
        void drawPoints() const;

        int pointSize;
        cg3::Color pointColor;
        int edgeWidth;
        cg3::Color edgeColor;
};

/**
 * @brief Default constructor. The attributes are setted staticaly, calling the related methods.
 */
inline DrawableBoundingTriangle::DrawableBoundingTriangle() {
    setEdgeColor(*new QColor(0,0,0));
    setPointColor(*new QColor(255,0,0));
    setEdgeWidth(4);
    setPointSize(7);
}

/**
 * @brief Constructor using the references of vertices of the triangle. The vertices of the triangle are set using the input parameters,
 * and the attributes inside the drawable class are set statically by calling the relative methods.
 * @param v1 reference of the first vertex
 * @param v2 reference of the second vertex
 * @param v3 reference of the third vertex
 */
inline DrawableBoundingTriangle::DrawableBoundingTriangle(const cg3::Point2Dd &v1, const cg3::Point2Dd &v2, const cg3::Point2Dd &v3):Triangle (v1,v2,v3){
    setEdgeColor(*new QColor(0,0,0));
    setPointColor(*new QColor(255,0,0));
    setEdgeWidth(4);
    setPointSize(7);
}

/**
 * @brief sceneCenter
 * @return
 */
inline cg3::Pointd DrawableBoundingTriangle::sceneCenter() const{
    cg3::Point2Dd center = getCenter();
    return *new cg3::Pointd (center.x(),center.y(), 0);
}

/**
 * @brief sceneRadius
 * @return
 */
inline double DrawableBoundingTriangle::sceneRadius() const{
    return getHypotenuse()/2;
}

/**
 * @brief setEdgeColor
 * @param c edge color
 */
inline void DrawableBoundingTriangle::setEdgeColor(const QColor &c){
    this->edgeColor = c;
}

/**
 * @brief setPointColor
 * @param c point color
 */
inline void DrawableBoundingTriangle::setPointColor(const QColor &c){
    this->pointColor = c;
}

/**
 * @brief setEdgeWidth
 * @param w edge width
 */
inline void DrawableBoundingTriangle::setEdgeWidth(const int &w){
    this->edgeWidth = w;
}

/**
 * @brief setPointSize
 * @param s point size
 */
inline void DrawableBoundingTriangle::setPointSize(const int &s){
    this->pointSize = s;
}

#endif // DRAWABLEBOUNDINGTRIANGLE_H
