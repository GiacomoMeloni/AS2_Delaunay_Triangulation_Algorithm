#include "drawablevoronoidiagram.h"

/**
 * @brief draw points and edges, taking in consideration all the dag nodes that are leaves.
 * taking into account all nodes adjacent to the current node. The circumcentres of the triangles are calculated.
 * Using these data points and edges are drawn.
 */
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
