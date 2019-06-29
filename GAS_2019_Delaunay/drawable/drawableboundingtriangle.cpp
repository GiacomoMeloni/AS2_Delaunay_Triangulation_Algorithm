#include "drawableboundingtriangle.h"

void DrawableBoundingTriangle::draw() const
{
    drawPoints();
    drawEdges();
}

void DrawableBoundingTriangle::drawPoints() const{
    cg3::viewer::drawPoint2D(getV1(), pointColor, pointSize);
    cg3::viewer::drawPoint2D(getV2(), pointColor, pointSize);
    cg3::viewer::drawPoint2D(getV3(), pointColor, pointSize);
}

void DrawableBoundingTriangle::drawEdges() const{
    for (std::pair<cg3::Point2Dd,cg3::Point2Dd> &edge : getEdges()){
        cg3::viewer::drawLine2D(edge.first,edge.second, edgeColor, edgeWidth);
    }
}
