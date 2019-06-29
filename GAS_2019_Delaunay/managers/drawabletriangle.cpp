#include "drawabletriangle.h"

#include <cg3/viewer/renderable_objects/2d/renderable_objects2d.h>

/**
 * @brief Empty polygon default constructor
 */
DrawableTriangle::DrawableTriangle() : Triangle(), color(QColor(0,0,255))
{

}

/**
 * @brief Constructor with a list of points
 * @param points Points of the polygon
 */
DrawableTriangle::DrawableTriangle(const cg3::Point2Dd& v1,const cg3::Point2Dd& v2,const cg3::Point2Dd& v3)
    : Triangle(v1,v2,v3),
      color(QColor(0,0,255))
{

}

/**
 * @brief Set color of the edges of the convex hull
 * @param color Color of the edges
 */
void DrawableTriangle::setColor(const QColor& color)
{
    this->color = color;
}

/**
 * @brief Method for drawing a polygon 2d
 */
void DrawableTriangle::draw() const {
    drawPoints();
    drawEdges();
}

/**
 * @brief Get the center of the polygon 2D
 * @return Center of the scene
 */
cg3::Pointd DrawableTriangle::sceneCenter() const {
    cg3::Pointd center(0,0,0);

    for (const cg3::Point2Dd &p : getVertices()){
        center.x() += p.x();
        center.y() += p.y();
    }

    center /= getVertices().size();
    return center;
}

/**
 * @brief Get the radius of the scene containing the polygon 2D
 * @return Radius of the scene
 */
double DrawableTriangle::sceneRadius() const {
    cg3::Pointd center = sceneCenter();

    double maxDistance = 0;
    return maxDistance;
}

void DrawableTriangle::drawEdges() const {
    cg3::viewer::drawLine2D(cg3::Point2Dd(getV1().x(), getV1().y()), cg3::Point2Dd(getV2().x(), getV2().y()), QColor(0,0,255), 1);
    cg3::viewer::drawLine2D(cg3::Point2Dd(getV1().x(), getV1().y()), cg3::Point2Dd(getV3().x(), getV3().y()), QColor(0,0,255), 1);
    cg3::viewer::drawLine2D(cg3::Point2Dd(getV2().x(), getV2().y()), cg3::Point2Dd(getV3().x(), getV3().y()), QColor(0,0,255), 1);
}

void DrawableTriangle::drawPoints() const {
    cg3::viewer::drawPoint2D(cg3::Point2Dd(getV1().x(), getV1().y()), QColor(0,0,255), 2);
    cg3::viewer::drawPoint2D(cg3::Point2Dd(getV2().x(), getV2().y()), QColor(0,0,255), 2);
    cg3::viewer::drawPoint2D(cg3::Point2Dd(getV3().x(), getV3().y()), QColor(0,0,255), 2);
}


