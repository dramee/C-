#include "../src/squareMatrix.cpp"
#include <gtest/gtest.h>

TEST(SquareMatrix, InitTest1) {
  SquareMatrix m{{1, 2}};

  EXPECT_EQ(m.getSize(), 2);
  EXPECT_DOUBLE_EQ(m[0][0], 1);
  EXPECT_DOUBLE_EQ(m[1][1], 2);
  EXPECT_DOUBLE_EQ(m[0][1], 0);
  EXPECT_DOUBLE_EQ(m[1][0], 0);
}

TEST(SquareMatrix, InitTest2) {
  SquareMatrix m{0, 2};

  EXPECT_DOUBLE_EQ(m[0][0], 0);
  EXPECT_DOUBLE_EQ(m[1][1], 0);
  EXPECT_DOUBLE_EQ(m[0][1], 0);
  EXPECT_DOUBLE_EQ(m[1][0], 0);
}

TEST(SquareMatrix, EqualsPositiveTest) {
  SquareMatrix m1{{1, 2}};
  SquareMatrix m2{{1, 2}};

  EXPECT_TRUE(m1 == m2);
}

TEST(SquareMatrix, EqualsNegativeTest) {
  SquareMatrix m1{{1, 2}};
  SquareMatrix m2{{2, 3}};

  EXPECT_TRUE(m1 != m2);
}

TEST(SquareMatrix, CopyCtrTest) {
  SquareMatrix m1{{1, 2}};
  SquareMatrix m2{m1};

  EXPECT_TRUE(m1 == m2);
}

TEST(SquareMatrix, MoveCtrTest) {
  SquareMatrix m1{{1, 2}};
  SquareMatrix m2{std::move(m1)};

  SquareMatrix expected{{1, 2}};

  EXPECT_FALSE(m1 == m2);
  EXPECT_EQ(m2, expected);
}

TEST(SquareMatrix, CopyAssignmentTest) {
  SquareMatrix m1{{1, 2}};
  SquareMatrix m2;

  m2 = m1;

  EXPECT_TRUE(m1 == m2);
}

TEST(SquareMatrix, MoveAssignmentTest) {
  SquareMatrix m1{{1, 2}};
  SquareMatrix m2;

  SquareMatrix expected{{1, 2}};

  m2 = std::move(m1);

  EXPECT_FALSE(m1 == m2);
  EXPECT_TRUE(m2 == expected);
}

TEST(SquareMatrix, AddTest) {
  SquareMatrix m1{{1, 2}};
  SquareMatrix m2{{2, 3}};

  EXPECT_EQ(m1 + m2, SquareMatrix({3, 5}));
}

TEST(SquareMatrix, MultTest) {
  SquareMatrix m1(2);
  SquareMatrix m2(2);

  m1[0][0] = 1;
  m1[0][1] = 2;
  m1[1][0] = 3;
  m1[1][1] = 4;

  m2[0][0] = 4;
  m2[0][1] = 5;
  m2[1][0] = 6;
  m2[1][1] = 7;

  SquareMatrix expected(2);

  expected[0][0] = 16;
  expected[0][1] = 19;
  expected[1][0] = 36;
  expected[1][1] = 43;

  EXPECT_EQ(m1 * m2, expected);
}

TEST(SquareMatrix, castTest) {
  SquareMatrix m(2);

  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;  

  double actualTrace = static_cast<double>(m);

  EXPECT_DOUBLE_EQ(actualTrace, 10);
}

TEST(SquareMatrix, scalarMult) {
  SquareMatrix m{{1, 2}};
  SquareMatrix actual = m * 2;

  EXPECT_EQ(actual, SquareMatrix({2, 4}));
}

TEST(SquareMatrix, addAssignment) {
  SquareMatrix m1{{1, 2}};
  SquareMatrix m2{{2, 3}};

  m1 += m2;

  EXPECT_EQ(m1, SquareMatrix({3, 5}));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}