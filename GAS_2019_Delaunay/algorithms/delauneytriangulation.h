#ifndef DELAUNEYTRIANGULATION_H
#define DELAUNEYTRIANGULATION_H

#include "../data_structures/triangle.h"
#include "../data_structures/dagnode.h"
#include <cg3/geometry/2d/point2d.h>
#include <cg3/geometry/2d/utils2d.h>



class DelauneyTriangulation
{
    public:
        inline DelauneyTriangulation();
        inline DelauneyTriangulation(const Triangle &boundingTriangle);

        inline const std::vector<Triangle> getTriangles() const;
        inline DagNode* getDAG() const;
        inline const std::vector<cg3::Point2Dd> getPoints() const;
        inline void addPointToList(const cg3::Point2Dd &newPoint);

        std::vector<Triangle> makeTriangles(DagNode* currentNode, const cg3::Point2Dd &newPoint);
        void makeSplit (DagNode* currentNode, std::vector<Triangle> &newTriangles);
        void addPointToTriangulation (const cg3::Point2Dd &newPoint);

    protected:
        std::vector<Triangle> _delauneyTriangles;
        DagNode* _dag;
        std::vector<cg3::Point2Dd> _points;
};

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

inline const std::vector<cg3::Point2Dd> DelauneyTriangulation::getPoints() const{
    return this->_points;
}

inline void DelauneyTriangulation::addPointToList(const cg3::Point2Dd &newPoint) {
    this->_points.push_back(newPoint);
}

#endif // DELAUNEYTRIANGULATION_H
