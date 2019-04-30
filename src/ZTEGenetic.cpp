#include "ZTEGenetic.h"

using namespace ZTE_crb;

void ZTEGenetic::InitGenetic()
{
    for (int i = 0; i < geneticSize; ++i) {
        Path _path = GeneratePath();
        geneticGroup.push_back(_path);
    }
    generations = 1;
}

size_t ZTE_crb::binarySearch(std::vector<double> num, double value) {
    size_t begin = 0, end= num.size()-1;
    while(begin < end-1){
        size_t mid = (begin + end) / 2;
        if (num[mid] <= value && num[mid+1] > value) {
            return mid;
        }
        if(num[mid] > value){
            end = mid;
        }
        else if (num[mid+1] <= value){
            begin = mid;
        }
    }
    return begin;
}

void ZTEGenetic::Evolution(bool verbose)
{
    std::random_device rd;
    std::mt19937 mt(rd());

    Path currentBest = FindBestPath();

    if (verbose)
        std::cout << "current generation size: " << geneticGroup.size() << std::endl;
    Crossover();
    if (verbose)
        std::cout << "generation size after crossover: " << geneticGroup.size() << std::endl;
    Mutation();
    if (verbose)
        std::cout << "generation size after mutation: " << geneticGroup.size() << std::endl;
    AddGenetics();
    if (verbose)
        std::cout << "generation size after add: " << geneticGroup.size() << std::endl;

    std::vector<double> fitValueList(geneticGroup.size(), 0.0);

    for (size_t i = 0; i < geneticGroup.size(); ++i){
        double fitValue = 10.0 / CalculatePathScore(geneticGroup[i]);
        if (i == 0) fitValueList[i] = fitValue;
        else fitValueList[i] = fitValueList[i-1] + fitValue;
    }

    std::uniform_real_distribution<double> distRouletteWheel(0.0, fitValueList[fitValueList.size()-1]);
    std::vector<Path> newGenerationGroup;

    for(size_t i = 0; i < geneticSize-1; ++i){
        double randomFitValue = distRouletteWheel(mt);
        size_t selectedGeneIndex = binarySearch(fitValueList, randomFitValue);
        newGenerationGroup.push_back(geneticGroup[selectedGeneIndex]);
    }
    newGenerationGroup.push_back(currentBest);
    geneticGroup = newGenerationGroup;
    generations++;
}

void ZTEGenetic::Crossover()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distRate(0.0, 1.0);

    std::vector <Path> newGenerations;

    for (auto p1_iter = geneticGroup.begin(); p1_iter != geneticGroup.begin()+geneticSize-1; p1_iter++) {
        for (auto p2_iter = p1_iter+1; p2_iter != geneticGroup.begin()+geneticSize; p2_iter++) {
            double randomNum = distRate(mt);
            if (randomNum < crossoverRate) {
                size_t len1 = (*p1_iter).size();
                size_t len2 = (*p2_iter).size();
                size_t len = std::min(len1, len2);

                std::uniform_int_distribution<size_t> distLen(0, len-2);
                size_t pos = distLen(mt);
                Path newPath = Exchange(*p1_iter, *p2_iter, pos);
                if (newPath.size() < GetVexNum())
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

    std::vector <Path> newGenerations;

    for (auto p_iter = geneticGroup.begin(); p_iter != geneticGroup.begin()+geneticSize; p_iter++) {
        double randomNum = distRate(mt);
        if (randomNum < mutationRate) {
            if (m_Vexs[VexType::MUST].empty() && m_Edge[EdgeType::MUST].empty()){
                continue;
            }
            else {
                std::uniform_int_distribution<size_t> distSelect(0, m_Vexs[VexType::MUST].size()+m_Edge[EdgeType::MUST].size()-1);
                size_t randomSelect = distSelect(mt);

                if (randomSelect >= m_Vexs[VexType::MUST].size()){
                    size_t randomIndex = randomSelect - m_Vexs[VexType::MUST].size();
                    auto e_iter = m_Edge[EdgeType::MUST].begin();
                    std::advance(e_iter, randomIndex);
                    Edge selectedEdge = *e_iter;
                    Path newPath = Variation(*p_iter, selectedEdge.first, selectedEdge.second);
                    if (newPath.size() < GetVexNum())
                        newGenerations.push_back(newPath);
                }
                else{
                    auto v_iter = m_Vexs[VexType::MUST].begin();
                    std::advance(v_iter, randomSelect);
                    Vex selectedVex = *v_iter;
                    Path newPath = Variation(*p_iter, selectedVex, selectedVex);
                    if (newPath.size() < GetVexNum())
                        newGenerations.push_back(newPath);
                }
            }
        }
    }

    geneticGroup.insert(geneticGroup.end(), newGenerations.begin(), newGenerations.end());
}

Path ZTEGenetic::Exchange(const Path &path1, const Path &path2, size_t pos)
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

void ZTEGenetic::AddGenetics()
{
    for (int i = 0; i < geneticSize; ++i){
        Path newPath = GeneratePath();
        geneticGroup.push_back(newPath);
    }
}

Path ZTEGenetic::FindBestPath(bool verbose) const
{
    int minScore = INT_MAX;
    Path result;
    for (auto &path : geneticGroup){
        int curScore = CalculatePathScore(path);
        if (curScore < minScore) {
            minScore = curScore;
            result = path;
        }
    }
    if (verbose)
        std::cout << "Best path score: " << minScore << std::endl;

    return result;
}

void ZTEGenetic::GeneticInfo() const
{
    std::cout << "current genaration: " << generations << std::endl;
    Path best = FindBestPath(true);
    DisplayPath(best);
}
