#include "include/ZTEGraph.h"

using namespace ZTE_crb;

void InitGraph(ZTEGraph &graph)
{
    graph.LoadGraph("./Graph1.csv");
    // graph.LoadGraph("/Users/robin.chen/ClionProjects/ZTEAlgorithm/Graph1.csv");
    graph.SetVex(7, VexType::MUST);
    graph.SetVex(12, VexType::MUST);
    graph.SetEdge(2, 4, 2, EdgeType::MUST);
    graph.SetEdge(13, 14, 1, EdgeType::MUST);
    graph.SetEdge(11, 12, 1, EdgeType::FORBID);

}

int main(int argc, char *argv[]) {
    ZTEGraph graph1;
    InitGraph(graph1);

    graph1.Display();
    Path shortcut = graph1.DijkstraPath(2, 16);

    for (auto &ele : shortcut) {
        std::cout << ele << ' ';
    }

    getchar();
    return 0;
}