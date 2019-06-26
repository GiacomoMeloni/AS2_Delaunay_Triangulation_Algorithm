#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cg3/geometry/2d/point2d.h>

class Triangle
{

    public:
        Triangle();
        Triangle (const cg3::Point2Dd& v1,const cg3::Point2Dd& v2,const cg3::Point2Dd& v3);

        inline const cg3::Point2Dd getV1() const {
            return this->_v1;
        }
        inline const cg3::Point2Dd getV2() const {
            return this->_v2;
        }
        inline const cg3::Point2Dd getV3() const {
            return this->_v3;
        }
        inline const std::vector<cg3::Point2Dd> getVertices() const {
            std::vector<cg3::Point2Dd> vertices;

            vertices.push_back(this->_v1);
            vertices.push_back(this->_v2);
            vertices.push_back(this->_v3);
            return vertices;
        }

        inline int getIndex() const {
            return this->index;
        }

        inline void setV1(cg3::Point2Dd v1){
            this->_v1 = v1;
        }
        inline void setV2(cg3::Point2Dd v2){
            this->_v2 = v2;
        }
        inline void setV3(cg3::Point2Dd v3){
            this->_v3 = v3;
        }
        inline void setVertices(cg3::Point2Dd v1, cg3::Point2Dd v2, cg3::Point2Dd v3){
            this->_v1 = v1;
            this->_v2 = v2;
            this->_v3 = v3;
        }

        inline std::vector<std::pair <cg3::Point2Dd, cg3::Point2Dd>> getEdges(){
            std::vector<std::pair <cg3::Point2Dd, cg3::Point2Dd>> edges;

            edges.push_back( std::make_pair(this->_v1,this->_v2));
            edges.push_back( std::make_pair(this->_v1,this->_v3));
            edges.push_back( std::make_pair(this->_v2,this->_v3));

            return edges;
        }

        void checkOrientationCounterclockwise(cg3::Point2Dd& v1, cg3::Point2Dd& v2, cg3::Point2Dd& v3);

        inline void orderingCounterClockwise(){
            cg3::Point2Dd temp;
            temp = this->_v2;
            this->_v2 = this->_v3;
            this->_v3 = temp;
        }

    protected:
        cg3::Point2Dd _v1;
        cg3::Point2Dd _v2;
        cg3::Point2Dd _v3;

        bool checked;
        unsigned int index;

};

#endif // TRIANGLE_H
