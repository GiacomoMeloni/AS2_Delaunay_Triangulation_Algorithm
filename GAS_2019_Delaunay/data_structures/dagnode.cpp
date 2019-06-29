#include "dagnode.h"

DagNode* DagNode::getChildContainsPoint(const cg3::Point2Dd &point){
    for (DagNode *node : getChildrens()){
        if (cg3::isPointLyingInTriangle(
                    node->getTriangle().getV1(),
                    node->getTriangle().getV2(),
                    node->getTriangle().getV2(),
                    point,true)){
            return node;
        }else {
            return nullptr;
        }
    }
}
