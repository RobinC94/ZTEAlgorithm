#include "gtest/gtest.h"

#include "ZTEGraph.h"

using namespace ZTE_crb;

class GraphTester : public ZTEGraph, public testing::Test {
protected:
    ZTEGraph graph_ = ZTEGraph(9);

    virtual void SetUp() {
        graph_.LoadGraph("../Graph1.csv");
    }

};

TEST(TestTest, EQandTRUE) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST_F(GraphTester, TestGetVex) {
    EXPECT_EQ(graph_.GetVexNum(), 18);
    EXPECT_EQ(graph_.GetEdgeNum(), 41);
}

TEST_F(GraphTester, TestCopyAndEqual) {
    ZTEGraph graph_copy(graph_);
    EXPECT_EQ(graph_copy.GetVexNum(), 18);
    EXPECT_EQ(graph_copy.GetEdgeNum(), 41);

    ZTEGraph graph_equal = graph_;
    EXPECT_EQ(graph_equal.GetVexNum(), 18);
    EXPECT_EQ(graph_equal.GetEdgeNum(), 41);
}

TEST_F(GraphTester, TestLoadGraph) {
    graph_.SetVex(7, VexType::MUST);
    graph_.SetVex(12, VexType::MUST);
    graph_.SetEdge(2, 4, 2, EdgeType::MUST);
    graph_.SetEdge(13, 14, 1, EdgeType::MUST);
    graph_.SetEdge(11, 12, 1, EdgeType::FORBID);
}

void SetElement(ZTEGraph &graph){
    graph.SetVex(7, VexType::MUST);
    graph.SetVex(12, VexType::MUST);
    graph.SetEdge(2, 4, 2, EdgeType::MUST);
    graph.SetEdge(13, 14, 1, EdgeType::MUST);
    graph.SetEdge(11, 12, 1, EdgeType::FORBID);
}

TEST_F(GraphTester, TestDisplay) {
    SetElement(graph_);
    graph_.DisplayGraph();
}

TEST_F(GraphTester, TestDijkstra) {
    Path shortcut_ = graph_.DijkstraPath(0, 4);
    graph_.DisplayPath(shortcut_);
}

TEST_F(GraphTester, TestPath) {
    Path path_1 = graph_.GeneratePath();
    graph_.DisplayPath(path_1);
    Path path_2 = graph_.GeneratePath();
    graph_.DisplayPath(path_2);
    Path path_3 = graph_.GeneratePath();
    graph_.DisplayPath(path_3);
}

TEST_F(GraphTester, TestCalculateScore) {
    SetElement(graph_);
    Path path_ = graph_.GeneratePath();
    graph_.DisplayPath(path_);
    int score_ = graph_.CalculatePathScore(path_);
    std::cout << "Score: " << score_ << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
