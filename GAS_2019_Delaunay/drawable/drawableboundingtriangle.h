#ifndef DRAWABLEBOUNDINGTRIANGLE_H
#define DRAWABLEBOUNDINGTRIANGLE_H

#include <cg3/utilities/color.h>
#include "cg3/viewer/interfaces/drawable_object.h"
#include "cg3/viewer/renderable_objects/2d/renderable_objects2d.h"
#include "../data_structures/triangle.h"


class DrawableBoundingTriangle : public cg3::DrawableObject, public Triangle {
    public:
        inline DrawableBoundingTriangle();
        inline DrawableBoundingTriangle(const cg3::Point2Dd &v1, const cg3::Point2Dd &v2, const cg3::Point2Dd &v3);

        void draw() const;
        inline cg3::Pointd sceneCenter() const;
        inline double sceneRadius() const;

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

inline DrawableBoundingTriangle::DrawableBoundingTriangle() {
    setEdgeColor(*new QColor(0,0,0));
    setPointColor(*new QColor(255,0,0));
    setEdgeWidth(1);
    setPointSize(2);
}

inline DrawableBoundingTriangle::DrawableBoundingTriangle(const cg3::Point2Dd &v1, const cg3::Point2Dd &v2, const cg3::Point2Dd &v3):Triangle (v1,v2,v3){
    setEdgeColor(*new QColor(0,0,0));
    setPointColor(*new QColor(255,0,0));
    setEdgeWidth(1);
    setPointSize(2);
}

inline cg3::Pointd DrawableBoundingTriangle::sceneCenter() const{
    cg3::Point2Dd center = getCenter();
    return *new cg3::Pointd (center.x(),center.y(), 0);
}

inline double DrawableBoundingTriangle::sceneRadius() const{
    return getHypotenuse()/2;
}

inline void DrawableBoundingTriangle::setEdgeColor(const QColor &c){
    this->edgeColor = c;
}

inline void DrawableBoundingTriangle::setPointColor(const QColor &c){
    this->pointColor = c;
}

inline void DrawableBoundingTriangle::setEdgeWidth(const int &w){
    this->edgeWidth = w;
}

inline void DrawableBoundingTriangle::setPointSize(const int &s){
    this->pointSize = s;
}

#endif // DRAWABLEBOUNDINGTRIANGLE_H
