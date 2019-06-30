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
        inline DagNode(const Triangle &triangle);

        /* --- Getter --- */
        inline Triangle getTriangle() const;
        inline std::vector<DagNode*> getChildrens() const;
        DagNode* getChildContainsPoint(const cg3::Point2Dd &point);

        /* --- Setter --- */
        inline void addChild(DagNode* newNode);

        /* --- Methods --- */
        inline bool checkNumberOfChildrens() const;
        inline bool isALeaf() const;
        inline bool isPointInTriangle(const cg3::Point2Dd &point) const;


    protected:
        Triangle _triangle;
        std::vector<DagNode*> _childrens;
};

/**
 * @brief Default constructor
 */
inline DagNode::DagNode(){

}

/**
 * @brief Dag node constructor with the triangle's reference
 * @param triangle - the reference of the triangle
 */
inline DagNode::DagNode(const Triangle &triangle){
    this->_triangle = triangle;
    this->_childrens = {};
}

/**
 * @brief Get the triangle stored in the node
 * @return triangle - the triangle stored in the dag node
 */
inline Triangle DagNode::getTriangle() const{
    return this->_triangle;
}

/**
 * @brief Get the list of node's childrens
 * @return childrens - the list of pointers from the current dag's node
 */
inline std::vector<DagNode*> DagNode::getChildrens() const{
    return this->_childrens;
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

/**
 * @brief Check if a point is lying in the triangle inside the current dag node
 * @param point - the reference of the newPoint to check
 * @return true if the point lies in the node's triangle, false otherwise
 */
inline bool DagNode::isPointInTriangle(const cg3::Point2Dd &point) const{
    return cg3::isPointLyingInTriangle(
                this->_triangle.getV1(),
                this->_triangle.getV1(),
                this->_triangle.getV1(),
                point,true);
}

#endif // DAG_H
