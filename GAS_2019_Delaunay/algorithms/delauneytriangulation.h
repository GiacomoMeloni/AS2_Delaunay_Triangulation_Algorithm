#ifndef DELAUNEYTRIANGULATION_H
#define DELAUNEYTRIANGULATION_H

#include "../data_structures/triangle.h"
#include "../data_structures/dag.h"
#include <cg3/geometry/2d/point2d.h>



class DelauneyTriangulation
{
    public:
        DelauneyTriangulation();
        DelauneyTriangulation(Triangle boundingTriangle){
            this->triangles.push_back(boundingTriangle);
            DAG* root = new DAG(boundingTriangle.getIndex());
            this->dag.push_back(*root);
            delete(root);
        }

    protected:
        std::vector<Triangle> triangles;
        std::vector<DAG> dag;
};

#endif // DELAUNEYTRIANGULATION_H
