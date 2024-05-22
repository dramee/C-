#include <cstdlib>
#include <stdexcept>
#include <vector>

class SquareMatrix {
  size_t size_;
  double **matrix_;

  void multiplyByScalar(double num) {
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        matrix_[i][j] *= num;
      }
    }
  }

  friend SquareMatrix &operator*(double left, SquareMatrix &right);
  friend SquareMatrix &operator*(SquareMatrix &left, double right);

public:
  SquareMatrix() : size_(0), matrix_(nullptr) {}

  explicit SquareMatrix(double value, size_t size) : size_(size) {
    matrix_ = new double *[size_];
    for (size_t i = 0; i < size_; ++i) {
      matrix_[i] = new double[size_];
      for (size_t j = 0; j < size_; ++j) {
        matrix_[i][j] = value;
      }
    }
  }

  SquareMatrix(size_t n) : size_(n) {
    matrix_ = new double *[size_];
    for (int i = 0; i < size_; ++i) {
      matrix_[i] = new double[size_];
    }
  }

  SquareMatrix(const SquareMatrix &other) : size_(other.size_) {
    matrix_ = new double *[other.size_];
    for (int i = 0; i < size_; i++) {
      matrix_[i] = new double[other.size_];
      for (int j = 0; j < size_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }

  SquareMatrix(SquareMatrix &&other)
      : size_(other.size_), matrix_(other.matrix_) {
    other.matrix_ = nullptr;
  }

  SquareMatrix(const std::vector<double> &diagonal)
      : SquareMatrix(diagonal.size()) {
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        if (i == j) {
          matrix_[i][j] = diagonal.at(i);
        } else {
          matrix_[i][j] = 0;
        }
      }
    }
  }

  explicit operator double() {
    double summ = 0;
    for (int i = 0; i < size_; i++) {
      for (int j = 0; j < size_; j++) {
        summ += matrix_[i][j];
      }
    }
    return summ;
  }

  SquareMatrix operator+(const SquareMatrix &other) const {
    SquareMatrix result = SquareMatrix(size_);
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        result.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
      }
    }
    return result;
  }

  SquareMatrix &operator+=(const SquareMatrix &other) {
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
    return *this;
  }

  SquareMatrix operator*(const SquareMatrix &other) const {
    SquareMatrix result = SquareMatrix(size_);
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        result.matrix_[i][j] = 0;
        for (int k = 0; k < size_; ++k) {
          result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    return result;
  }

  SquareMatrix &operator*=(SquareMatrix other) {
    SquareMatrix result(size_);
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        result.matrix_[i][j] = 0;
        for (int k = 0; k < size_; ++k) {
          result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    std::swap(matrix_, result.matrix_);
    return *this;
  }

  SquareMatrix &operator*=(const double lambda) {
    multiplyByScalar(lambda);
    return *this;
  }

  SquareMatrix &operator=(SquareMatrix other) {
    std::swap(size_, other.size_);
    std::swap(matrix_, other.matrix_);
    return *this;
  }

  bool operator==(const SquareMatrix &other) const {
    if (!matrix_ || !other.matrix_ || size_ != other.size_) {
      return false;
    }
    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  bool operator!=(const SquareMatrix &other) const { return !(*this == other); }

  ~SquareMatrix() {
    if (matrix_) {
      for (int i = 0; i < size_; ++i) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
    }
  }

  double *operator[](size_t index) {
    if (matrix_ == nullptr) {
      throw std::runtime_error("Matrix unitialized");
    }
    return matrix_[index];
  }

  size_t getSize() const { return size_; }
};

SquareMatrix &operator*(double left, SquareMatrix &right) {
  right.multiplyByScalar(left);
  return right;
}
SquareMatrix &operator*(SquareMatrix &left, double right) {
  left.multiplyByScalar(right);
  return left;
}