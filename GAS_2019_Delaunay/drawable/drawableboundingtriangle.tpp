#include "drawableboundingtriangle.h"

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
    return getHypotenuse();
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
