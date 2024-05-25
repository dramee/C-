#include <memory>
#include <sstream>

class Expression {

public:
  virtual std::shared_ptr<Expression>
  diff(const std::string &variable) const = 0;
  virtual std::stringstream toStringStream() const = 0;
};

class Binary : public Expression {
protected:
  std::shared_ptr<Expression> left, right;

public:
  virtual char getSign() const = 0;

  Binary(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
      : left(l), right(r) {}
  std::stringstream toStringStream() const {
    std::stringstream ss;
    ss << "(" << left->toStringStream().str() << " " << getSign() << " "
       << right->toStringStream().str() << ")";
    return ss;
  }
};

class Add : public Binary {
public:
  Add(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
      : Binary(l, r) {}
  std::shared_ptr<Expression> diff(const std::string &variable) const override;
  char getSign() const override { return '+'; }
};

class Sub : public Binary {
public:
  Sub(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
      : Binary(l, r) {}
  std::shared_ptr<Expression> diff(const std::string &variable) const override;
  char getSign() const override { return '-'; }
};

class Mult : public Binary {
public:
  Mult(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
      : Binary(l, r) {}
  std::shared_ptr<Expression> diff(const std::string &variable) const override;
  char getSign() const override { return '*'; }
};

class Div : public Binary {
public:
  Div(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
      : Binary(l, r) {}
  std::shared_ptr<Expression> diff(const std::string &variable) const override;
  char getSign() const override { return '/'; }
};

class Exponent : public Binary {
public:
  Exponent(std::shared_ptr<Expression> base,
           std::shared_ptr<Expression> exponent)
      : Binary(base, exponent) {}
  std::shared_ptr<Expression> diff(const std::string &variable) const override;
  char getSign() const override { return '^'; }
};

class Var : public Expression {
private:
  std::string name;

public:
  Var(const std::string &n) : name(n) {}
  std::shared_ptr<Expression> diff(const std::string &variable) const override;
  std::string getName() const { return name; }
  std::stringstream toStringStream() const override {
    std::stringstream ss;
    ss << name;
    return ss;
  }
};

class Val : public Expression {
private:
  int value;

public:
  Val(int val) : value(val) {}

  std::shared_ptr<Expression> diff(const std::string &variable) const override;
  int getValue() const { return value; }
  std::stringstream toStringStream() const override {
    std::stringstream ss;
    ss << value;
    return ss;
  }
};