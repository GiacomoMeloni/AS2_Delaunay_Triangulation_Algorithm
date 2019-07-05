#ifndef DELAUNEYTRIANGULATION_H
#define DELAUNEYTRIANGULATION_H

#include "../data_structures/triangle.h"
#include "../data_structures/dagnode.h"
#include <cg3/geometry/2d/point2d.h>
#include <cg3/geometry/2d/utils2d.h>
#include <Eigen/Dense>

/**
 * @brief Class that manage the Delaunay Triangulation. The aim of this class is to build and fill all the data structures that rappresenting the triangulation.
 * This class contains a vector of triangles that collect all that triangles made by splits;
 * a dag node pointer used to build the DAG structure starting from the root (the bounding triangle);
 * a vector of dagNode pointer that collect all the created pointer of the DAG (this is made to manage the cancellation of the dag and the construction of the voronoi diagram)
 */
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

/**
 * @brief Default constructor.
 **/
inline DelauneyTriangulation::DelauneyTriangulation(){

}

/**
 * @brief Constructor using the bounding triangle's reference.
 * Once the triangle is pushed inside the triangles vector, its index is used to instantiate the dag root
 * @param boundingTriangle the reference of the bounding triangle.
 */
inline DelauneyTriangulation::DelauneyTriangulation(const Triangle &boundingTriangle){
    this->_delauneyTriangles.push_back(boundingTriangle);
    size_t indexOfTriangle = _delauneyTriangles.size()-1;
    this->_dag = new DagNode(indexOfTriangle);
    this->_allNodeCollection={};
}

/**
 * @brief Deconstructor. It calls the function clearDelaunayTriangulation in order to manage the cancellation of the data structures.
 **/
inline DelauneyTriangulation::~DelauneyTriangulation(){
    clearDelaunayTriangulation();
}

/**
 * @brief getTrianles get the reference to the vector of triangles
 * @return the reference of the vector of triangles
 */
inline const std::vector<Triangle>& DelauneyTriangulation::getTriangles() const{
    return this->_delauneyTriangles;
}

/**
 * @brief getDAG get the pointer to the dag root
 * @return the pointer to the dag root
 */
inline DagNode* DelauneyTriangulation::getDAG() const{
    return this->_dag;
}

/**
 * @brief getLeaves get the vector of triangles leaves.
 * @return a vector of triangles
 */
inline std::vector<Triangle> DelauneyTriangulation::getLeaves() const{
    std::vector<Triangle> leaves;
    for (const Triangle &triangle : _delauneyTriangles){
        if (triangle.getIsALeaf()){
            leaves.push_back(triangle);
        }
    }
    return leaves;
}

/**
 * @brief getAllDagNodes get a reference to the vector of DAG nodes.
 * @return a reference to the vector of DAG nodes.
 */
inline std::vector<DagNode*>& DelauneyTriangulation::getAllDagNodes(){
    return this->_allNodeCollection;
}

/**
 * @brief addTriangleToTriangulation add a triangle inside the vector of triangles. Once added the other internal structures are setted.
 * @param the reference of the new Triangle to add.
 */
inline void DelauneyTriangulation::addTriangleToTriangulation (const Triangle &newTriangle){
    this->_delauneyTriangles.push_back(newTriangle);
    size_t indexOfTriangle = _delauneyTriangles.size()-1;
    this->_dag = new DagNode(indexOfTriangle);
    this->_allNodeCollection={};
}

/**
 * @brief isPointInNode check if a point is lying in the triangle inside the current dag node
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

/**
 * @brief clearDelaunayTriangulation clear all the data structures of the triangulation.
 */
inline void DelauneyTriangulation::clearDelaunayTriangulation (){
    std::vector<DagNode*> allDagNodes;
    this->_delauneyTriangles.clear();

    for (DagNode* node : _allNodeCollection){
        delete node;
    }
    this->_allNodeCollection.clear();
}

#endif // DELAUNEYTRIANGULATION_H
