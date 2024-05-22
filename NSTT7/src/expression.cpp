#include "expression.h"
#include <stdexcept>

std::shared_ptr<Expression> Var::diff(const std::string &variable) const {
  if (variable == name) {
    return std::make_shared<Val>(1); // d(x)/dx = Val(1);
  } else {
    return std::make_shared<Val>(0);
  }
}

std::shared_ptr<Expression> Exponent::diff(const std::string &variable) const {
  if (std::shared_ptr<Var> v = std::dynamic_pointer_cast<Var>(right);
      v && v->getName() == variable) {
    // d(u^y)/dx = u^y * d(y*ln(u))/dx = u^y * ln(u) * dy/dx
    throw std::runtime_error("Chain rule not implemented yet");
  } else if (std::shared_ptr<Var> v = std::dynamic_pointer_cast<Var>(left);
             v && v->getName() == variable) {
    // d(u^n)/dx = n * u^(n-1) * du/dx
    // Expression *n_minus_one = new Sub(right, new Val(1));
    std::shared_ptr<Sub> n_minus_one =
        std::make_shared<Sub>(right, std::make_shared<Val>(1));
    return std::make_shared<Mult>(
        std::make_shared<Mult>(right,
                               std::make_shared<Exponent>(left, n_minus_one)),
        left->diff(variable));
  } else {
    // Exponent is a constant, base is not just the variable
    return std::make_shared<Val>(0);
  }
}

std::shared_ptr<Expression> Div::diff(const std::string &variable) const {
  return std::make_shared<Div>(
      std::make_shared<Sub>(
          std::make_shared<Mult>(left->diff(variable), right),
          std::make_shared<Mult>(left, right->diff(variable))),
      std::make_shared<Mult>(right, right));
}

std::shared_ptr<Expression> Mult::diff(const std::string &variable) const {
  return std::make_shared<Add>(
      std::make_shared<Mult>(left->diff(variable), right),
      std::make_shared<Mult>(left, right->diff(variable)));
}

std::shared_ptr<Expression> Sub::diff(const std::string &variable) const {
  return std::make_shared<Sub>(
      std::make_shared<Sub>(left->diff(variable), right),
      right->diff(variable));
}

std::shared_ptr<Expression> Add::diff(const std::string &variable) const {
  return std::make_shared<Add>(left->diff(variable), right->diff(variable));
}

std::shared_ptr<Expression> Val::diff(const std::string &variable) const {
  return std::make_shared<Val>(0);
}