#ifndef DRAWABLEDELAUNEYTRIANGULATION_H
#define DRAWABLEDELAUNEYTRIANGULATION_H

#include <cg3/utilities/color.h>
#include "cg3/viewer/interfaces/drawable_object.h"
#include "cg3/viewer/renderable_objects/2d/renderable_objects2d.h"
#include "../algorithms/delauneytriangulation.h"


class DrawableDelauneyTriangulation : public cg3::DrawableObject, public DelauneyTriangulation {
    public:
        inline DrawableDelauneyTriangulation();
        inline DrawableDelauneyTriangulation(const Triangle &boundingTriangle);

        void draw() const;
        inline cg3::Pointd sceneCenter() const;
        inline double sceneRadius() const;

        inline void setEdgeColor(const QColor& c);
        inline void setPointColor(const QColor& c);
        inline void setEdgeWidth(const int &w);
        inline void setPointSize(const int &s);

    protected:
        void drawEdges(const Triangle &triangle) const;
        void drawPoints(const Triangle &triangle) const;

        int pointSize;
        cg3::Color pointColor;
        int edgeWidth;
        cg3::Color edgeColor;
};

inline DrawableDelauneyTriangulation::DrawableDelauneyTriangulation() {
    setEdgeColor(*new QColor(0,0,255));
    setPointColor(*new QColor(255,0,0));
    setEdgeWidth(1);
    setPointSize(3);
}

inline DrawableDelauneyTriangulation::DrawableDelauneyTriangulation(const Triangle &boundingTriangle):DelauneyTriangulation (boundingTriangle) {
    setEdgeColor(*new QColor(0,0,255));
    setPointColor(*new QColor(255,0,0));
    setEdgeWidth(1);
    setPointSize(3);
}

inline cg3::Pointd DrawableDelauneyTriangulation::sceneCenter() const{
    return *new cg3::Pointd (0, 0, 0);
}

inline double DrawableDelauneyTriangulation::sceneRadius() const{
    return 1e+6;
}

inline void DrawableDelauneyTriangulation::setEdgeColor(const QColor &c){
    this->edgeColor = c;
}

inline void DrawableDelauneyTriangulation::setPointColor(const QColor &c){
    this->pointColor = c;
}

inline void DrawableDelauneyTriangulation::setEdgeWidth(const int &w){
    this->edgeWidth = w;
}

inline void DrawableDelauneyTriangulation::setPointSize(const int &s){
    this->pointSize = s;
}

#endif // DRAWABLEBOUNDINGTRIANGLE_H
