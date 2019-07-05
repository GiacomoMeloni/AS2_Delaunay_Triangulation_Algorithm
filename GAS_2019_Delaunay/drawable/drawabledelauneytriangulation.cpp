#include "drawabledelauneytriangulation.h"

/**
 * @brief draw call the methods to draw points and edges, taking in consideration
 * triangles that are setted as leaves in the triangles collections.
 */
void DrawableDelauneyTriangulation::draw() const
{
    for (const Triangle &triangle : this->getTriangles()){
        if (triangle.getIsALeaf()){
            drawPoints(triangle);
            drawEdges(triangle);
        }
    }
}

/**
 * @brief draw points using the triangle's vertices
 */
void DrawableDelauneyTriangulation::drawPoints(const Triangle &triangle) const{
    cg3::viewer::drawPoint2D(triangle.getV1(), pointColor, pointSize);
    cg3::viewer::drawPoint2D(triangle.getV2(), pointColor, pointSize);
    cg3::viewer::drawPoint2D(triangle.getV3(), pointColor, pointSize);
}

/**
 * @brief draw edges using the triangle's vertices
 */
void DrawableDelauneyTriangulation::drawEdges(const Triangle &triangle) const{
    for (std::pair<cg3::Point2Dd,cg3::Point2Dd> &edge : triangle.getEdges()){
        cg3::viewer::drawLine2D(edge.first,edge.second, edgeColor, edgeWidth);
    }
}
