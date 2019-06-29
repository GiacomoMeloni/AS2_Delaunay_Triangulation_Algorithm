#ifndef DELAUNEYTRIANGULATION_H
#define DELAUNEYTRIANGULATION_H

#include "../data_structures/triangle.h"
#include "../data_structures/dagnode.h"
#include <cg3/geometry/2d/point2d.h>
#include <cg3/geometry/2d/utils2d.h>



class DelauneyTriangulation
{
    public:
        inline DelauneyTriangulation();
        inline DelauneyTriangulation(const Triangle &boundingTriangle);

        inline const std::vector<Triangle> getTriangles() const;
        inline DagNode* getDAG() const;
        inline const std::vector<cg3::Point2Dd> getPoints();
        inline void addPointToList(const cg3::Point2Dd &newPoint);

        std::vector<Triangle> makeTriangles(DagNode* currentNode, const cg3::Point2Dd &newPoint);
        void makeSplit (DagNode* currentNode, std::vector<Triangle> &newTriangles);
        void addPointToTriangulation (const cg3::Point2Dd &newPoint);

    protected:
        std::vector<Triangle> _delauneyTriangles;
        DagNode* _dag;
        std::vector<cg3::Point2Dd> _points;
};

#endif // DELAUNEYTRIANGULATION_H
