#include "Graph.h"

using namespace ZTE_crb;

ZTEGraph::ZTEGraph(const ZTEGraph &copy) {
	vexNum = copy.vexNum;
	edgeNum = copy.edgeNum;

	for (auto&path : copy.matrix) 
		matrix.push_back(path);

	m_Vexs = copy.m_Vexs;
	m_Edge = copy.m_Edge;
}

ZTEGraph& ZTEGraph::operator=(const ZTEGraph &copy) {
	if (this == &copy)
		return *this;

	vexNum = copy.vexNum;
	edgeNum = copy.edgeNum;

	for (auto&path : copy.matrix)
		matrix.push_back(path);

	m_Vexs = copy.m_Vexs;
	m_Edge = copy.m_Edge;

	return *this;
}

void ZTEGraph::LoadGraph(const char* fileName)
{
	std::ifstream fin("Graph1.csv");
	if (!fin.is_open()) throw std::logic_error("文件不存在！");
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

void ZTEGraph::SetVex(Vex v, VexType t)
{
	if (v < 0 || v >= vexNum) throw std::invalid_argument("输入点不存在！");
	switch (t)
	{
	case ZTE_crb::VexType::START:
	case ZTE_crb::VexType::END:
		if (m_Vexs[t].empty()) m_Vexs[t].push_back(v);
		else throw std::invalid_argument("已存在起点/终点！");
		break;
	case ZTE_crb::VexType::COMMON:
		for (auto itor = m_Vexs[VexType::MUST].begin(); itor != m_Vexs[VexType::MUST].end(); ++itor)
		{
			if (v == (*itor)) {
				m_Vexs[VexType::MUST].erase(itor);
				goto _LABEL_COMMON_END;
			}
		}
		for (auto itor = m_Vexs[VexType::FORBIT].begin(); itor != m_Vexs[VexType::FORBIT].end(); ++itor)
		{
			if (v == (*itor)) {
				m_Vexs[VexType::FORBIT].erase(itor);
				goto _LABEL_COMMON_END;
			}
		}
		_LABEL_COMMON_END:
		break;
	case ZTE_crb::VexType::MUST:
	case ZTE_crb::VexType::FORBIT:
		for (auto itor = m_Vexs[t].begin(); itor != m_Vexs[t].end(); ++itor)
		{
			if (v == (*itor)) goto _LABEL_FM_END;
		}
		m_Vexs[t].push_back(v);
		_LABEL_FM_END:
		break;
	default:
		break;
	}
}

void ZTEGraph::SetEdge(Vex v1, Vex v2, int weight, EdgeType t)
{
	if (v1 < 0 || v1 >= vexNum) throw std::invalid_argument("v1不合法！");
	if (v2 < 0 || v2 >= vexNum) throw std::invalid_argument("v2不合法！");
	if (v1 == v2) throw std::invalid_argument("v1不能与V2相同！");
	if (weight <= 0) throw std::invalid_argument("权值必须为正！");

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
				m_Edge[EdgeType::FORBIT].erase(itor);
				goto _LABEL_COMMON_END;
			}
		}
		for (auto itor = m_Edge[EdgeType::FORBIT].begin(); itor != m_Edge[EdgeType::FORBIT].end(); ++itor)
		{
			if ((v1 == (*itor).first && v2 == (*itor).second) ||
				(v2 == (*itor).first && v1 == (*itor).second)) {
				m_Edge[EdgeType::FORBIT].erase(itor);
				goto _LABEL_COMMON_END;
			}
		}
	_LABEL_COMMON_END:
		break;
	case ZTE_crb::EdgeType::MUST:
	case ZTE_crb::EdgeType::FORBIT:
		Edge e(v1, v2);
		for (auto itor = m_Edge[t].begin(); itor != m_Edge[t].end(); ++itor)
		{
			if ((v1 == (*itor).first && v2 == (*itor).second) ||
				(v2 == (*itor).first && v1 == (*itor).second)) goto _LABEL_FM_END;
		}		
		m_Edge[t].push_back(e);
		_LABEL_FM_END:
		break;
	}
}

void ZTEGraph::Display(bool showVexElem)
{
	std::cout << "邻接矩阵：" << std::endl;

	for (int i = 0; i < vexNum; ++i)
	{
		if (showVexElem) {
			std::cout << (i == (m_Vexs[VexType::START].front()) ? "s" : (i == (m_Vexs[VexType::END].front()) ? "e" : std::to_string(i))) << ":";
		}
		for (auto&ele : matrix[i])
			std::cout << "  " << ele;
		std::cout << std::endl;
	}

	std::cout << std::endl << "总点数：" << vexNum << std::endl;
	std::cout << "总边数：" << edgeNum << std::endl;


	std::cout << std::endl << "必经点：";
	for (auto&i: m_Vexs[VexType::MUST]) std::cout << "  " << i;

	std::cout << std::endl << "不经点：";
	for (auto&i : m_Vexs[VexType::FORBIT]) std::cout << "  " << i;

	std::cout << std::endl << "必经边：";
	for (auto&pi :m_Edge[EdgeType::MUST])
		std::cout << "  (" << pi.first << "," << pi.second << ")";

	std::cout << std::endl << "不经边：";
	for (auto&pi :m_Edge[EdgeType::FORBIT])
		std::cout << "  (" << pi.first << "," << pi.second << ")";
	std::cout << std::endl;
}

Path ZTEGraph::DijkstraPath(Vex v1, Vex v2)
{
	std::vector<int> distance(vexNum, MAX_DIS);
	std::vector<Vex> previous(vexNum, v1);
	std::vector<bool> known(vexNum, false);

	distance[v1] = 0;
	while (1) {
		int minDist = MAX_DIS;
		Vex smallVex = -1;
		for (int i = 0; i < vexNum; i++) {
			if (distance[i] <= minDist && known[i] == false) {
				smallVex = i;
				minDist = distance[i];
			}
		}
		if(smallVex < 0) break;

		known[smallVex] = true;

		for (int i = 0; i < vexNum; i++) {
			if (matrix[smallVex][i] > 0 && known[i] == false) {
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