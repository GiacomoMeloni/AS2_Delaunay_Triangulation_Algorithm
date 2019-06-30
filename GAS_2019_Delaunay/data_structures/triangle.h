#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cg3/geometry/2d/point2d.h>

/**
 * @brief Class representing a 2D Triangle. The triangle is rappresented by three vertices.
 * The vertices order is counter-clockwise.
 */

class Triangle
{

    public:
        /* --- Constructor --- */
        inline Triangle();
        inline Triangle (const cg3::Point2Dd& v1,const cg3::Point2Dd& v2,const cg3::Point2Dd& v3);

        /* --- Getters --- */
        inline const cg3::Point2Dd getV1() const;
        inline const cg3::Point2Dd getV2() const;
        inline const cg3::Point2Dd getV3() const;
        inline const std::vector<cg3::Point2Dd> getVertices() const;
        inline std::vector<std::pair <cg3::Point2Dd, cg3::Point2Dd>> getEdges() const;

        /* --- Setters --- */
        inline void setV1(const cg3::Point2Dd &v);
        inline void setV2(const cg3::Point2Dd &v);
        inline void setV3(const cg3::Point2Dd &v);
        inline void setVertices(const cg3::Point2Dd &v1, const cg3::Point2Dd &v2, const cg3::Point2Dd &v3);

        /* --- Methods --- */
        inline cg3::Point2Dd getCenter() const;
        inline double getHypotenuse() const;
        inline bool checkOrientationCounterclockwise(const cg3::Point2Dd& v1,const cg3::Point2Dd& v2,const cg3::Point2Dd& v3) const;
        inline void orderingCounterClockwise();

    protected:
        cg3::Point2Dd _v1;
        cg3::Point2Dd _v2;
        cg3::Point2Dd _v3;

};

/**
 * @brief Default constructor
 */
inline Triangle::Triangle(){

}

/**
 * @brief Constructor with the points (counter-clockwise)
 * @param v1 - reference of the first vertex
 * @param v2 - reference of the second vertex
 * @param v3 - reference of the third vertex
 */
inline Triangle::Triangle (const cg3::Point2Dd& v1,const cg3::Point2Dd& v2,const cg3::Point2Dd& v3){
    if (!checkOrientationCounterclockwise(v1,v2,v3)){
        this->orderingCounterClockwise();

    this->_v1 = v1;
    this->_v2 = v2;
    this->_v3 = v3;
    }
}

/**
 * @brief Get the first vertex of the triangle
 * @return _v1 - the reference of the first triangle's vertex
 */
inline const cg3::Point2Dd Triangle::getV1() const {
    return this->_v1;
}

/**
 * @brief Get the second vertex of the triangle
 * @return _v2 - the reference of the second triangle's vertex
 */
inline const cg3::Point2Dd Triangle::getV2() const {
    return this->_v2;
}

/**
 * @brief Get the third vertex of the triangle
 * @return _v3 - the reference of the third triangle's vertex
 */
inline const cg3::Point2Dd Triangle::getV3() const {
    return this->_v3;
}

/**
 * @brief Get the vertices of the triangle
 * @return _vertices - the list of triangle's vertices
 */
inline const std::vector<cg3::Point2Dd> Triangle::getVertices() const {
    std::vector<cg3::Point2Dd> _vertices;

    _vertices.push_back(this->_v1);
    _vertices.push_back(this->_v2);
    _vertices.push_back(this->_v3);
    return _vertices;
}

/**
 * @brief Get the edges of the triangle
 * @return _edges - the list of triangle's edges
 */
inline std::vector<std::pair <cg3::Point2Dd, cg3::Point2Dd>> Triangle::getEdges() const{
    std::vector<std::pair <cg3::Point2Dd, cg3::Point2Dd>> _edges;

    _edges.push_back( std::make_pair(this->_v1,this->_v2));
    _edges.push_back( std::make_pair(this->_v1,this->_v3));
    _edges.push_back( std::make_pair(this->_v2,this->_v3));

    return _edges;
}

/**
 * @brief Set the value of the first vertex
 * @param v - reference of the new vertex value
 * @return new value of first vertex
 */
inline void Triangle::setV1(const cg3::Point2Dd &v){
    this->_v1 = v;
}

/**
 * @brief Set the value of the second vertex
 * @param v - vertex
 * @return new value of second vertex
 */
inline void Triangle::setV2(const cg3::Point2Dd &v){
    this->_v2 = v;
}

/**
 * @brief Set the value of the third vertex
 * @param v - vertex
 * @return new value of third vertex
 */
inline void Triangle::setV3(const cg3::Point2Dd &v){
    this->_v3 = v;
}

/**
 * @brief Set the vertices of the triangle
 * @param v1 - reference of the new value of the first vertex
 * @param v2 - reference of the new value of the second vertex
 * @param v3 - reference of the new value of the third vertex
 * @return new values for the vertices of the triangle
 */
inline void Triangle::setVertices(const cg3::Point2Dd &v1, const cg3::Point2Dd &v2, const cg3::Point2Dd &v3){
    this->_v1 = v1;
    this->_v2 = v2;
    this->_v3 = v3;
}

inline cg3::Point2Dd Triangle::getCenter() const{
    double centX, centY;
    for (cg3::Point2Dd p : getVertices()){
        centX += p.x();
        centY += p.y();
    }
    centX /= getVertices().size();
    centY /= getVertices().size();

    return *new cg3::Point2Dd (centX,centY);
}

inline double Triangle::getHypotenuse() const{
    return std::max({
                this->getV1().dist(this->getV2()),
                this->getV1().dist(this->getV3()),
                this->getV2().dist(this->getV3())});
}

/**
 * @brief Check if the triangle vertices are in counterclockwise order
 * @param v1 - reference of the first vertex
 * @param v2 - reference of the second vertex
 * @param v3 - reference of the third vertex
 * @return true if vertices are in counterclockwise order false otherwise
 */
inline bool Triangle::checkOrientationCounterclockwise(const cg3::Point2Dd &v1,const cg3::Point2Dd &v2,const cg3::Point2Dd &v3) const{
    double check = (v2.y() - v1.y()) * (v3.x() - v2.x()) - (v2.x() - v1.x()) * (v3.y() - v2.y());

    if (check >= 0)
        return false;
    else {
        return true;
    }
}

/**
 * @brief Order the last two vertices to have a counterclockwise vertices order
 * @return vertices ordered in counterclockwise order
 */
inline void Triangle::orderingCounterClockwise(){
    cg3::Point2Dd temp;
    temp = this->_v2;
    this->_v2 = this->_v3;
    this->_v3 = temp;
}

#endif // TRIANGLE_H
