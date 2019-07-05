#include "drawablevoronoidiagram.h"

void DrawableVoronoiDiagram::draw() const
{
    for (DagNode* node : *_allDagNodes){
        if(node->isALeaf()){
            for (DagNode* adjacent : node->getAdjacencies())
            {
                cg3::viewer::drawLine2D(
                            (*_triangles)[node->getTriangleIndex()].getCircleCenter(),
                            (*_triangles)[adjacent->getTriangleIndex()].getCircleCenter(),
                            edgeColor, edgeWidth);
                cg3::viewer::drawPoint2D((*_triangles)[node->getTriangleIndex()].getCircleCenter(), pointColor, pointSize);
                cg3::viewer::drawPoint2D((*_triangles)[adjacent->getTriangleIndex()].getCircleCenter(), pointColor, pointSize);
            }
        }
    }

}
