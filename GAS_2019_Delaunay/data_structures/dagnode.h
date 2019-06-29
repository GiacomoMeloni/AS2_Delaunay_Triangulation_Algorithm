#ifndef DAG_H
#define DAG_H

#include <cg3/geometry/2d/point2d.h>
#include "triangle.h"
#include <cg3/geometry/2d/utils2d.h>

class DagNode
{
    public:

        /* --- Constructor --- */
        inline DagNode();
        inline DagNode(const Triangle &triangle);

        /* --- Getter --- */
        inline Triangle getTriangle() const;
        inline std::vector<DagNode*> getChildrens() const;
        DagNode* getChildContainsPoint(const cg3::Point2Dd &point);

        /* --- Setter --- */
        inline void addChild(DagNode* newNode);

        /* --- Methods --- */
        inline bool checkNumberOfChildrens() const;
        inline bool isALeaf() const;
        inline bool isPointInTriangle(const cg3::Point2Dd &point) const;


    protected:
        Triangle _triangle;
        std::vector<DagNode*> _childrens;
};

#endif // DAG_H
