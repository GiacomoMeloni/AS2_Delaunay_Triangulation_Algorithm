#include "dagnode.h"

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
    return (_childrens.size()==0) ? true : false;
}

/**
 * @brief Check if a point is lying in the triangle inside the current dag node
 * @param point - the reference of the newPoint to check
 * @return true if the point lies in the node's triangle, false otherwise
 */
inline bool DagNode::isPointInTriangle(cg3::Point2Dd &point) const{
    return cg3::isPointLyingInTriangle(
                this->_triangle.getV1(),
                this->_triangle.getV1(),
                this->_triangle.getV1(),
                point,true);
}


