#ifndef DAG_H
#define DAG_H

#include <cg3/geometry/2d/point2d.h>
#include "triangle.h"

class DAG
{
    public:
        DAG();
        DAG(const int indexTriangle);

        inline void addChild(int indexNewTriangle){
            this->_indexChildrens.push_back(indexNewTriangle);
        }

        inline bool checkSizeOfChildrens (){
            return (this->_indexChildrens.size()>=3) ? false : true;
        }

    protected:
        int _indexTriangle;
        std::vector<int> _indexChildrens;
        int _indexNode;

};

#endif // DAG_H
