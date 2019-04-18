#include "ZTEGenetic.h"

using namespace ZTE_crb;

void ZTEGenetic::InitGenetic()
{
    for (int i = 0; i < geneticSize; ++i) {
        Path _path = GeneratePath();
        geneticGroup.push_back(_path);
    }
}

void ZTEGenetic::Evolution()
{
    Crossover();
}

void ZTEGenetic::Crossover()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distRate(0.0, 1.0);

    std::vector <Path> newGeneration;

    std::cout << geneticGroup.size() << std::endl;

    for (auto p1_iter = geneticGroup.begin(); p1_iter != geneticGroup.end()-1; p1_iter++) {
        for (auto p2_iter = p1_iter+1; p2_iter!= geneticGroup.end(); p2_iter++) {
            double randomNum = distRate(mt);
            randomNum = 0;
            if (randomNum < crossoverRate) {
                size_t len1 = (*p1_iter).size();
                size_t len2 = (*p2_iter).size();
                size_t len = std::min(len1, len2);

                std::uniform_int_distribution<int> distLen(0, len-2);
                int pos = distLen(mt);
                Path newPath = Exchange(*p1_iter, *p2_iter, pos);
                newGeneration.push_back(newPath);

            }
            break;
        }
        break;
    }
}

Path ZTEGenetic::Exchange(Path p1, Path p2, int pos)
{
    Path shortcut = DijkstraPath(p1[pos], p2[pos]);

    Path p;
    p.insert(p.end(), p1.begin(), p1.begin()+pos+1);
    p.insert(p.end(), shortcut.begin()+1, shortcut.end());
    p.insert(p.end(), p2.begin()+pos+1, p2.end());
    return p;
}
