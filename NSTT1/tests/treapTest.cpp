#include "../src/treap.cpp"
#include <gtest/gtest.h>

TEST(TreapTest, insertTest) {
  Treap<int> treap;
  treap.insert(5);
  treap.insert(4);
  treap.insert(7);
  std::vector<int> actual = treap.getSorted();
  std::vector<int> expected{4, 5, 7};
  EXPECT_EQ(actual, expected);
}

TEST(TreapTest, removeTest) {
  Treap<int> treap;
  treap.insert(5);
  treap.insert(4);
  treap.insert(7);
  treap.insert(10);
  treap.remove(5);
  std::vector<int> actual = treap.getSorted();
  std::vector<int> expected{4, 7, 10};
  EXPECT_EQ(actual, expected);
}

TEST(TreapTest, findTestPositive) {
  Treap<int> treap;
  treap.insert(3);
  treap.insert(6);
  treap.insert(7);
  treap.insert(123);
  treap.insert(213);
  EXPECT_TRUE(treap.find(123));
}

TEST(TreapTest, findTestNegative) {
  Treap<int> treap;
  treap.insert(3);
  treap.insert(6);
  treap.insert(7);
  treap.insert(123);
  treap.insert(213);
  EXPECT_FALSE(treap.find(1024));
}

TEST(TreapTest, initTest) {
  Treap<int> treap;
  EXPECT_TRUE(treap.empty());
}

TEST(TreapTest, maxTestFailed) {
  Treap<int> treap;
  EXPECT_THROW(
      {
        try {
          int value = treap.max();
        } catch (const std::runtime_error &e) {
          // and this tests that it has the correct message
          EXPECT_STREQ("Data is empty", e.what());
          throw;
        }
      },
      std::runtime_error);
}

TEST(TreapTest, removeSimpleFailed) {
  Treap<int> treap;
  EXPECT_THROW(
      {
        try {
          treap.remove(5);
        } catch (const std::invalid_argument &e) {
          // and this tests that it has the correct message
          EXPECT_STREQ("Remove error: no such element", e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(TreapTest, removeFailed) {
  Treap<int> treap;
  treap.insert(3);
  treap.insert(4);
  treap.insert(10);
  EXPECT_THROW(
      {
        try {
          treap.remove(5);
        } catch (const std::invalid_argument &e) {
          // and this tests that it has the correct message
          EXPECT_STREQ("Remove error: no such element", e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(TreapTest, minTestFailed) {
  Treap<int> treap;
  EXPECT_THROW(
      {
        try {
          int value = treap.min();
        } catch (const std::runtime_error &e) {
          // and this tests that it has the correct message
          EXPECT_STREQ("Data is empty", e.what());
          throw;
        }
      },
      std::runtime_error);
}

TEST(TreapTest, maxTest) {
  Treap<int> treap;
  treap.insert(3);
  treap.insert(3);
  treap.insert(6);
  treap.insert(7);
  treap.insert(123);
  treap.insert(213);
  EXPECT_EQ(treap.max(), 213);
}

TEST(TreapTest, minTest) {
  Treap<int> treap;
  treap.insert(3);
  treap.insert(3);
  treap.insert(6);
  treap.insert(7);
  treap.insert(123);
  treap.insert(213);
  EXPECT_EQ(treap.min(), 3);
}

TEST(TreapTest, copyCtrTest1) {
  Treap<int> t1;;
  t1.insert(2);
  t1.insert(3);
  t1.insert(19);
  t1.insert(25);
  Treap<int> t2(t1);
  t2.remove(19);

  std::vector<int> actualT1 = t1.getSorted();
  std::vector<int> actualT2 = t2.getSorted();

  std::vector<int> expectedT1{2, 3, 19, 25};
  std::vector<int> expectedT2{2, 3, 25};

  EXPECT_EQ(actualT1, expectedT1);
  EXPECT_EQ(actualT2, expectedT2);
}

TEST(TreapTest, copyCtrTest2) {
  Treap<int> t1;
  t1.insert(2);
  t1.insert(3);
  t1.insert(19);
  t1.insert(25);
  Treap<int> t2(t1);
  t2.insert(15);

  std::vector<int> actualT1 = t1.getSorted();
  std::vector<int> actualT2 = t2.getSorted();

  std::vector<int> expectedT1{2, 3, 19, 25};
  std::vector<int> expectedT2{2, 3, 15, 19, 25};

  EXPECT_EQ(actualT1, expectedT1);
  EXPECT_EQ(actualT2, expectedT2);
}

TEST(TreapTest, copyAssignmentOpTest1) {
  Treap<int> t1;
  Treap<int> t2;
  t1.insert(2);
  t1.insert(3);
  t1.insert(19);
  t1.insert(25);
  t2 = t1;

  std::vector<int> actualT1 = t1.getSorted();
  std::vector<int> actualT2 = t2.getSorted();

  std::vector<int> expected{2, 3, 19, 25};

  EXPECT_EQ(actualT1, expected);
  EXPECT_EQ(actualT2, expected);
}

TEST(TreapTest, copyAssignmentOpTest2) {
  Treap<int> t1;
  Treap<int> t2;
  t1.insert(2);
  t1.insert(3);
  t1.insert(19);
  t1.insert(25);
  t2.insert(31);
  t2.insert(32);
  t2 = t1;

  std::vector<int> actualT1 = t1.getSorted();
  std::vector<int> actualT2 = t2.getSorted();

  std::vector<int> expected{2, 3, 19, 25};

  EXPECT_EQ(actualT1, expected);
  EXPECT_EQ(actualT2, expected);
}

TEST(TreapTest, copyAssignmentOpTest3) {
  Treap<int> t1;
  Treap<int> t2;
  t1.insert(2);
  t1.insert(3);
  t1.insert(19);
  t1.insert(25);
  t2.insert(31);
  t2.insert(32);
  t2 = t1;

  t2.remove(19);

  std::vector<int> actualT1 = t1.getSorted();
  std::vector<int> actualT2 = t2.getSorted();

  std::vector<int> expectedT1{2, 3, 19, 25};
  std::vector<int> expectedT2{2, 3, 25};

  EXPECT_EQ(actualT1, expectedT1);
  EXPECT_EQ(actualT2, expectedT2);
}

TEST(TreapTest, moveCtrTest) {
  Treap<int> t1;
  t1.insert(3);
  t1.insert(42);
  t1.insert(15);
  Treap t2 = std::move(t1);
  std::vector<int> actual = t2.getSorted();
  std::vector<int> expected{3, 15, 42};

  EXPECT_TRUE(t1.empty());
  EXPECT_EQ(actual, expected);
}

TEST(TreapTest, moveAssignmentTest) {
  Treap<int> t1;
  t1.insert(3);
  t1.insert(42);
  t1.insert(15);
  Treap<int> t2;
  t2.insert(15);
  t2.insert(25);
  t2.insert(50);

  t2 = std::move(t1);
  std::vector<int> actual = t2.getSorted();
  std::vector<int> expected{3, 15, 42};

  EXPECT_TRUE(t1.empty());
  EXPECT_EQ(actual, expected);
}

TEST(TreapTest, templateTest) {
  Treap<double> td;

  td.insert(1);
  td.insert(3);

  EXPECT_EQ(std::vector<double>({1, 3}), td.getSorted());
}

TEST(TreapTest, iteratorTest) {
  Treap<int> ti;

  ti.insert(42);
  ti.insert(15);
  ti.insert(1);
  ti.insert(90);

  size_t idx = 0;
  std::vector<int> expected{1, 15, 42, 90};

  for (auto value : ti) {
    EXPECT_EQ(expected.at(idx++),  value);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}