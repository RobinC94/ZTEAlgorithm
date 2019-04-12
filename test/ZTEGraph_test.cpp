#include "gtest/gtest.h"

#include "../include/ZTEGraph.h"

using namespace ZTE_crb;

class GraphTester : public ZTEGraph, public testing::Test {
protected:
    ZTEGraph graph_;

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

TEST_F(GraphTester, TestLoadGraph) {
    graph_.SetVex(7, VexType::MUST);
    graph_.SetVex(12, VexType::MUST);
    graph_.SetEdge(2, 4, 2, EdgeType::MUST);
    graph_.SetEdge(13, 14, 1, EdgeType::MUST);
    graph_.SetEdge(11, 12, 1, EdgeType::FORBID);
}

TEST_F(GraphTester, TestDisplay) {
    graph_.Display();
}

TEST_F(GraphTester, TestDijkstra) {
    graph_.DijkstraPath(0, 4);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

