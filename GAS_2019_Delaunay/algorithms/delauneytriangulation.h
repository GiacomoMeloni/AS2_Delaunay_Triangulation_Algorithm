#ifndef DELAUNEYTRIANGULATION_H
#define DELAUNEYTRIANGULATION_H

#include "../data_structures/triangle.h"
#include "../data_structures/dagnode.h"
#include <cg3/geometry/2d/point2d.h>
#include <cg3/geometry/2d/utils2d.h>



class DelauneyTriangulation
{
    public:
        DelauneyTriangulation();
        DelauneyTriangulation(Triangle boundingTriangle);
        void addPoint (cg3::Point2Dd newPoint);
        unsigned long findPointPosition(cg3::Point2Dd newPoint);

        inline std::vector<cg3::Point2Dd> getPoints() {
            return this->points;
        }

    protected:
        std::vector<Triangle> triangles;
        std::vector<DAG> dag;
        std::vector<cg3::Point2Dd> points;
//        std::vector<cg3::Point2Dd> points;
};

#endif // DELAUNEYTRIANGULATION_H
