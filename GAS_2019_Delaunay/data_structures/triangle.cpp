#include "triangle.h"

/**
 * @brief Default constructor
 */
Triangle::Triangle()
{

}

/**
 * @brief Constructor with the points (counter-clockwise)
 * @param points The list of points
 */
Triangle::Triangle(const cg3::Point2Dd& v1,const cg3::Point2Dd& v2,const cg3::Point2Dd& v3)
{
    this->_v1 = v1;
    this->_v2 = v2;
    this->_v3 = v3;

    if (!checkOrientationCounterclockwise(this->_v1,this->_v2,this->_v3)){
        orderingCounterClockwise();
    }
}

/**
 * @brief Find orientation of ordered triplet (v1, v2, v3).
 * @return true if the orientation of vertices is counterclockwise, false otherwise.
 */
bool checkOrientationCounterclockwise(const cg3::Point2Dd& v1,const cg3::Point2Dd& v2,const cg3::Point2Dd& v3){

    double check = (v2.y() - v1.y()) * (v3.x() - v2.x()) - (v2.x() - v1.x()) * (v3.y() - v2.y());

    if (check >= 0)
        return false;
    else {
        return true;
    }
}
