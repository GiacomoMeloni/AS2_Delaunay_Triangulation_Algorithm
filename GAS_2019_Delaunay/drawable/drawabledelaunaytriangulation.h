#ifndef DRAWABLEDELAUNEYTRIANGULATION_H
#define DRAWABLEDELAUNEYTRIANGULATION_H

#include <cg3/utilities/color.h>
#include "cg3/viewer/interfaces/drawable_object.h"
#include "cg3/viewer/renderable_objects/2d/renderable_objects2d.h"
#include "../algorithms/delaunaytriangulationalgorithm.h"

/**
 * @brief Class representing the drawable Delaunay Triangulation. This class inherit to cg3::DrawableObject and from DelaunayTriangulation.
 * It permit to draw a Delaunay Triangulation.
 * This class contains the features of the geometric objects that will be draw.
 */
class DrawableDelaunayTriangulation : public cg3::DrawableObject, public DelaunayTriangulationAlgorithm {
    public:
        inline DrawableDelaunayTriangulation();
        inline DrawableDelaunayTriangulation(const Triangle &boundingTriangle);

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

/**
 * @brief Default constructor. The attributes are setted staticaly, calling the related methods.
 */
inline DrawableDelaunayTriangulation::DrawableDelaunayTriangulation() {
    setEdgeColor(QColor(0,0,255));
    setPointColor(QColor(255,0,0));
    setEdgeWidth(1);
    setPointSize(3);
}

/**
 * @brief Constructor using the bounding triangle's reference.
 * The attributes inside the drawable class are set statically by calling the relative methods.
 * @param boundingTriangle the reference of the bounding triangle.
 */
inline DrawableDelaunayTriangulation::DrawableDelaunayTriangulation(const Triangle &boundingTriangle):DelaunayTriangulationAlgorithm (boundingTriangle) {
    setEdgeColor(QColor(0,0,255));
    setPointColor(QColor(255,0,0));
    setEdgeWidth(1);
    setPointSize(3);
}

/**
 * @brief sceneCenter
 * @return
 */
inline cg3::Pointd DrawableDelaunayTriangulation::sceneCenter() const{
    return cg3::Pointd (0, 0, 0);
}

/**
 * @brief sceneRadius
 * @return
 */
inline double DrawableDelaunayTriangulation::sceneRadius() const{
    return 1e+6;
}

/**
 * @brief setEdgeColor
 * @param c edge color
 */
inline void DrawableDelaunayTriangulation::setEdgeColor(const QColor &c){
    this->edgeColor = c;
}

/**
 * @brief setPointColor
 * @param c point color
 */
inline void DrawableDelaunayTriangulation::setPointColor(const QColor &c){
    this->pointColor = c;
}

/**
 * @brief setEdgeWidth
 * @param w edge width
 */
inline void DrawableDelaunayTriangulation::setEdgeWidth(const int &w){
    this->edgeWidth = w;
}

/**
 * @brief setPointSize
 * @param s point size
 */
inline void DrawableDelaunayTriangulation::setPointSize(const int &s){
    this->pointSize = s;
}

#endif // DRAWABLEBOUNDINGTRIANGLE_H
