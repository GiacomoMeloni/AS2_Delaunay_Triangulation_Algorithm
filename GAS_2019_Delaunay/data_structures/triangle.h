#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cg3/geometry/2d/point2d.h>

class Triangle
{

    public:
        inline Triangle();
        inline Triangle (const cg3::Point2Dd& v1,const cg3::Point2Dd& v2,const cg3::Point2Dd& v3);

        inline const cg3::Point2Dd getV1() const;
        inline const cg3::Point2Dd getV2() const;
        inline const cg3::Point2Dd getV3() const;
        inline const std::vector<cg3::Point2Dd> getVertices() const;
        inline std::vector<std::pair <cg3::Point2Dd, cg3::Point2Dd>> getEdges() const;

        inline void setV1(cg3::Point2Dd v1);
        inline void setV2(cg3::Point2Dd v2);
        inline void setV3(cg3::Point2Dd v3);
        inline void setVertices(cg3::Point2Dd v1, cg3::Point2Dd v2, cg3::Point2Dd v3);

        inline bool checkOrientationCounterclockwise(const cg3::Point2Dd& v1,const cg3::Point2Dd& v2,const cg3::Point2Dd& v3);
        inline void orderingCounterClockwise();

    protected:
        cg3::Point2Dd _v1;
        cg3::Point2Dd _v2;
        cg3::Point2Dd _v3;

};

#endif // TRIANGLE_H
