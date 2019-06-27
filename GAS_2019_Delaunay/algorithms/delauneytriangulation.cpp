#include "delauneytriangulation.h"

DelauneyTriangulation::DelauneyTriangulation()
{

}

DelauneyTriangulation::DelauneyTriangulation(Triangle boundingTriangle){
    this->triangles.push_back(boundingTriangle);
    this->dag.push_back(*new DAG(boundingTriangle.getIndex()));
}

unsigned int DelauneyTriangulation::findPointPosition(cg3::Point2Dd newPoint){
    bool found = false;
    int i = 0;
    while (found == false){
        if (!dag[i].gotChildrens()){
            found = true;
        }else if ()
    }
    return i;
}

void DelauneyTriangulation::addPoint(cg3::Point2Dd newPoint){
    unsigned int nodeIndex = findPointPosition(newPoint);
}
