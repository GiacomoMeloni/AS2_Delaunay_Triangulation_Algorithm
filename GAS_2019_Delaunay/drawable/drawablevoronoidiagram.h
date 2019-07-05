#ifndef DRAWABLEVORONOIDIAGRAM_H
#define DRAWABLEVORONOIDIAGRAM_H

#include <cg3/utilities/color.h>
#include "cg3/viewer/interfaces/drawable_object.h"
#include "cg3/viewer/renderable_objects/2d/renderable_objects2d.h"
#include "../algorithms/delauneytriangulation.h"

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

inline DrawableVoronoiDiagram::DrawableVoronoiDiagram() {
    this->_allDagNodes = nullptr;
    this->_triangles = nullptr;

    setEdgeColor(*new QColor(0,255,0));
    setPointColor(*new QColor(255,0,0));
    setEdgeWidth(1);
    setPointSize(3);
}

inline DrawableVoronoiDiagram::DrawableVoronoiDiagram(std::vector<DagNode*> *allNodes,std::vector<Triangle> *triangles){
    this->_allDagNodes = allNodes;
    this->_triangles = triangles;
    setEdgeColor(*new QColor(0,255,0));
    setPointColor(*new QColor(255,0,0));
    setEdgeWidth(1);
    setPointSize(3);
}

inline cg3::Pointd DrawableVoronoiDiagram::sceneCenter() const{
    return *new cg3::Pointd (0, 0, 0);
}

inline double DrawableVoronoiDiagram::sceneRadius() const{
    return 1e+6;
}

inline void DrawableVoronoiDiagram::setEdgeColor(const QColor &c){
    this->edgeColor = c;
}

inline void DrawableVoronoiDiagram::setPointColor(const QColor &c){
    this->pointColor = c;
}

inline void DrawableVoronoiDiagram::setEdgeWidth(const int &w){
    this->edgeWidth = w;
}

inline void DrawableVoronoiDiagram::setPointSize(const int &s){
    this->pointSize = s;
}

inline void DrawableVoronoiDiagram::setAllDagNodes(std::vector<DagNode*> *allNodes){
    this->_allDagNodes = allNodes;
}

inline void DrawableVoronoiDiagram::setTriangles(const std::vector<Triangle> *triangles){
    this->_triangles = triangles;
}


#endif // DRAWABLEVORONOIDIAGRAM_H
