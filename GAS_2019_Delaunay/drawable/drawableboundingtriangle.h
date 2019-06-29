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

#endif // DRAWABLEBOUNDINGTRIANGLE_H
