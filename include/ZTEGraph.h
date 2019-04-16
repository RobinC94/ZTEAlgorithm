#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <set>
#include <algorithm>
#include <random>

#include "CommonType.h"

namespace ZTE_crb {
    class ZTEGraph
    {
    public:
        ZTEGraph() {};
        ~ZTEGraph() {};
        ZTEGraph(int _maxVexNum) : maxVexNum(_maxVexNum) {};
        ZTEGraph(const ZTEGraph &copy);
        ZTEGraph& operator=(const ZTEGraph &copy);

        int GetVexNum() const { return vexNum; };
        int GetEdgeNum() const { return edgeNum; };

        void LoadGraph(const char* fileName);
        void SetVex(const Vex &v, const VexType &t);
        void SetEdge(const Vex &v1, const Vex &v2, const int &weight, const EdgeType &t);
        void SetMaxVexNum(int vexNum) { maxVexNum = vexNum; };

        Path GeneratePath();
        Path DijkstraPath(const Vex &v1, const Vex &v2) const;

        void DisplayGraph(bool showVexElem = true) const;
        void DisplayPath(const Path &path) const;

        int CalculatePathScore(const Path &path) const;

    protected:
        int vexNum, edgeNum;
        Matrix matrix;
        int maxVexNum;

        std::map<VexType, std::set<Vex>> m_Vexs;
        std::map<EdgeType, std::set<Edge>> m_Edge;

    };
}
