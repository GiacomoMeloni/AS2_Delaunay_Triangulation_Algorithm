#include "drawabledelauneytriangulation.h"

DrawableDelaunayTriangulation::DrawableDelaunayTriangulation()
{

}

DrawableDelaunayTriangulation::DrawableDelaunayTriangulation(Triangle boudingTriangle) :
    DelauneyTriangulation (boudingTriangle)
{
    pointSize = 4;
    edgeWidth = 1;
    edgeColor=(QColor(0,0,255));
    pointColor=(QColor(255,0,0));
}

void DrawableDelaunayTriangulation::draw(){
    drawPoints();
    drawEdges();
}

cg3::Pointd DrawableDelaunayTriangulation::sceneCenter() const{
    return cg3::Pointd(0,0,0);
}

double DrawableDelaunayTriangulation::sceneRadius() const{
    return 1e+6;
}

void  DrawableDelaunayTriangulation::drawPoints() {
    for (cg3::Point2Dd &p : getPoints()){

    }
}

void  DrawableDelaunayTriangulation::drawEdges(){

}
