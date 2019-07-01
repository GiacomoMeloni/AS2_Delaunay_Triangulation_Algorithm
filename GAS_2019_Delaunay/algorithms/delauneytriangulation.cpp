#include "delauneytriangulation.h"

void DelauneyTriangulation::updateAdjacencies(DagNode* father, DagNode* child, size_t &indexOfFirstBrother, size_t &indexOfSecondBrother){
    if (!father->getAdjacencies().empty()){
        for (size_t &triangleIndex : father->getAdjacencies()){
            if (_delauneyTriangles[triangleIndex].isAdjacent(_delauneyTriangles[child->getTriangleIndex()])){
                child->addAdjacencies(triangleIndex);
            }
        }
    }
    child->addAdjacencies(indexOfFirstBrother);
    child->addAdjacencies(indexOfSecondBrother);
}

DagNode* DelauneyTriangulation::getChildContainsPoint(DagNode* &currentNode, const cg3::Point2Dd &point){
    for (DagNode *node : currentNode->getChildrens()){
        if (cg3::isPointLyingInTriangle(
                    this->_delauneyTriangles[node->getTriangleIndex()].getV1(),
                    this->_delauneyTriangles[node->getTriangleIndex()].getV2(),
                    this->_delauneyTriangles[node->getTriangleIndex()].getV3(),
                    point,true)){
            return node;
        }
    }
    return nullptr;
}

void DelauneyTriangulation::makeSplits(DagNode* currentNode, const cg3::Point2Dd &newPoint){
    Triangle delta1 = *new Triangle(
                _delauneyTriangles[currentNode->getTriangleIndex()].getV1(),
                _delauneyTriangles[currentNode->getTriangleIndex()].getV2(),
                newPoint, true);
    Triangle delta2 = *new Triangle(
                _delauneyTriangles[currentNode->getTriangleIndex()].getV1(),
                _delauneyTriangles[currentNode->getTriangleIndex()].getV3(),
                newPoint, true);
    Triangle delta3 = *new Triangle(
                _delauneyTriangles[currentNode->getTriangleIndex()].getV2(),
                _delauneyTriangles[currentNode->getTriangleIndex()].getV3(),
                newPoint, true);

    this->_delauneyTriangles.push_back(delta1);
    size_t indexOfFirstChildTriangle = _delauneyTriangles.size()-1;
    currentNode->addChild(new DagNode(indexOfFirstChildTriangle));

    this->_delauneyTriangles.push_back(delta2);
    size_t indexOfSecondChildTriangle = _delauneyTriangles.size()-1;
    currentNode->addChild(new DagNode(indexOfSecondChildTriangle));

    this->_delauneyTriangles.push_back(delta3);
    size_t indexOfThirdChildTriangle = _delauneyTriangles.size()-1;
    currentNode->addChild(new DagNode(indexOfThirdChildTriangle));

    updateAdjacencies(currentNode,currentNode->getFirstChild(),indexOfSecondChildTriangle,indexOfThirdChildTriangle);
    updateAdjacencies(currentNode,currentNode->getSecondChild(),indexOfFirstChildTriangle,indexOfThirdChildTriangle);
    updateAdjacencies(currentNode,currentNode->getThirdChild(),indexOfFirstChildTriangle,indexOfSecondChildTriangle);
}

void DelauneyTriangulation::addPointToTriangulation(const cg3::Point2Dd &newPoint){
    bool found= false;
    DagNode* check = getDAG();
    addPointToList(newPoint);

    while (found == false){
        if (check->isALeaf() /*&& check->isPointInTriangle(newPoint)*/){
            _delauneyTriangles[check->getTriangleIndex()].setIsALeaf(false);
            makeSplits(check, newPoint);
            found = true;
        }else{
            check = getChildContainsPoint(check,newPoint);
        }
    }
}
