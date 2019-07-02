#include "delauneytriangulation.h"

cg3::Point2Dd DelauneyTriangulation::getOppositePoint(const Triangle &currentTriangle,const Triangle &adjacentTriangle){
    for (cg3::Point2Dd vertexAdjacentTriangle : adjacentTriangle.getVertices()){
        bool found = false;
        for (cg3::Point2Dd vertexCurrentTriangle : currentTriangle.getVertices()){
            if (vertexCurrentTriangle == vertexAdjacentTriangle)
                found = true;
        }
        if(!found)
            return vertexAdjacentTriangle;
    }
    return cg3::Point2Dd(0,0);
}

void DelauneyTriangulation::updateAdjacencies(DagNode* father, DagNode* child, DagNode* nodeOfFirstBrother, DagNode* nodeOfSecondBrother){
    if (!father->getAdjacencies().empty()){
        for (DagNode* &node : father->getAdjacencies()){
            if (_delauneyTriangles[node->getTriangleIndex()].isAdjacent(_delauneyTriangles[child->getTriangleIndex()])){
                child->addAdjacencies(node);
                break;
            }
        }
    }
    child->addAdjacencies(nodeOfFirstBrother);
    child->addAdjacencies(nodeOfSecondBrother);
}

void DelauneyTriangulation::updateAdjacenciesOnEdgeFlip(DagNode* father_1, DagNode* father_2, DagNode* child, DagNode* brotherNode){
    if (!father_1->getAdjacencies().empty()){
        for (DagNode* node : father_1->getAdjacencies()){
            if (_delauneyTriangles[node->getTriangleIndex()].isAdjacent(_delauneyTriangles[child->getTriangleIndex()])){
                child->addAdjacencies(node);
                break;
            }
        }
    }
    if (!father_2->getAdjacencies().empty()){
        for (DagNode* node : father_2->getAdjacencies()){
            if (_delauneyTriangles[node->getTriangleIndex()].isAdjacent(_delauneyTriangles[child->getTriangleIndex()])){
                child->addAdjacencies(node);
                break;
            }
        }
    }
    child->addAdjacencies(brotherNode);
}


void DelauneyTriangulation::legalizeEdge(DagNode* node){
    cg3::Point2Dd oppositePoint;

    for (DagNode* adjacentNode : node->getAdjacencies()){
        oppositePoint = getOppositePoint(_delauneyTriangles[node->getTriangleIndex()],_delauneyTriangles[adjacentNode->getTriangleIndex()]);

        if(cg3::isPointLyingInCircle(
                    _delauneyTriangles[node->getTriangleIndex()].getV1(),
                    _delauneyTriangles[node->getTriangleIndex()].getV2(),
                    _delauneyTriangles[node->getTriangleIndex()].getV3(),
                    oppositePoint, true)){

            _delauneyTriangles[node->getTriangleIndex()].setIsALeaf(false);
            _delauneyTriangles[adjacentNode->getTriangleIndex()].setIsALeaf(false);

            Triangle delta1 = Triangle(
                        _delauneyTriangles[node->getTriangleIndex()].getV1(),
                        _delauneyTriangles[node->getTriangleIndex()].getV3(),
                        oppositePoint,true);
            Triangle delta2 = Triangle(
                        _delauneyTriangles[node->getTriangleIndex()].getV1(),
                        _delauneyTriangles[node->getTriangleIndex()].getV2(),
                        oppositePoint,true);

            this->_delauneyTriangles.push_back(delta1);
            size_t indexOfFirstChildTriangle = _delauneyTriangles.size()-1;
            DagNode* firstChild = new DagNode (indexOfFirstChildTriangle);
            node->addChild(firstChild);
            adjacentNode->addChild(firstChild);

            this->_delauneyTriangles.push_back(delta2);
            size_t indexOfSecondChildTriangle = _delauneyTriangles.size()-1;
            DagNode* secondChild = new DagNode (indexOfSecondChildTriangle);
            node->addChild(secondChild);
            adjacentNode->addChild(secondChild);

            updateAdjacenciesOnEdgeFlip(node, adjacentNode,node->getFirstChild(),node->getSecondChild());
            updateAdjacenciesOnEdgeFlip(node, adjacentNode,node->getSecondChild(),node->getFirstChild());

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
    Triangle delta1 = Triangle(
                newPoint,
                _delauneyTriangles[currentNode->getTriangleIndex()].getV1(),
                _delauneyTriangles[currentNode->getTriangleIndex()].getV2(), true);
    Triangle delta2 = Triangle(
                newPoint,
                _delauneyTriangles[currentNode->getTriangleIndex()].getV1(),
                _delauneyTriangles[currentNode->getTriangleIndex()].getV3(), true);
    Triangle delta3 = Triangle(
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

    updateAdjacencies(currentNode,currentNode->getFirstChild(),currentNode->getSecondChild(),currentNode->getThirdChild());
    updateAdjacencies(currentNode,currentNode->getSecondChild(),currentNode->getFirstChild(),currentNode->getThirdChild());
    updateAdjacencies(currentNode,currentNode->getThirdChild(),currentNode->getFirstChild(),currentNode->getSecondChild());
    for (DagNode* adjacentNode : currentNode->getAdjacencies()){
    }
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
