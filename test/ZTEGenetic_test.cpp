#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "CxxTestDefs.h"
#include "ZTEGenetic.h"

using namespace ZTE_crb;


class GeneticTester : public ZTEGenetic, public testing::Test {
protected:
    ZTEGenetic genetic_ = ZTEGenetic(100, 30);

    virtual void SetUp() {
        genetic_.LoadGraph("../Graph1.csv");
        genetic_.SetVex(7, VexType::MUST);
        genetic_.SetVex(12, VexType::MUST);
        genetic_.SetEdge(2, 4, 2, EdgeType::MUST);
        genetic_.SetEdge(13, 14, 1, EdgeType::MUST);
        genetic_.SetEdge(11, 12, 1, EdgeType::FORBID);

        srand((unsigned)time(NULL));

        genetic_.InitGenetic();
    }

};

TEST(TestTest, EQandTRUE) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST_F(GeneticTester, TestGetVex) {
    EXPECT_EQ(genetic_.GetVexNum(), 18);
    EXPECT_EQ(genetic_.GetEdgeNum(), 41);
}

TEST_F(GeneticTester, TestDisplay) {
    genetic_.DisplayGraph();
}

TEST_F(GeneticTester, TestDijkstra) {
    Path shortcut_ = genetic_.DijkstraPath(0, 4);
    genetic_.DisplayPath(shortcut_);
}

TEST_F(GeneticTester, TestGeneratePath) {
    Path path_ = genetic_.GeneratePath();
    genetic_.DisplayPath(path_);
    int score_ = genetic_.CalculatePathScore(path_);
    std::cout << "Score: " << score_ << std::endl;
}

TEST_F(GeneticTester, TestExchange) {
    Path path1_ = {0, 1, 9, 11, 16, 17};
    Path path2_ = {0, 1, 4, 5, 2, 3, 7, 8, 15, 17};
    Path newPath_ = genetic_.Exchange(path1_, path2_, 4);
    genetic_.DisplayPath(newPath_);
    //EXPECT_THAT(newPath_, ElementsAre(0, 1, 9, 11, 10, 5, 2, 3, 7, 8, 15, 17));
}

TEST_F(GeneticTester, TestEvolution) {
    genetic_.Evolution();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}