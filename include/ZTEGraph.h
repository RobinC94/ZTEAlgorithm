#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include "CommonType.h"
#include <map>
#include <list>

namespace ZTE_crb {
    class ZTEGraph
    {
    public:
        ZTEGraph() {};
        ~ZTEGraph() {};
        ZTEGraph(const ZTEGraph &copy);
        ZTEGraph& operator=(const ZTEGraph &copy);

        int GetVexNum() { return vexNum; };
        int GetEdgeNum() { return edgeNum; };

        void LoadGraph(const char* fileName);
        void SetVex(const Vex &v, const VexType &t);
        void SetEdge(const Vex &v1, const Vex &v2, const int &weight, const EdgeType &t);

        Path DijkstraPath(const Vex &v1, const Vex &v2);

        void Display(bool showVexElem = true) ;

    protected:
        int vexNum, edgeNum;
        Matrix matrix;

        std::map<VexType, std::list<Vex>> m_Vexs;
        std::map<EdgeType, std::list<Edge>> m_Edge;
    };
}
