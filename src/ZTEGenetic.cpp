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
    Mutation();
}

void ZTEGenetic::Crossover()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distRate(0.0, 1.0);

    std::vector <Path> newGenerations;

    for (auto p1_iter = geneticGroup.begin(); p1_iter != geneticGroup.end()-1; p1_iter++) {
        for (auto p2_iter = p1_iter+1; p2_iter != geneticGroup.end(); p2_iter++) {
            double randomNum = distRate(mt);
            if (randomNum < crossoverRate) {
                size_t len1 = (*p1_iter).size();
                size_t len2 = (*p2_iter).size();
                size_t len = std::min(len1, len2);

                std::uniform_int_distribution<int> distLen(0, len-2);
                int pos = distLen(mt);
                Path newPath = Exchange(*p1_iter, *p2_iter, pos);
                newGenerations.push_back(newPath);
            }
        }
    }

    geneticGroup.insert(geneticGroup.end(), newGenerations.begin(), newGenerations.end());
}

void ZTEGenetic::Mutation()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distRate(0.0, 1.0);

    for (auto p_iter = geneticGroup.begin(); p_iter != geneticGroup.begin()+geneticSize; p_iter++) {
        double randomNum = distRate(mt);
        randomNum = 0.0;
        if (randomNum < mutationRate) {
            if (m_Vexs[VexType::MUST].empty() && m_Edge[EdgeType::MUST].empty()){
                continue;

            }

            else {

            }
        }
        break;

    }
}

Path ZTEGenetic::Exchange(const Path &path1, const Path &path2, int pos)
{
    Path shortcut = DijkstraPath(path1[pos], path2[pos]);

    Path resultPath;
    resultPath.insert(resultPath.end(), path1.begin(), path1.begin()+pos+1);
    resultPath.insert(resultPath.end(), shortcut.begin()+1, shortcut.end());
    resultPath.insert(resultPath.end(), path2.begin()+pos+1, path2.end());
    return resultPath;
}

Path ZTEGenetic::Variation(const Path &path, Vex target1, Vex target2)
{
    Path goTo;
    Path goBack;
    Vex firstVex = path[0];
    Vex secondVex = path[0];

    if (target1 == target2) {
        int minDist = INT_MAX - 1;
        int secondMinDist = INT_MAX;
        for (auto &v : path) {
            Path shortcut = DijkstraPath(v, target1);
            int dist = CalculatePathDistance(shortcut);
            if (dist < minDist) {
                secondMinDist = minDist;
                secondVex = firstVex;
                minDist = dist;
                firstVex = v;
                goTo = shortcut;
            }
            else if (dist < secondMinDist) {
                secondMinDist = dist;
                secondVex = v;
                goBack = shortcut;
            }
        }
    }

    else {
        firstVex = FindNearestVex(path, target1, goTo);
        secondVex = FindNearestVex(path, target2, goBack);
    }
    std::reverse(goBack.begin(), goBack.end());

    Path resultPath;

    resultPath.insert(resultPath.end(), path.begin(), std::find(path.begin(), path.end(), firstVex));
    resultPath.insert(resultPath.end(), goTo.begin(), goTo.end());
    if (target1 == target2) resultPath.pop_back();
    resultPath.insert(resultPath.end(), goBack.begin(), goBack.end());
    resultPath.insert(resultPath.end(), std::find(path.begin(), path.end(), secondVex)+1, path.end());

    return resultPath;
}

Vex ZTEGenetic::FindNearestVex(const Path &path, Vex vex, Path &shortcut)
{
    int minDist = INT_MAX;
    Vex result = path[0];
    for (auto &v : path) {
        Path curShortcut = DijkstraPath(v, vex);
        int curDist = CalculatePathDistance(curShortcut);
        if (curDist < minDist){
            minDist = curDist;
            result = v;
            shortcut = curShortcut;
        }
    }
    return result;
}
