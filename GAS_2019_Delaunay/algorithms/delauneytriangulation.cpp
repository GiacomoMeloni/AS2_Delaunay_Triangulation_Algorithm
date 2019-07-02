#include "delauneytriangulation.h"

cg3::Point2Dd DelauneyTriangulation::getOppositePoint(const Triangle &currentTriangle,const Triangle &adjacentTriangle){
    for (cg3::Point2Dd vertexCurrentTriangle : currentTriangle.getVertices()){
        for (cg3::Point2Dd vertexAdjacentTriangle : adjacentTriangle.getVertices()){
            if (vertexCurrentTriangle != vertexAdjacentTriangle)
                return vertexAdjacentTriangle;
        }
    }
    return cg3::Point2Dd(0,0);
}

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

void DelauneyTriangulation::updateAdjacencies(DagNode* father, DagNode* child, size_t &brotherIndex){
    if (!father->getAdjacencies().empty()){
        for (size_t &triangleIndex : father->getAdjacencies()){
            if (_delauneyTriangles[triangleIndex].isAdjacent(_delauneyTriangles[child->getTriangleIndex()])){
                child->addAdjacencies(triangleIndex);
            }
        }
    }
    child->addAdjacencies(brotherIndex);
}


void DelauneyTriangulation::legalizeEdge(DagNode* node){
    cg3::Point2Dd oppositePoint;

    for (size_t indexAdjacentTriangle : node->getAdjacencies()){
        oppositePoint = getOppositePoint(_delauneyTriangles[node->getTriangleIndex()],_delauneyTriangles[indexAdjacentTriangle]);

        if(cg3::isPointLyingInCircle(
                    _delauneyTriangles[node->getTriangleIndex()].getV1(),
                    _delauneyTriangles[node->getTriangleIndex()].getV2(),
                    _delauneyTriangles[node->getTriangleIndex()].getV3(),
                    oppositePoint, true)){

            _delauneyTriangles[node->getTriangleIndex()].setIsALeaf(false);
            _delauneyTriangles[indexAdjacentTriangle].setIsALeaf(false);

            Triangle delta1 = *new Triangle(
                        _delauneyTriangles[node->getTriangleIndex()].getV1(),
                        _delauneyTriangles[node->getTriangleIndex()].getV3(),
                        oppositePoint,true);
            Triangle delta2 = *new Triangle(
                        _delauneyTriangles[node->getTriangleIndex()].getV1(),
                        _delauneyTriangles[node->getTriangleIndex()].getV2(),
                        oppositePoint,true);

            this->_delauneyTriangles.push_back(delta1);
            size_t indexOfFirstChildTriangle = _delauneyTriangles.size()-1;
            node->addChild(new DagNode(indexOfFirstChildTriangle));

            this->_delauneyTriangles.push_back(delta2);
            size_t indexOfSecondChildTriangle = _delauneyTriangles.size()-1;
            node->addChild(new DagNode(indexOfSecondChildTriangle));

            updateAdjacencies(node,node->getFirstChild(),indexOfSecondChildTriangle);
            updateAdjacencies(node,node->getSecondChild(),indexOfFirstChildTriangle);

            legalizeEdge(node->getFirstChild());
            legalizeEdge(node->getSecondChild());
        }
    }

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
                newPoint,
                _delauneyTriangles[currentNode->getTriangleIndex()].getV1(),
                _delauneyTriangles[currentNode->getTriangleIndex()].getV2(), true);
    Triangle delta2 = *new Triangle(
                newPoint,
                _delauneyTriangles[currentNode->getTriangleIndex()].getV1(),
                _delauneyTriangles[currentNode->getTriangleIndex()].getV3(), true);
    Triangle delta3 = *new Triangle(
                newPoint,
                _delauneyTriangles[currentNode->getTriangleIndex()].getV2(),
                _delauneyTriangles[currentNode->getTriangleIndex()].getV3(), true);

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

            legalizeEdge (check->getFirstChild());
            legalizeEdge (check->getSecondChild());
            legalizeEdge (check->getThirdChild());

            found = true;
        }else{
            check = getChildContainsPoint(check,newPoint);
        }
    }
}
