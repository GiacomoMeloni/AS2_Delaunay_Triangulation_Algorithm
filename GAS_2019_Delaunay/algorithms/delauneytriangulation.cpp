#include "delauneytriangulation.h"

std::vector<Triangle> DelauneyTriangulation::makeTriangles(DagNode* currentNode, const cg3::Point2Dd &newPoint){
    std::vector<Triangle> newTriangles;

    Triangle delta1 = *new Triangle(
                currentNode->getTriangle().getV1(),
                currentNode->getTriangle().getV2(),
                newPoint);
    newTriangles.push_back(delta1);
    Triangle delta2 = *new Triangle(
                currentNode->getTriangle().getV1(),
                currentNode->getTriangle().getV3(),
                newPoint);
    newTriangles.push_back(delta2);
    Triangle delta3 = *new Triangle(
                currentNode->getTriangle().getV2(),
                currentNode->getTriangle().getV3(),
                newPoint);
    newTriangles.push_back(delta3);

    return newTriangles;
}

void DelauneyTriangulation::makeSplit(DagNode *currentNode, std::vector<Triangle> &newTriangles){

    for (Triangle &newTriangle : newTriangles){
        currentNode->addChild(new DagNode(newTriangle));
        this->_delauneyTriangles.push_back(newTriangle);
    }
}

void DelauneyTriangulation::addPointToTriangulation(const cg3::Point2Dd &newPoint){
    bool found= false;
    DagNode* check = getDAG();
    addPointToList(newPoint);

    while (found == false){
        if (check->isALeaf() /*&& check->isPointInTriangle(newPoint)*/){
            std::vector<Triangle> newTriangles = makeTriangles(check, newPoint);
            makeSplit(check, newTriangles);
            found = true;
        }else{
            check = check->getChildContainsPoint(newPoint);
        }
    }
}
