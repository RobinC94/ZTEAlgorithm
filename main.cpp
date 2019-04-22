#include "ZTEGenetic.h"

using namespace ZTE_crb;

void InitGenetic(ZTEGenetic &genetic)
{
    genetic.LoadGraph("../Graph1.csv");
    genetic.SetVex(7, VexType::MUST);
    genetic.SetVex(12, VexType::MUST);
    genetic.SetEdge(2, 4, 2, EdgeType::MUST);
    genetic.SetEdge(13, 14, 1, EdgeType::MUST);
    genetic.SetEdge(11, 12, 1, EdgeType::FORBID);
    genetic.InitGenetic();

}

int main(int argc, char *argv[]) {
    ZTEGenetic genetic1 = ZTEGenetic(100, 9);
    InitGenetic(genetic1);
    genetic1.DisplayGraph();

    for (int i = 0; i < 30; ++i){
        genetic1.GeneticInfo();
        genetic1.Evolution();
    }

    genetic1.GeneticInfo();

    getchar();
    return 0;
}