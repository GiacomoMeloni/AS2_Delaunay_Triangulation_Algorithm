#include "delaunaytriangulation.h"

/**
 * @brief getOppositePoint get the point opposite the triangle under consideration.
 * @param currentTriangle is the pointer to the node under consideration.
 * @param adjacentTriangle is the pointer to the node adjacent to currentTriangle.
 * @return the point opposite the triangle under consideration.
 */
cg3::Point2Dd DelaunayTriangulation::getOppositePoint(const Triangle &currentTriangle,const Triangle &adjacentTriangle){
    cg3::Point2Dd opposite;
    for (cg3::Point2Dd vertexAdjacentTriangle : adjacentTriangle.getVertices()){
        bool found = false;
        for (cg3::Point2Dd vertexCurrentTriangle : currentTriangle.getVertices()){
            if (vertexCurrentTriangle == vertexAdjacentTriangle)
                found = true;
        }
        if(!found)
            opposite = vertexAdjacentTriangle;
    }
    return opposite;
}

/**
 * @brief updateAdjacencies is used in the incremental step, in makeSplits, to update the adjacencies of the triangles
 * generated by the insertion of the new point.
 * Given the pointer to the father, all its adjacencies are taken. Once an adjacency is found, the update process is stopped.
 * At the end the brothers of the created node are inserted between the adjacencies.
 * @param father is the pointer to the node that has been splitted.
 * @param child is the pointer to one of the node that was created before to which adjacencies will be updated.
 * @param nodeOfFirstBrother is the pointer to one of the brothers generated before.
 * @param nodeOfSecondBrother is the pointer to one of the brothers generated before.
 */
void DelaunayTriangulation::updateAdjacencies(DagNode* father, DagNode* child, DagNode* nodeOfFirstBrother, DagNode* nodeOfSecondBrother){
    if (!father->getAdjacencies().empty()){
        for (DagNode* &node : father->getAdjacencies()){
            if (_delauneyTriangles[node->getTriangleIndex()].isAdjacent(_delauneyTriangles[child->getTriangleIndex()])){
                child->addAdjacencies(node);
                break;
            }
        }
    }
    child->addAdjacencies(nodeOfFirstBrother);
    child->addAdjacencies(nodeOfSecondBrother);
}

/**
 * @brief updateAdjacenciesOnEdgeFlip is used in legalizeEdge to update the adjacencies of the triangles generated due to the edge flip.
 * Considering that the triangles generated in the edge flip, share two different fathers, they can inherit the adjacencies from one of them.
 * Naturally also the adjacencies of the triangles adjacent to the father are updated with the new nodes created.
 * @param father_1 is the pointer to one of the node that was involved in the edge flip.
 * @param father_2 is the pointer to one of the node that was involved in the edge flip.
 * @param child is the pointer to one of the nodes created by the edge flip and to which adjacencies will be updated.
 * @param brotherNode is the pointer to the other node created by the edge flip.
 */
void DelaunayTriangulation::updateAdjacenciesOnEdgeFlip(DagNode* father_1, DagNode* father_2, DagNode* child, DagNode* brotherNode){
    if (!father_1->getAdjacencies().empty()){
        for (DagNode* node : father_1->getAdjacencies()){
            if (node != father_2){
                if (_delauneyTriangles[node->getTriangleIndex()].isAdjacent(_delauneyTriangles[child->getTriangleIndex()])){
                    child->addAdjacencies(node);
                    node->changeAdjacencies(father_1,child);
                    break;
                }
            }
        }
    }
    if (!father_2->getAdjacencies().empty()){
        for (DagNode* node : father_2->getAdjacencies()){
            if (node != father_1){
                if (_delauneyTriangles[node->getTriangleIndex()].isAdjacent(_delauneyTriangles[child->getTriangleIndex()])){
                    child->addAdjacencies(node);
                    node->changeAdjacencies(father_2,child);
                    break;
                }
            }
        }
    }
    child->addAdjacencies(brotherNode);
}

/**
 * @brief updateAdjacenciesOnBrothers is used in the incremental step, in the makeSplits function, to update the adjacencies of the triangles
 * that were adiacent to the split node.
 * @param adjacent is the pointer to the node that was adjacent to the one splitted.
 * @param splittedBrother is the pointer to the splitted node.
 */
void DelaunayTriangulation::updateAdjacenciesOnBrothers(DagNode* adjacent, DagNode* splittedBrother){
    for (DagNode* children : splittedBrother->getChildrens()){
        if (_delauneyTriangles[children->getTriangleIndex()].isAdjacent(_delauneyTriangles[adjacent->getTriangleIndex()])){
            adjacent->changeAdjacencies(splittedBrother,children);
            break;
        }
    }
}

/**
 * @brief legalizeEdge has the task of managing illegal edges, the node to be checked is given in input together with a support parameter that corresponds
 * to the smallest index among the brothers of the node to be controlled (this to avoid unnecessary checks).
 * Considering the adjacent triangle, once its opposite point is found, it checks if this point is inside the vertex of the triangle created with the new point
 * (the new point of the triangulation is always inserted as v1).
 * If it is inside, then it is considered as an illegal edge, two triangles are created and all the structures are updated, considering that this time the
 * children due to edge flip will be shared by both the current node (node) and its adjacent (adjacentNode).
 * Once everything is updated, the recursive call is made on both children generated by the edge flip.
 * @param node the pointer to the node that store the triangle's index created before.
 * @param lowerBrotherIndex support parameter to avoid to check the brothers of the triangles created.
 */
void DelaunayTriangulation::legalizeEdge(DagNode* node, size_t lowerBrotherIndex){
    cg3::Point2Dd oppositePoint;

    for (DagNode* adjacentNode : node->getAdjacencies()){
        if(adjacentNode->getTriangleIndex() < lowerBrotherIndex){
            oppositePoint = getOppositePoint(_delauneyTriangles[node->getTriangleIndex()],_delauneyTriangles[adjacentNode->getTriangleIndex()]);

            if(cg3::isPointLyingInCircle(
                        _delauneyTriangles[node->getTriangleIndex()].getV1(),
                        _delauneyTriangles[node->getTriangleIndex()].getV2(),
                        _delauneyTriangles[node->getTriangleIndex()].getV3(),
                        oppositePoint, true)){

                _delauneyTriangles[node->getTriangleIndex()].setIsALeaf(false);
                _delauneyTriangles[adjacentNode->getTriangleIndex()].setIsALeaf(false);

                Triangle delta1 = Triangle(
                            _delauneyTriangles[node->getTriangleIndex()].getV1(),
                            _delauneyTriangles[node->getTriangleIndex()].getV3(),
                            oppositePoint,true);
                Triangle delta2 = Triangle(
                            _delauneyTriangles[node->getTriangleIndex()].getV1(),
                            _delauneyTriangles[node->getTriangleIndex()].getV2(),
                            oppositePoint,true);

                this->_delauneyTriangles.push_back(delta1);
                size_t indexOfFirstChildTriangle = _delauneyTriangles.size()-1;
                DagNode* firstChild = new DagNode (indexOfFirstChildTriangle);
                node->addChild(firstChild);
                adjacentNode->addChild(firstChild);

                this->_delauneyTriangles.push_back(delta2);
                size_t indexOfSecondChildTriangle = _delauneyTriangles.size()-1;
                DagNode* secondChild = new DagNode (indexOfSecondChildTriangle);
                node->addChild(secondChild);
                adjacentNode->addChild(secondChild);

                /*The procedure to update the adjacences of the new nodes generated in the edge flip
                 * is diffirente from the updates used in the incremental step (makeSplits)*/
                updateAdjacenciesOnEdgeFlip(node, adjacentNode,node->getFirstChild(),node->getSecondChild());
                updateAdjacenciesOnEdgeFlip(node, adjacentNode,node->getSecondChild(),node->getFirstChild());

                this->_allNodeCollection.push_back(node->getFirstChild());
                this->_allNodeCollection.push_back(node->getSecondChild());

                size_t referenceBrothersIndex = node->getTheLowerTriangleIndexFromChildrens();

                legalizeEdge(node->getFirstChild(),referenceBrothersIndex);
                legalizeEdge(node->getSecondChild(),referenceBrothersIndex);
            }
        }
    }
}

/**
 * @brief getChildContainsPoint, given the current node and the new point to be inserted in the triangulation, return the children that cointains the point.
 * scrolling through the list of children, it is checked which contains the node and is then returned.
 * @param currentNode the pointer to the node that store the triangle's index that contains the new point
 * @param newPoint the reference of the new point to insert in the triangulation
 * @return the next pointer of the DAG structure that contains the point
 */
DagNode* DelaunayTriangulation::getChildContainsPoint(DagNode* &currentNode, const cg3::Point2Dd &point){
    for (DagNode *node : currentNode->getChildrens()){
        if (cg3::isPointLyingInTriangle(
                    this->_delauneyTriangles[node->getTriangleIndex()].getV1(),
                    this->_delauneyTriangles[node->getTriangleIndex()].getV2(),
                    this->_delauneyTriangles[node->getTriangleIndex()].getV3(),
                    point,true)){
            return node;
        }
    }
    return nullptr;
}

/**
 * @brief makeSplits manages, given the current node and the new point to be inserted in the triangulation, the incremental step.
 * Create three triangles using the new point and the vertices of the triangle to which the node refers.
 * Once created, the triangles are inserted into the vector of triangles and the three relative nodes are created in the structure of the DAG.
 * Once the structures are updated, the adjacencies of each new triangle are also updated, and the adjacencies of the split triangle are updated too.
 * @param currentNode the pointer to the node that store the triangle's index that contains the new point
 * @param newPoint the reference of the new point to insert in the triangulation
 */
void DelaunayTriangulation::makeSplits(DagNode* currentNode, const cg3::Point2Dd &newPoint){
    Triangle delta1 = Triangle(
                newPoint,
                _delauneyTriangles[currentNode->getTriangleIndex()].getV1(),
                _delauneyTriangles[currentNode->getTriangleIndex()].getV2(), true);
    Triangle delta2 = Triangle(
                newPoint,
                _delauneyTriangles[currentNode->getTriangleIndex()].getV1(),
                _delauneyTriangles[currentNode->getTriangleIndex()].getV3(), true);
    Triangle delta3 = Triangle(
                newPoint,
                _delauneyTriangles[currentNode->getTriangleIndex()].getV2(),
                _delauneyTriangles[currentNode->getTriangleIndex()].getV3(), true);

    this->_delauneyTriangles.push_back(delta1);
    size_t indexOfFirstChildTriangle = _delauneyTriangles.size()-1;
    currentNode->addChild(new DagNode(indexOfFirstChildTriangle));

    this->_delauneyTriangles.push_back(delta2);
    size_t indexOfSecondChildTriangle = _delauneyTriangles.size()-1;
    currentNode->addChild(new DagNode(indexOfSecondChildTriangle));

    this->_delauneyTriangles.push_back(delta3);
    size_t indexOfThirdChildTriangle = _delauneyTriangles.size()-1;
    currentNode->addChild(new DagNode(indexOfThirdChildTriangle));

    updateAdjacencies(currentNode,currentNode->getFirstChild(),currentNode->getSecondChild(),currentNode->getThirdChild());
    updateAdjacencies(currentNode,currentNode->getSecondChild(),currentNode->getFirstChild(),currentNode->getThirdChild());
    updateAdjacencies(currentNode,currentNode->getThirdChild(),currentNode->getFirstChild(),currentNode->getSecondChild());

    /*All new children created by the current node are added to the node list.*/
    this->_allNodeCollection.push_back(currentNode->getFirstChild());
    this->_allNodeCollection.push_back(currentNode->getSecondChild());
    this->_allNodeCollection.push_back(currentNode->getThirdChild());

    /*In the case of the bounding triangle there is no need to update any adjacency lists*/
    if (!currentNode->getAdjacencies().empty()){
        for (DagNode* adjacentNode : currentNode->getAdjacencies()){
            updateAdjacenciesOnBrothers(adjacentNode,currentNode);
        }
    }
}

/**
 * @brief addPointToTriangulation is the method that permit to add a point in triangulation and calls
 * all the related method in order to correctly manage the insertion process.
 * Given a point, the function searches in which node of the lying. Once arrived at a leaf (the node containing the point), the leaf flag of the corresponding triangle is setted to false.
 * The split function (makeSplits) is called in order to manage the incremental step of the algorithm.
 * Once the children are created, the legalizeEdge function is called on each of them.
 * At the end it will have updated our structure with the addition of the input point provided.
 * @param newPoint - the reference of the newPoint to add to the triangulation
 */
void DelaunayTriangulation::addPointToTriangulation(const cg3::Point2Dd &newPoint){
    bool found= false;
    DagNode* check = getDAG();

    while (found == false){
        if (check->isALeaf()){
            _delauneyTriangles[check->getTriangleIndex()].setIsALeaf(false);
            makeSplits(check, newPoint);

            /*referenceBrothersIndex is used to avoid checking brothers of newly created triangles
             * as adjacencies in the legalizeEdge function*/

            size_t referenceBrothersIndex = check->getTheLowerTriangleIndexFromChildrens();

            /*Here we check before sending the function legalize if the newly created triangles
             * have more than two adjacencies (so they have different adjacencies beyond the brothers).
             * If the brothers are alone as adjacent then it is useless to enter the legalizeEdge function.*/

            if (check->getFirstChild()->getAdjacencies().size()>2)
                legalizeEdge (check->getFirstChild(),referenceBrothersIndex);

            if (check->getSecondChild()->getAdjacencies().size()>2)
                legalizeEdge (check->getSecondChild(), referenceBrothersIndex);

            if (check->getThirdChild()->getAdjacencies().size()>2)
                legalizeEdge (check->getThirdChild(), referenceBrothersIndex);

            found = true;
        }else{
            /*getChildContainsPoint consente di restituire il puntatore al nodo successivo nella struttura
             * che contiene il punto*/
            check = getChildContainsPoint(check,newPoint);
        }
    }
}
