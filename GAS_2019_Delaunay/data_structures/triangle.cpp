#include "triangle.h"

/**
 * @brief Calculate the circumcenter of the triangle
 * @return the point of the circumcenter
 */
cg3::Point2Dd Triangle::getCircleCenter() const{
    double m1 = (this->_v1.x() - this->_v2.x())/(this->_v2.y() - this->_v1.y());
    double m2 = (this->_v1.x() - this->_v3.x())/(this->_v3.y() - this->_v1.y());

    double x = 0.5 * (this->_v1.x() + (this->_v2.x()*m1 - this->_v2.y() + this->_v3.y() - this->_v3.x()*m2)/(m1 - m2));
    double y = 0.5 * (this->_v1.y() + this->_v2.y() + (2*x - this->_v1.x() - this->_v2.x())*m1);

    return cg3::Point2Dd(x,y);
}

