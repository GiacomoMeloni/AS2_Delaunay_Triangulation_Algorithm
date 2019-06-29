#include "delauneytriangulation.h"

DelauneyTriangulation::DelauneyTriangulation()
{

}

DelauneyTriangulation::DelauneyTriangulation(Triangle boundingTriangle){
    this->triangles.push_back(boundingTriangle);
    this->dag.push_back(*new DAG(triangles.size()-1));
    this->points.push_back(boundingTriangle.getV1());
    this->points.push_back(boundingTriangle.getV2());
    this->points.push_back(boundingTriangle.getV3());
}

unsigned long DelauneyTriangulation::findPointPosition(cg3::Point2Dd newPoint){
    bool found = false;
    unsigned long i = 0;
    while (found == false){
        if (dag[i].isALeaf()){
            found = true;
            //check first children
        }else if (cg3::isPointLyingInTriangle(
                      this->triangles[dag[i].getChildrensIndex()[0]].getV1(),
                      this->triangles[dag[i].getChildrensIndex()[0]].getV2(),
                      this->triangles[dag[i].getChildrensIndex()[0]].getV3(),
                      newPoint,true)){
            i = dag[i].getChildrensIndex()[0];
            //check second children
        }else if (cg3::isPointLyingInTriangle(
                      this->triangles[dag[i].getChildrensIndex()[1]].getV1(),
                      this->triangles[dag[i].getChildrensIndex()[1]].getV2(),
                      this->triangles[dag[i].getChildrensIndex()[1]].getV3(),
                      newPoint,true)){
            i = dag[i].getChildrensIndex()[1];
            //check third children
        }else if (cg3::isPointLyingInTriangle(
                      this->triangles[dag[i].getChildrensIndex()[2]].getV1(),
                      this->triangles[dag[i].getChildrensIndex()[2]].getV2(),
                      this->triangles[dag[i].getChildrensIndex()[2]].getV3(),
                      newPoint,true)){
            i = dag[i].getChildrensIndex()[2];
        }
    }
    return i;
}

void DelauneyTriangulation::addPoint(cg3::Point2Dd newPoint){
    this->points.push_back(newPoint);

    unsigned long nodeIndex = findPointPosition(newPoint);

    //Split the current triangle
    Triangle firstSplit(
                newPoint,
                triangles[dag[nodeIndex].getTriangleIndex()].getV1(),
                triangles[dag[nodeIndex].getTriangleIndex()].getV2());
    this->triangles.push_back(firstSplit);
    this->dag.push_back(*new DAG(triangles.size()-1));
    this->dag[nodeIndex].addChild(dag.size()-1);

    //Split the current triangle
    Triangle secondSplit(
                newPoint,
                triangles[dag[nodeIndex].getTriangleIndex()].getV1(),
                triangles[dag[nodeIndex].getTriangleIndex()].getV3());
    this->triangles.push_back(secondSplit);
    this->dag.push_back(*new DAG(triangles.size()-1));
    this->dag[nodeIndex].addChild(dag.size()-1);

    //Split the current triangle
    Triangle thirdSplit(
                newPoint,
                triangles[dag[nodeIndex].getTriangleIndex()].getV2(),
                triangles[dag[nodeIndex].getTriangleIndex()].getV3());
    this->triangles.push_back(thirdSplit);
    this->dag.push_back(*new DAG(triangles.size()-1));
    this->dag[nodeIndex].addChild(dag.size()-1);
}
