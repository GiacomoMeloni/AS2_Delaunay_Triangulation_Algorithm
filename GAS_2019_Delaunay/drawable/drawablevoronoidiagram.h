#ifndef DRAWABLEVORONOIDIAGRAM_H
#define DRAWABLEVORONOIDIAGRAM_H

#include <cg3/utilities/color.h>
#include "cg3/viewer/interfaces/drawable_object.h"
#include "cg3/viewer/renderable_objects/2d/renderable_objects2d.h"
#include "../algorithms/delaunaytriangulationalgorithm.h"

/**
 * @brief Class representing the drawable voronoi diagram. This class inherit to cg3::DrawableObject.
 * It permit to draw the voronoi diagram using the dag nodes and the triangles collections of the delaunay triangulation.
 * This class contains the features of the geometric objects that will be draw.
 */
class DrawableVoronoiDiagram : public cg3::DrawableObject {
    public:
        inline DrawableVoronoiDiagram();
        inline DrawableVoronoiDiagram(std::vector<DagNode*> *allNodes,std::vector<Triangle> *leaves);

        void draw() const;
        inline cg3::Pointd sceneCenter() const;
        inline double sceneRadius() const;

        inline void setEdgeColor(const QColor& c);
        inline void setPointColor(const QColor& c);
        inline void setEdgeWidth(const int &w);
        inline void setPointSize(const int &s);

        inline void setAllDagNodes(std::vector<DagNode*> *allNodes);
        inline void setTriangles(const std::vector<Triangle> *leaves);

    protected:
        void drawEdges(const Triangle &triangle) const;
        void drawPoints(const Triangle &triangle) const;

        std::vector<DagNode*>* _allDagNodes;
        const std::vector<Triangle>* _triangles;

        int pointSize;
        cg3::Color pointColor;
        int edgeWidth;
        cg3::Color edgeColor;
};

/**
 * @brief Default constructor.
 */
inline DrawableVoronoiDiagram::DrawableVoronoiDiagram() {
    this->_allDagNodes = nullptr;
    this->_triangles = nullptr;

    setEdgeColor(*new QColor(0,255,0));
    setPointColor(*new QColor(255,0,0));
    setEdgeWidth(1);
    setPointSize(3);
}

/**
 * @brief Constructor using the pointer to the list of the DAG nodes and the pointer to the list of triangles to set the internal attributes.
 * The other geometric attributes inside the drawable class are set statically by calling the relative methods.
 * @param allNodes pointer to the list of DAG nodes
 * @param triangles pointer to the list of triangles
 */
inline DrawableVoronoiDiagram::DrawableVoronoiDiagram(std::vector<DagNode*> *allNodes,std::vector<Triangle> *triangles){
    this->_allDagNodes = allNodes;
    this->_triangles = triangles;
    setEdgeColor(*new QColor(0,255,0));
    setPointColor(*new QColor(255,0,0));
    setEdgeWidth(1);
    setPointSize(3);
}

/**
 * @brief sceneCenter
 * @return
 */
inline cg3::Pointd DrawableVoronoiDiagram::sceneCenter() const{
    return *new cg3::Pointd (0, 0, 0);
}

/**
 * @brief sceneRadius
 * @return
 */
inline double DrawableVoronoiDiagram::sceneRadius() const{
    return 1e+6;
}

/**
 * @brief setEdgeColor
 * @param c edge color
 */
inline void DrawableVoronoiDiagram::setEdgeColor(const QColor &c){
    this->edgeColor = c;
}

/**
 * @brief setPointColor
 * @param c point color
 */
inline void DrawableVoronoiDiagram::setPointColor(const QColor &c){
    this->pointColor = c;
}

/**
 * @brief setEdgeWidth
 * @param w edge width
 */
inline void DrawableVoronoiDiagram::setEdgeWidth(const int &w){
    this->edgeWidth = w;
}

/**
 * @brief setPointSize
 * @param s point size
 */
inline void DrawableVoronoiDiagram::setPointSize(const int &s){
    this->pointSize = s;
}

/**
 * @brief setAllDagNodes set the internal attribute with a pointer to the list of nodes.
 * @param allNodes a pointer to a DagNode pointers vector
 */
inline void DrawableVoronoiDiagram::setAllDagNodes(std::vector<DagNode*> *allNodes){
    this->_allDagNodes = allNodes;
}

/**
 * @brief setAllDagNodes set the internal attribute with a pointer to the list of triangles.
 * @param triangles a pointer to a triangles vector
 */
inline void DrawableVoronoiDiagram::setTriangles(const std::vector<Triangle> *triangles){
    this->_triangles = triangles;
}


#endif // DRAWABLEVORONOIDIAGRAM_H
