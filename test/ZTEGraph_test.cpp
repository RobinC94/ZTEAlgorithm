#include "gtest/gtest.h"

#include "CxxTestDefs.h"
#include "ZTEGraph.h"

using namespace ZTE_crb;

class GraphTester : public ZTEGraph, public testing::Test {
protected:
    ZTEGraph graph_ = ZTEGraph();

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

void SetElement(ZTEGraph &graph){
    graph.SetVex(7, VexType::MUST);
    graph.SetVex(12, VexType::MUST);
    graph.SetEdge(2, 4, 2, EdgeType::MUST);
    graph.SetEdge(13, 14, 1, EdgeType::MUST);
    graph.SetEdge(11, 12, 1, EdgeType::FORBID);
    graph.SetMaxVexNum(9);
}

TEST_F(GraphTester, TestDisplay) {
    SetElement(graph_);
    graph_.DisplayGraph();
}

TEST_F(GraphTester, TestDijkstra) {
    Path shortcut_ = graph_.DijkstraPath(2, 13);
    graph_.DisplayPath(shortcut_);
    shortcut_ = graph_.DijkstraPath(5, 5);
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
    Path path_ = {0, 3, 7, 6, 5, 12, 13, 16, 17};
    graph_.DisplayPath(path_);
    int score_ = graph_.CalculatePathScore(path_);
    EXPECT_EQ(score_, 1012);
}

TEST_F(GraphTester, TestCalculateDistance) {
    Path path_ = {0, 2, 4, 5, 12, 13, 15, 17};
    int dist_ = graph_.CalculatePathDistance(path_);
    EXPECT_EQ(dist_, 15);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
