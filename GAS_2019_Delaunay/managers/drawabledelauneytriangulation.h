#ifndef DRAWABLEDELAUNAYTRIANGULATION_H
#define DRAWABLEDELAUNAYTRIANGULATION_H

#include "cg3/viewer/interfaces/drawable_object.h"
#include "../algorithms/delauneytriangulation.h"

class DrawableDelaunayTriangulation :public DelauneyTriangulation, public cg3::DrawableObject
{
    public:
        DrawableDelaunayTriangulation();
        DrawableDelaunayTriangulation(Triangle boundingTriangle);

        void draw();
        cg3::Pointd sceneCenter() const;
        double sceneRadius() const;


    private:
        void drawEdges();
        void drawPoints();

        int pointSize;
        QColor pointColor;
        int edgeWidth;
        QColor edgeColor;
};

#endif // DRAWABLEDELAUNAYTRIANGULATION_H
