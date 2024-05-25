#include <cstdlib>
#include <stdexcept>

typedef std::pair<double, double> Point;

double EPS = 10e-6;

class Line {
  const double a_, b_, c_;

public:
  Line(Point &p1, Point &p2)
      : a_(p2.first - p1.first), b_(-(p2.second - p1.second)),
        c_(-a_ * p2.first - b_ * p2.second) {
    if (a_ == 0 && b_ == 0) {
      throw std::invalid_argument("Error: both coefficients equals 0");
    }
  }

  Line(double a, double b, double c) : a_(a), b_(b), c_(c) {
    if (a_ == 0 && b_ == 0) {
      throw std::invalid_argument("Error: both coefficients equal 0");
    }
  }

  double a() const { return a_; }

  double b() const { return b_; }

  double c() const { return c_; }
  bool isParallel(const Line &other) const {
    if (std::abs(a_ * other.b_ - other.a_ * b_) < EPS) {
      return true;
    } else {
      return false;
    }
  }

  bool belong(const Point &p) const {
    return std::abs(a_ * p.first + b_ * p.second + c_) < EPS;
  }

  Point intersection(const Line &other) const {
    if (isParallel(other)) {
      throw std::invalid_argument("Lines are parallel");
    }
    if (a_ != 0) {
      double newB = other.b_ - b_ * other.a_ / a_;
      double newC = other.c_ - c_ * other.a_ / a_;
      double y = -newC / newB;
      double x = (-b_ * y - c_) / a_;
      return Point{x, y};
    } else {
      return other.intersection(*this);
    }
  }

  Line getPerpendicular(const Point &p) const {
    if (!belong(p)) {
      throw std::invalid_argument("Point does not belong to a line");
    }
    return Line{b_, -a_, a_ * p.second - b_ * p.first};
  }
};