#include "../include/ZTEGraph.h"

using namespace ZTE_crb;

ZTEGraph::ZTEGraph(const ZTEGraph &copy) {
    vexNum = copy.vexNum;
    edgeNum = copy.edgeNum;

    for (auto &path : copy.matrix)
        matrix.push_back(path);

    m_Vexs = copy.m_Vexs;
    m_Edge = copy.m_Edge;
}

ZTEGraph& ZTEGraph::operator=(const ZTEGraph &copy) {
    if (this == &copy)
        return *this;

    vexNum = copy.vexNum;
    edgeNum = copy.edgeNum;

    for (auto &path : copy.matrix)
        matrix.push_back(path);

    m_Vexs = copy.m_Vexs;
    m_Edge = copy.m_Edge;

    return *this;
}

void ZTEGraph::LoadGraph(const char* fileName)
{
    std::ifstream fin(fileName);
    if (!fin.is_open()) throw std::logic_error("No graph file!");
    std::string line;
    vexNum = 0;
    edgeNum = 0;

    std::regex spliter{ "," };
    while (getline(fin, line)) {
        std::sregex_token_iterator itor(line.begin(), line.end(), spliter, -1);
        std::sregex_token_iterator ender;
        Path p;
        while (itor != ender)
        {
            auto para = *(itor++);
            Vex v = std::stoi(para);
            p.push_back(v);
            if (p.back() > 0) edgeNum++;
        }
        matrix.push_back(p);
        vexNum++;
    }
    edgeNum /= 2;

    SetVex(0, VexType::START);
    SetVex(vexNum-1, VexType::END);
}

void ZTEGraph::SetVex(const Vex &v, const VexType &t)
{
    if (v < 0 || v >= vexNum) throw std::invalid_argument("Invalid input vex!");
    switch (t)
    {
        case ZTE_crb::VexType::START:
        case ZTE_crb::VexType::END:
            if (m_Vexs[t].empty()) m_Vexs[t].insert(v);
            else throw std::invalid_argument("Start/End point already exists!");
            break;
        case ZTE_crb::VexType::COMMON:
            for (auto itor = m_Vexs[VexType::MUST].begin(); itor != m_Vexs[VexType::MUST].end(); ++itor)
            {
                if (v == (*itor)) {
                    m_Vexs[VexType::MUST].erase(itor);
                    goto _LABEL_COMMON_END;
                }
            }
            for (auto itor = m_Vexs[VexType::FORBID].begin(); itor != m_Vexs[VexType::FORBID].end(); ++itor)
            {
                if (v == (*itor)) {
                    m_Vexs[VexType::FORBID].erase(itor);
                    goto _LABEL_COMMON_END;
                }
            }
        _LABEL_COMMON_END:
            break;
        case ZTE_crb::VexType::MUST:
        case ZTE_crb::VexType::FORBID:
            for (auto itor = m_Vexs[t].begin(); itor != m_Vexs[t].end(); ++itor)
            {
                if (v == (*itor)) goto _LABEL_FM_END;
            }
            m_Vexs[t].insert(v);
        _LABEL_FM_END:
            break;
        default:
            break;
    }
}

void ZTEGraph::SetEdge(const Vex &v1, const Vex &v2, const int &weight, const EdgeType &t)
{
    if (v1 < 0 || v1 >= vexNum) throw std::invalid_argument("Invalid v1!");
    if (v2 < 0 || v2 >= vexNum) throw std::invalid_argument("Invalid v2!");
    if (v1 == v2) throw std::invalid_argument("Same v1 and v2!");
    if (weight <= 0) throw std::invalid_argument("Weight must be positive!");

    if (matrix[v1][v2] == 0) edgeNum++;
    matrix[v1][v2] = weight;
    matrix[v2][v1] = weight;

    switch (t)
    {
        case ZTE_crb::EdgeType::COMMON:
            for (auto itor = m_Edge[EdgeType::MUST].begin(); itor != m_Edge[EdgeType::MUST].end(); ++itor)
            {
                if ((v1 == (*itor).first && v2 == (*itor).second) ||
                    (v2 == (*itor).first && v1 == (*itor).second)) {
                    m_Edge[EdgeType::FORBID].erase(itor);
                    goto _LABEL_COMMON_END;
                }
            }
            for (auto itor = m_Edge[EdgeType::FORBID].begin(); itor != m_Edge[EdgeType::FORBID].end(); ++itor)
            {
                if ((v1 == (*itor).first && v2 == (*itor).second) ||
                    (v2 == (*itor).first && v1 == (*itor).second)) {
                    m_Edge[EdgeType::FORBID].erase(itor);
                    goto _LABEL_COMMON_END;
                }
            }
        _LABEL_COMMON_END:
            break;
        case ZTE_crb::EdgeType::MUST:
        case ZTE_crb::EdgeType::FORBID:
            Edge e(v1, v2);
            for (auto itor = m_Edge[t].begin(); itor != m_Edge[t].end(); ++itor)
            {
                if ((v1 == (*itor).first && v2 == (*itor).second) ||
                    (v2 == (*itor).first && v1 == (*itor).second)) goto _LABEL_FM_END;
            }
            m_Edge[t].insert(e);
        _LABEL_FM_END:
            break;
    }
}

void ZTEGraph::DisplayGraph(bool showVexElem) const
{
    std::cout << "Adjacency Matrix:" << std::endl;

    for (int i = 0; i < vexNum; ++i)
    {
        if (showVexElem) {
            std::cout << (i == *(m_Vexs.at(VexType::START).begin()) ? "s" : (i == *(m_Vexs.at(VexType::END).begin()) ? "e" : std::to_string(i))) << ":";
        }
        for (auto&ele : matrix[i])
            std::cout << "  " << ele;
        std::cout << std::endl;
    }

    std::cout << std::endl << "Vex num:" << vexNum << std::endl;
    std::cout << "Edge num:" << edgeNum << std::endl;


    std::cout << std::endl << "Must pass vex:";
    if (m_Vexs.find(VexType::MUST) != m_Vexs.end()) {
        for (auto &i: m_Vexs.at(VexType::MUST)) std::cout << "  " << i;
    }

    std::cout << std::endl << "Forbid pass vex:";
    if (m_Vexs.find(VexType::FORBID) != m_Vexs.end()) {
        for (auto &i : m_Vexs.at(VexType::FORBID)) std::cout << "  " << i;
    }

    std::cout << std::endl << "Must pass edge:";
    if (m_Edge.find(EdgeType::MUST) != m_Edge.end()) {
        for (auto &pi :m_Edge.at(EdgeType::MUST))
            std::cout << "  (" << pi.first << "," << pi.second << ")";
    }

    std::cout << std::endl << "Forbid pass edge:";
    if (m_Edge.find(EdgeType::MUST) != m_Edge.end()) {
        for (auto &pi :m_Edge.at(EdgeType::FORBID))
            std::cout << "  (" << pi.first << "," << pi.second << ")";
    }
    std::cout << std::endl;
}

void ZTEGraph::DisplayPath(const Path &path) const
{
    std::cout << "s: ";
    for (auto &ele : path) {
        std::cout << ele << ' ';
    }
    std::cout << 'e' << std::endl;
}

Path ZTEGraph::DijkstraPath(const Vex &v1, const Vex &v2) const
{
    std::vector<int> distance(vexNum, MAX_DIS);
    std::vector<Vex> previous(vexNum, v1);
    std::vector<bool> known(vexNum, false);

    distance[v1] = 0;
    while (1) {
        int minDist = MAX_DIS;
        Vex smallVex = -1;
        for (int i = 0; i < vexNum; i++) {
            if (distance[i] <= minDist && !known[i]) {
                smallVex = i;
                minDist = distance[i];
            }
        }
        if(smallVex < 0) break;

        known[smallVex] = true;

        for (int i = 0; i < vexNum; i++) {
            if (matrix[smallVex][i] > 0 && !known[i]) {
                if (distance[smallVex] + matrix[smallVex][i] < distance[i]) {
                    distance[i] = distance[smallVex] + matrix[smallVex][i];
                    previous[i] = smallVex;
                }
            }
        }
    }

    Path shortPath(1,v2);

    while (shortPath.front() != v1) {
        shortPath.insert(shortPath.begin(), previous[shortPath.front()]);
    }

    return shortPath;
}

Path ZTEGraph::GeneratePath()
{
    std::random_device rd;
    std::mt19937 mt(rd());

    _START:
    std::vector<bool> passed(vexNum, false);
    Path path;
    Vex currentVex = 0;

    while (currentVex != vexNum-1) {
        path.push_back(currentVex);
        passed[currentVex] = true;
        std::vector<Vex> selectedList;

        for (int i = 0; i < vexNum; ++i) {
            if (matrix[currentVex][i] > 0 && !passed[i]) {
                selectedList.push_back(i);
            }
        }

        if (selectedList.empty()) {
            goto _START;
        }

        //std::random_shuffle(selectedList.begin(), selectedList.end());
        //currentVex = *selectedList.begin();

        //int index = rand() % selectedList.size();
        std::uniform_int_distribution<int> dist(0, selectedList.size()-1);
        int index = dist(mt);
        currentVex = selectedList[index];
    }

    path.push_back(currentVex);
    return path;
}

int ZTEGraph::CalculatePathScore(const Path &path) const
{
    int score = 0;
    bool findMustVex = false;
    bool findMustEdge = false;
    std::set<Vex> passedMustVex;
    std::set<Edge> passedMustEdge;

    if (path.size() > maxVexNum) {
        score += OVER_VEX_VALUE * (path.size() - maxVexNum);
    }

    if (m_Vexs.find(VexType::MUST) != m_Vexs.end()) {
        score += MUST_VEX_VALUE * (m_Vexs.at(VexType::MUST).size());
        findMustVex = true;
    }
    if (m_Edge.find(EdgeType::MUST) != m_Edge.end()) {
        score += MUST_EDGE_VALUE * (m_Edge.at(EdgeType::MUST).size());
        findMustEdge = true;
    }

    for (auto iter = path.begin(); iter != path.end(); ++iter) {
        if (findMustVex) {
            if (m_Vexs.at(VexType::MUST).find(*iter) != m_Vexs.at(VexType::MUST).end()
                    && passedMustVex.find(*iter) == passedMustVex.end()) {
                score -= MUST_VEX_VALUE;
                passedMustVex.insert(*iter);
            }
        }

        if (m_Vexs.find(VexType::FORBID) != m_Vexs.end()) {
            if (m_Vexs.at(VexType::FORBID).find(*iter) != m_Vexs.at(VexType::FORBID).end()) {
                score += FORBID_VEX_VALUE;
            }
        }

        auto nextIter = iter+1;
        if (nextIter != path.end()) {
            score += matrix[*iter][*nextIter];
            Edge inEdge(*iter, *nextIter);
            Edge outEdge(*nextIter, *iter);

            if (findMustEdge) {
                if (m_Edge.at(EdgeType::MUST).find(inEdge) != m_Edge.at(EdgeType::MUST).end()
                    || m_Edge.at(EdgeType::MUST).find(outEdge) != m_Edge.at(EdgeType::MUST).end()) {
                    if (passedMustEdge.find(inEdge) == passedMustEdge.end()) {
                        score -= MUST_EDGE_VALUE;
                        passedMustEdge.insert(inEdge);
                        passedMustEdge.insert(outEdge);
                    }
                }
            }

            if (m_Edge.find(EdgeType::FORBID) != m_Edge.end()) {
                if (m_Edge.at(EdgeType::FORBID).find(inEdge) != m_Edge.at(EdgeType::FORBID).end()
                    || m_Edge.at(EdgeType::FORBID).find(outEdge) != m_Edge.at(EdgeType::FORBID).end() ) {
                    score += FORBID_EDGE_VALUE;
                }
            }
        }

    }

    return score;

}