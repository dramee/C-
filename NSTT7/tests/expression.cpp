#include "../src/expression.h"
#include <gtest/gtest.h>

TEST(DiffTest, AddVarConst) {
  std::shared_ptr<Expression> a = std::make_shared<Var>("y");
  std::shared_ptr<Expression> b = std::make_shared<Val>(3);
  std::shared_ptr<Expression> c = std::make_shared<Add>(a, b);
  EXPECT_EQ(c->diff("x")->toStringStream().str(), "(0 + 0)");

  std::shared_ptr<Expression> d = std::make_shared<Var>("y");
  std::shared_ptr<Expression> e = std::make_shared<Val>(2);
  std::shared_ptr<Expression> f = std::make_shared<Add>(d, e);
  EXPECT_EQ(f->diff("y")->toStringStream().str(), "(1 + 0)");
}

TEST(DiffTest, MultVarConst) {
  std::shared_ptr<Expression> a = std::make_shared<Var>("x");
  std::shared_ptr<Expression> b = std::make_shared<Val>(3);
  std::shared_ptr<Expression> c = std::make_shared<Mult>(a, b);
  EXPECT_EQ(c->diff("x")->toStringStream().str(), "((1 * 3) + (x * 0))");

  std::shared_ptr<Expression> d = std::make_shared<Var>("y");
  std::shared_ptr<Expression> e = std::make_shared<Val>(2);
  std::shared_ptr<Expression> f = std::make_shared<Mult>(d, e);
  EXPECT_EQ(f->diff("y")->toStringStream().str(), "((1 * 2) + (y * 0))");
}

TEST(DiffTest, DivVarConst) {
  // Testing division of a variable by a constant
  std::shared_ptr<Expression> a = std::make_shared<Var>("x");
  std::shared_ptr<Expression> b = std::make_shared<Val>(2);
  std::shared_ptr<Expression> c = std::make_shared<Div>(a, b);
  EXPECT_EQ(c->diff("x")->toStringStream().str(),
            "(((1 * 2) - (x * 0)) / (2 * 2))");

  // Testing division of a constant by a variable
  std::shared_ptr<Expression> d = std::make_shared<Var>("y");
  std::shared_ptr<Expression> e = std::make_shared<Val>(4);
  std::shared_ptr<Expression> f = std::make_shared<Div>(e, d);
  EXPECT_EQ(f->diff("y")->toStringStream().str(),
            "(((0 * y) - (4 * 1)) / (y * y))");
}

TEST(DiffTest, ExpVarConst) {
  std::shared_ptr<Expression> a = std::make_shared<Var>("x");
  std::shared_ptr<Expression> b = std::make_shared<Val>(2);
  std::shared_ptr<Expression> c = std::make_shared<Exponent>(a, b);
  EXPECT_EQ(c->diff("x")->toStringStream().str(), "((2 * (x ^ (2 - 1))) * 1)");
}

TEST(DiffTest, ExpConstVar) {
  std::shared_ptr<Expression> a = std::make_shared<Val>(2);
  std::shared_ptr<Expression> b = std::make_shared<Var>("x");
  std::shared_ptr<Expression> c = std::make_shared<Exponent>(a, b);
  ASSERT_THROW(c->diff("x")->toStringStream().str(), std::runtime_error);
}

TEST(DiffTest, ExpConstConst) {
  std::shared_ptr<Expression> a = std::make_shared<Val>(2);
  std::shared_ptr<Expression> b = std::make_shared<Val>(3);
  std::shared_ptr<Expression> c = std::make_shared<Exponent>(a, b);
  EXPECT_EQ(c->diff("x")->toStringStream().str(), "0");
}

// TEST(DiffTest, AddConst) {

// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}