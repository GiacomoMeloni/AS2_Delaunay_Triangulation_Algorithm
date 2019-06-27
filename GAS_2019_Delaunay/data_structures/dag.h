#ifndef DAG_H
#define DAG_H

#include <cg3/geometry/2d/point2d.h>
#include "triangle.h"

class DAG
{
    public:
        DAG();
        DAG(const unsigned int indexTriangle);

        inline void addChild(unsigned int indexNewTriangle){
            if (!checkSizeOfChildrens()){
                this->_indexChildrens.push_back(indexNewTriangle);
            }
        }

        inline bool checkSizeOfChildrens (){
            return (this->_indexChildrens.size()>=3) ? false : true;
        }

        inline bool gotChildrens (){
            return (_indexChildrens.size()>0) ? true : false;
        }

        inline unsigned int getTriangleIndex(){
            return this->_indexTriangle;
        }

        inline std::vector<unsigned int> getChildrensIndex(){
            return this->_indexChildrens;
        }

        inline unsigned int getDAGNodeIndex(){
            return this->_indexNode;
        }

    protected:
        unsigned int _indexTriangle;
        std::vector<unsigned int> _indexChildrens;
        unsigned int _indexNode;
};

#endif // DAG_H
