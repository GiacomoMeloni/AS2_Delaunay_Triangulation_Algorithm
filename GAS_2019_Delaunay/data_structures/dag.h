#ifndef DAG_H
#define DAG_H

#include <cg3/geometry/2d/point2d.h>
#include "triangle.h"

class DAG
{
    public:
        DAG();
        DAG(const unsigned long indexTriangle);

        inline void addChild(unsigned long indexNewTriangle){
            if (!checkSizeOfChildrens()){
                this->_indexChildrens.push_back(indexNewTriangle);
            }
        }

        inline bool checkSizeOfChildrens (){
            return (this->_indexChildrens.size()>=3) ? false : true;
        }

        inline bool isALeaf (){
            return (_indexChildrens.size()==0) ? true : false;
        }

        inline unsigned long getTriangleIndex(){
            return this->_indexTriangle;
        }

        inline std::vector<unsigned long> getChildrensIndex(){
            return this->_indexChildrens;
        }

        inline unsigned long getDAGNodeIndex(){
            return this->_indexNode;
        }

    protected:
        unsigned long _indexTriangle;
        std::vector<unsigned long> _indexChildrens;
        unsigned long _indexNode;
};

#endif // DAG_H
