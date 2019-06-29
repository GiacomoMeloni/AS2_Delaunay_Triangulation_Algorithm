#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cg3/geometry/2d/point2d.h>

/**
 * @brief Class representing a 2D Triangle. The triangle is rappresented by three vertices.
 * The vertices order is counter-clockwise.
 */

class Triangle
{

    public:
        /* --- Constructor --- */
        inline Triangle();
        inline Triangle (const cg3::Point2Dd& v1,const cg3::Point2Dd& v2,const cg3::Point2Dd& v3);

        /* --- Getters --- */
        inline const cg3::Point2Dd getV1() const;
        inline const cg3::Point2Dd getV2() const;
        inline const cg3::Point2Dd getV3() const;
        inline const std::vector<cg3::Point2Dd> getVertices() const;
        inline std::vector<std::pair <cg3::Point2Dd, cg3::Point2Dd>> getEdges() const;

        /* --- Setters --- */
        inline void setV1(const cg3::Point2Dd &v);
        inline void setV2(const cg3::Point2Dd &v);
        inline void setV3(const cg3::Point2Dd &v);
        inline void setVertices(const cg3::Point2Dd &v1, const cg3::Point2Dd &v2, const cg3::Point2Dd &v3);

        /* --- Methods --- */
        inline bool checkOrientationCounterclockwise(const cg3::Point2Dd& v1,const cg3::Point2Dd& v2,const cg3::Point2Dd& v3) const;
        inline void orderingCounterClockwise();

    protected:
        cg3::Point2Dd _v1;
        cg3::Point2Dd _v2;
        cg3::Point2Dd _v3;

};

#endif // TRIANGLE_H
