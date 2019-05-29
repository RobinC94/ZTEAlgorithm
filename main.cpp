#include "ZTEGenetic.h"

using namespace ZTE_crb;

int generations = 100;
int genetics = 200;
int maxNum = 9;
double crossRate = 0.1;
double muteRate = 0.2;

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
    ZTEGenetic genetic1 = ZTEGenetic(genetics, maxNum, crossRate, muteRate);
    InitGenetic(genetic1);
    genetic1.DisplayGraph();

    for (int i = 0; i < generations-1; ++i){
        genetic1.GeneticInfo();
        genetic1.Evolution();
    }

    std::cout << std::endl << "------------\nevolution done!" << std::endl;
    genetic1.GeneticInfo();

    getchar();
    return 0;
}