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
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    std::vector <Path> newGeneration;

    std::cout << geneticGroup.size() << std::endl;

    for (auto p1_iter = geneticGroup.begin(); p1_iter != geneticGroup.end()-1; p1_iter++) {
        for (auto p2_iter = p1_iter+1; p2_iter!= geneticGroup.end(); p2_iter++) {
            double randomNum = dist(mt);
            randomNum = 0;
            if (randomNum < crossoverRate) {
                Path newPath = Exchange(*p1_iter, *p2_iter);
                newGeneration.push_back(newPath);

                DisplayPath(*p1_iter);
                DisplayPath(*p2_iter);
                //DisplayPath(newPath);
            }
            break;
        }
        break;
    }
}

Path ZTEGenetic::Exchange(Path p1, Path p2)
{
    size_t len1 = p1.size();
    size_t len2 = p2.size();
    size_t len = std::min(len1, len2);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, len-2);

    int pos = dist(mt);

    std::cout << pos << ' ' << len << std::endl;

    Path p;
    return p;

}
