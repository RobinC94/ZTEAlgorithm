#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "CxxTestDefs.h"
#include "ZTEGenetic.h"

using namespace ZTE_crb;


class GeneticTester : public ZTEGenetic, public testing::Test {
protected:
    ZTEGenetic genetic_ = ZTEGenetic(100, 9, 0.1, 0.05);

    virtual void SetUp() {
        genetic_.LoadGraph("../Graph1.csv");
        genetic_.SetVex(7, VexType::MUST);
        genetic_.SetVex(12, VexType::MUST);
        genetic_.SetEdge(2, 4, 2, EdgeType::MUST);
        genetic_.SetEdge(13, 14, 1, EdgeType::MUST);
        genetic_.SetEdge(11, 12, 1, EdgeType::FORBID);

        genetic_.InitGenetic();
    }

};

TEST(TestTest, EQandTRUE) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(TestTest, TestBinarySearch) {
    std::vector<double> array_ = {0.1, 0.3, 0.7, 0.9, 1.2, 1.6, 1.7, 1.8, 2.0};
    EXPECT_EQ(binarySearch(array_, 0.4), 1);
    EXPECT_EQ(binarySearch(array_, 1.5), 4);
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

TEST_F(GeneticTester, TestFindNear) {
    Path path_ = {0, 2, 4, 9, 10, 12, 13, 17};
    Path tmpPath_;
    Vex nearest_;
    nearest_ = genetic_.FindNearestVex(path_, 1, tmpPath_);
    EXPECT_EQ(nearest_, 2);
    nearest_ = genetic_.FindNearestVex(path_, 8, tmpPath_);
    std::cout << "Near:" << nearest_ << std::endl;
    genetic_.DisplayPath(tmpPath_);
}

TEST_F(GeneticTester, TestVariation) {
    Path path_ = {0, 3, 7, 6, 12, 10, 9, 11, 16, 17};
    Path result_ = genetic_.Variation(path_, 4, 2);
    genetic_.DisplayPath(result_);
    path_ = {0, 1, 9, 11, 16, 17};
    result_ = genetic_.Variation(path_, 7, 7);
    genetic_.DisplayPath(result_);
}

TEST_F(GeneticTester, TestEvolution) {
    Path best_ = genetic_.FindBestPath();
    genetic_.DisplayPath(best_);
    genetic_.Evolution(true);
    best_ = genetic_.FindBestPath();
    genetic_.DisplayPath(best_);
    genetic_.Evolution(true);
    best_ = genetic_.FindBestPath();
    genetic_.DisplayPath(best_);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}