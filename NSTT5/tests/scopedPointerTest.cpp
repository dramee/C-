#include "../src/scopedPointer.cpp"
#include <gtest/gtest.h>

class TestClass {
  size_t size;

public:
  TestClass(size_t size) : size(size) {}
  size_t getSize() const { return size; }
};

TEST(ScopedPointer, initTransferPointerTest) {
    ScopedPointerTransfer<TestClass> spt{new TestClass{20}};
    EXPECT_EQ(20, spt->getSize());
}

TEST(ScopedPointer, initDeepPointerTest) {
    ScopedPointerDeep<TestClass> spd{new TestClass{20}};
    EXPECT_EQ(20, spd->getSize());
}

TEST(ScopedPointer, transferTest1) {
    ScopedPointerTransfer<TestClass> spt{new TestClass{42}};
    ScopedPointerTransfer<TestClass> newSpt{std::move(spt)};
    EXPECT_EQ(newSpt->getSize(), 42);
    EXPECT_TRUE(spt.isEmpty());
}

TEST(ScopedPointer, transferTest2) {
    ScopedPointerTransfer<TestClass> spt{new TestClass{42}};
    ScopedPointerTransfer<TestClass> newSpt{new TestClass{15}};
    newSpt = std::move(spt);
    EXPECT_TRUE(spt.isEmpty());
    EXPECT_EQ(newSpt->getSize(), 42);
}

TEST(ScopedPointer, deepCopyTest1) {
    ScopedPointerDeep<TestClass> spt{new TestClass{42}};
    ScopedPointerDeep<TestClass> newSpt{spt};

    EXPECT_EQ(spt->getSize(), newSpt->getSize());
}

TEST(ScopedPointer, deepCopyTest2) {
    ScopedPointerDeep<TestClass> spt{new TestClass{42}};
    ScopedPointerDeep<TestClass> newSpt{new TestClass{15}};

    newSpt = spt;

    EXPECT_EQ(spt->getSize(), newSpt->getSize());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}