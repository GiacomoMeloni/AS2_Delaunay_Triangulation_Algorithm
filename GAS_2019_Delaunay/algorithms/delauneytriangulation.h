#ifndef DELAUNEYTRIANGULATION_H
#define DELAUNEYTRIANGULATION_H

#include "../data_structures/triangle.h"
#include "../data_structures/dagnode.h"
#include <cg3/geometry/2d/point2d.h>
#include <cg3/geometry/2d/utils2d.h>
#include <Eigen/Dense>



class DelauneyTriangulation
{
    public:
        /* --- Constructor --- */
        inline DelauneyTriangulation();
        inline DelauneyTriangulation(const Triangle &boundingTriangle);
        inline ~DelauneyTriangulation();

        /* --- Getters --- */
        inline const std::vector<Triangle>& getTriangles() const;
        inline DagNode* getDAG() const;
        inline std::vector<Triangle> getLeaves() const;
        cg3::Point2Dd getOppositePoint(const Triangle &currentTriangle, const Triangle &adjacentTriangle);
        inline std::vector<DagNode*>& getAllDagNodes();
        DagNode* getChildContainsPoint(DagNode* &currentNode, const cg3::Point2Dd &point);

        /* --- Setters --- */
        inline void addTriangleToTriangulation (const Triangle &newTriangle);

        /* --- Methods --- */
        void updateAdjacencies(DagNode* father, DagNode* child, DagNode* nodeOfFirstBrother, DagNode* nodeOfSecondBrother);
        void updateAdjacenciesOnBrothers(DagNode* adjacent, DagNode* splittedBrother);
        void updateAdjacenciesOnEdgeFlip(DagNode* father_1, DagNode* father_2, DagNode* child, DagNode* brotherNode);
        inline bool isPointInNode(DagNode* &currentNode, const cg3::Point2Dd &point) const;        
        void makeSplits(DagNode* currentNode, const cg3::Point2Dd &newPoint);
        void addPointToTriangulation (const cg3::Point2Dd &newPoint);
        void legalizeEdge (DagNode* node, size_t lowerBrotherIndex);
        inline void clearDelaunayTriangulation();


    protected:
        std::vector<Triangle> _delauneyTriangles;
        DagNode* _dag;
        std::vector<DagNode*> _allNodeCollection;
};

inline DelauneyTriangulation::DelauneyTriangulation(){

}

inline DelauneyTriangulation::DelauneyTriangulation(const Triangle &boundingTriangle){
    this->_delauneyTriangles.push_back(boundingTriangle);
    size_t indexOfTriangle = _delauneyTriangles.size()-1;
    this->_dag = new DagNode(indexOfTriangle);
    this->_allNodeCollection={};
}

inline DelauneyTriangulation::~DelauneyTriangulation(){
    clearDelaunayTriangulation();
}

inline const std::vector<Triangle>& DelauneyTriangulation::getTriangles() const{
    return this->_delauneyTriangles;
}

inline DagNode* DelauneyTriangulation::getDAG() const{
    return this->_dag;
}

inline std::vector<Triangle> DelauneyTriangulation::getLeaves() const{
    std::vector<Triangle> leaves;
    for (const Triangle &triangle : _delauneyTriangles){
        if (triangle.getIsALeaf()){
            leaves.push_back(triangle);
        }
    }
    return leaves;
}

inline std::vector<DagNode*>& DelauneyTriangulation::getAllDagNodes(){
    return this->_allNodeCollection;
}

inline void DelauneyTriangulation::addTriangleToTriangulation (const Triangle &newTriangle){
    this->_delauneyTriangles.push_back(newTriangle);
    size_t indexOfTriangle = _delauneyTriangles.size()-1;
    this->_dag = new DagNode(indexOfTriangle);
    this->_allNodeCollection={};
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

inline void DelauneyTriangulation::clearDelaunayTriangulation (){
    std::vector<DagNode*> allDagNodes;
    this->_delauneyTriangles.clear();

    for (DagNode* node : _allNodeCollection){
        delete node;
    }
    this->_allNodeCollection.clear();
}

#endif // DELAUNEYTRIANGULATION_H
