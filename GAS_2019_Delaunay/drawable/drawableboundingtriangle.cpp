#include "drawableboundingtriangle.h"

/**
 * @brief draw call the methods to draw points and edges
 */
void DrawableBoundingTriangle::draw() const
{
    drawPoints();
    drawEdges();
}

/**
 * @brief draw points using the triangle's vertices
 */
void DrawableBoundingTriangle::drawPoints() const{
    cg3::viewer::drawPoint2D(_v1, pointColor, pointSize);
    cg3::viewer::drawPoint2D(_v2, pointColor, pointSize);
    cg3::viewer::drawPoint2D(_v3, pointColor, pointSize);
}

/**
 * @brief draw edges using the triangle's vertices
 */
void DrawableBoundingTriangle::drawEdges() const{
    for (std::pair<cg3::Point2Dd,cg3::Point2Dd> &edge : getEdges()){
        cg3::viewer::drawLine2D(edge.first,edge.second, edgeColor, edgeWidth);
    }
}
