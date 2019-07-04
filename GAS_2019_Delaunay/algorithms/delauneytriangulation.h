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
        inline std::vector<Triangle> getLeaves() const;
        cg3::Point2Dd getOppositePoint(const Triangle &currentTriangle, const Triangle &adjacentTriangle);

        inline void addPointToList(const cg3::Point2Dd &newPoint);

        void updateAdjacencies(DagNode* father, DagNode* child, DagNode* nodeOfFirstBrother, DagNode* nodeOfSecondBrother);
        void updateAdjacenciesOnBrothers(DagNode* adjacent, DagNode* splittedBrother);
        void updateAdjacenciesOnEdgeFlip(DagNode* father_1, DagNode* father_2, DagNode* child, DagNode* brotherNode);
        inline bool isPointInNode(DagNode* &currentNode, const cg3::Point2Dd &point) const;
        DagNode* getChildContainsPoint(DagNode* &currentNode, const cg3::Point2Dd &point);
        void makeSplits(DagNode* currentNode, const cg3::Point2Dd &newPoint);
        void addPointToTriangulation (const cg3::Point2Dd &newPoint);
        void legalizeEdge (DagNode* node, size_t lowerBrotherIndex);

        inline void clearDagNode (DagNode* node);
        inline void clearDelaunayTriangulation();


    protected:
        std::vector<Triangle> _delauneyTriangles;
        DagNode* _dag;
        std::vector<cg3::Point2Dd> _points;
};

inline DelauneyTriangulation::DelauneyTriangulation(){

}

inline DelauneyTriangulation::DelauneyTriangulation(const Triangle &boundingTriangle){
    this->_delauneyTriangles.push_back(boundingTriangle);
    size_t indexOfTriangle = _delauneyTriangles.size()-1;
    this->_dag = new DagNode(indexOfTriangle);
    this->_delauneyTriangles[0].setIsALeaf(true);
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

inline std::vector<Triangle> DelauneyTriangulation::getLeaves() const{
    std::vector<Triangle> leaves;
    for (const Triangle &triangle : getTriangles()){
        if (triangle.getIsALeaf()){
            leaves.push_back(triangle);
        }
    }
    return  leaves;
}

inline void DelauneyTriangulation::addPointToList(const cg3::Point2Dd &newPoint) {
    this->_points.push_back(newPoint);
}

/**
 * @brief Check if a point is lying in the triangle inside the current dag node
 * @param point - the reference of the newPoint to check
 * @return true if the point lies in the node's triangle, false otherwise
 */
inline bool DelauneyTriangulation::isPointInNode(DagNode* &currentNode, const cg3::Point2Dd &point) const{
    return cg3::isPointLyingInTriangle(
                this->_delauneyTriangles[currentNode->getTriangleIndex()].getV1(),
                this->_delauneyTriangles[currentNode->getTriangleIndex()].getV2(),
                this->_delauneyTriangles[currentNode->getTriangleIndex()].getV3(),
                point,true);
}

//inline void DelauneyTriangulation::clearDagNode (DagNode* node){
//    if (!node->getChildrens().empty()){
//        for (DagNode* child : node->getChildrens()){
//            clearDagNode(child);
//        }
//    }
//    free(node);
//}

//inline void DelauneyTriangulation::clearDelaunayTriangulation (){
//    this->_delauneyTriangles.clear();
//    this->_points.clear();
//    clearDagNode(this->_dag);
//}

#endif // DELAUNEYTRIANGULATION_H
