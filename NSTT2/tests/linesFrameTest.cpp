#include "../src/linesFrame.cpp"
#include <gtest/gtest.h>

TEST(linesFrameTest, pointInit) {
  Point p{1, 2};
  EXPECT_DOUBLE_EQ(1, p.first);
  EXPECT_DOUBLE_EQ(2, p.second);
}

TEST(linesFrameTest, lineFromCoefInit) {
  Line line{1, 2, 3};
  EXPECT_DOUBLE_EQ(1, line.a());
  EXPECT_DOUBLE_EQ(2, line.b());
  EXPECT_DOUBLE_EQ(3, line.c());
}

TEST(linesFrameTest, lineFromPointsInit1) {
  Point p1{0, 0};
  Point p2{1, 1};
  Line line{p1, p2};
  EXPECT_DOUBLE_EQ(1, line.a());
  EXPECT_DOUBLE_EQ(-1, line.b());
  EXPECT_DOUBLE_EQ(0, line.c());
}

TEST(linesFrameTest, lineFromPointsInit2) {
  Point p1{0, 1};
  Point p2{1, 1};
  Line line{p1, p2};
  EXPECT_DOUBLE_EQ(1, line.a());
  EXPECT_DOUBLE_EQ(0, line.b());
  EXPECT_DOUBLE_EQ(-1, line.c());
}

TEST(linesFrameTest, parallelPositive1) {
  Line l1{1, 2, 3};
  Line l2{2, 4, 1231512};
  EXPECT_TRUE(l1.isParallel(l2));
}

TEST(linesFrameTest, parallelPositive2) {
  Line l1{0, 3, 310};
  Line l2{0, 5, 12351};
  EXPECT_TRUE(l1.isParallel(l2));
}

TEST(linesFrameTest, parallelNegative) {
  Line l1{0, 1, 1};
  Line l2{1, 0, 1};
  EXPECT_FALSE(l1.isParallel(l2));
}

TEST(linesFrameTest, belongPositive) {
  Point p{1, 4};
  Line l{8, 1.5, -14};
  EXPECT_TRUE(l.belong(p));
}

TEST(linesFrameTest, belongNegative) {
  Point p{0, 0};
  Line l{0, 1, -1};
  EXPECT_FALSE(l.belong(p));
}

TEST(linesFrameTest, simpleIntersection) {
  Line l1{0, 1, 0};
  Line l2{1, 0, 0};
  Point ip = l1.intersection(l2);
  EXPECT_DOUBLE_EQ(ip.first, 0);
  EXPECT_DOUBLE_EQ(ip.second, 0);
}

TEST(linesFrameTest, intersection) {
  Line l1{1, 0, -1};
  Line l2{1, -1, -1};
  Point p = l1.intersection(l2);
  EXPECT_DOUBLE_EQ(p.first, 1);
  EXPECT_DOUBLE_EQ(p.second, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}