#include "dag.h"

DAG::DAG()
{

}

DAG::DAG(const int indexTriangle)
{
    this->_indexTriangle = indexTriangle;
    this->_indexChildrens = {};
    this->_indexNode = 0;
}

