#include "delauneytriangulation.h"

inline DelauneyTriangulation::DelauneyTriangulation(){

}

inline DelauneyTriangulation::DelauneyTriangulation(const Triangle &boundingTriangle){
    this->_delauneyTriangles.push_back(boundingTriangle);
    this->_dag = new DagNode (boundingTriangle);
    this->_points = {};
}

inline const std::vector<Triangle> DelauneyTriangulation::getTriangles() const{
    return this->_delauneyTriangles;
}

inline DagNode* DelauneyTriangulation::getDAG() const{
    return this->_dag;
}

inline const std::vector<cg3::Point2Dd> DelauneyTriangulation::getPoints(){
    return this->_points;
}

inline void DelauneyTriangulation::addPointToList(const cg3::Point2Dd &newPoint) {
    this->_points.push_back(newPoint);
}
