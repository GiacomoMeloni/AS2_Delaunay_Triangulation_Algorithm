#ifndef DAG_H
#define DAG_H

#include <cg3/geometry/2d/point2d.h>
#include "triangle.h"
#include <cg3/geometry/2d/utils2d.h>

class DagNode
{
    public:

        /* --- Constructor --- */
        inline DagNode();
        inline DagNode(size_t &idexOftriangle);

        /* --- Getter --- */
//        inline Triangle* getTriangle() const;
        inline size_t getTriangleIndex() const;
        inline std::vector<DagNode*> getChildrens() const;
        inline std::vector<DagNode*> getAdjacencies() const;
        inline DagNode* getFirstChild() const;
        inline DagNode* getSecondChild() const;
        inline DagNode* getThirdChild() const;

        /* --- Setter --- */
        inline void addChild(DagNode* newNode);
        inline void addAdjacencies(DagNode* &adjacentNode);

        /* --- Methods --- */
        inline bool checkNumberOfChildrens() const;
        inline bool isALeaf() const;
        inline void changeAdjacencies(DagNode* old, DagNode* current);

    protected:
//        Triangle _triangle;
        size_t _triangleIndex;
        std::vector<DagNode*> _childrens;
        std::vector<DagNode*> _adjacencies;
};

/**
 * @brief Default constructor
 */
inline DagNode::DagNode(){

}

/**
 * @brief Dag node constructor with the triangle's index
 * @param indexOfTriangle - the index of the triangle
 */
inline DagNode::DagNode(size_t &indexOftriangle){
    this->_triangleIndex = indexOftriangle;
    this->_childrens = {};
    this->_adjacencies = {};
}

/**
 * @brief Get the triangle index stored in the node
 * @return _triangleIndex - the triangle index stored in the dag node
 */
inline size_t DagNode::getTriangleIndex() const{
    return this->_triangleIndex;
}

/**
 * @brief Get the list of node's childrens
 * @return childrens - the list of pointers from the current dag's node
 */
inline std::vector<DagNode*> DagNode::getChildrens() const{
    return this->_childrens;
}

/**
 * @brief Get the list of triangle's indeces ajacent to the triangle pointed by the current node
 * @return _ajacencies - the list of triangle's indeces adjacet with the current node's triangle
 */
inline std::vector<DagNode*> DagNode::getAdjacencies() const{
    return this-> _adjacencies;
}

inline DagNode* DagNode::getFirstChild() const{
    return this->_childrens[0];
}

inline DagNode* DagNode::getSecondChild() const{
    return this->_childrens[1];
}

inline DagNode* DagNode::getThirdChild() const{
    return this->_childrens[2];
}

/**
 * @brief Add a child in the list of the node
 * @param newNode - the pointer of the new dag node created
 * @return add the node in the list of childrens of the current dag node
 */
inline void DagNode::addChild(DagNode* newNode){
    if (checkNumberOfChildrens()){
        this->_childrens.push_back(newNode);
    }
}

inline void DagNode::addAdjacencies(DagNode* &adjacentNode){
    this->_adjacencies.push_back(adjacentNode);
}

/**
 * @brief Check if the number of the children is more than 3
 * @return true if the size of the children is less than 3, false otherwise
 */
inline bool DagNode::checkNumberOfChildrens () const{
    return (this->_childrens.size()<3) ? true : false;
}

/**
 * @brief Check if the current dag node is a leaf
 * @return true if the dag node doesn't got any child, false otherwise
 */
inline bool DagNode::isALeaf () const{
    return _childrens.empty();
}

inline void DagNode::changeAdjacencies(DagNode* old, DagNode* current){
    for (size_t i = 0; i < getAdjacencies().size(); i++){
        if (_adjacencies[i] == old){
            _adjacencies[i] = current;
        }
    }
}

#endif // DAG_H
