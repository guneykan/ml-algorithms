#include "matrix.h"

#include <cmath>
#include <iostream>

Matrix::Matrix(int r, int c, double val) : _r(r), _c(c) {
  _data = std::vector<double>(r * c, val);
  _data.reserve(r * c);
}

Matrix::Matrix(const std::vector<double> &data, int r, int c) {
  if (data.size() != r * c) {
    std::cerr << "Can't create the matrix!" << std::endl;
    throw "Dimension error";
  }

  _data = data;
  _data.reserve(r * c);
  _r = r;
  _c = c;
}

double Matrix::get(int i, int j) const { return _data[i * _c + j]; }

void Matrix::set(int i, int j, double val) { _data[i * _c + j] = val; }

Matrix Matrix::plus(const Matrix &m) const {
  if (_r != m._r || _c != m._c) {
    std::cerr << "Can't sum the matrices!" << std::endl;
    throw DimensionException();
  }
  std::vector<double> copy = _data;
  std::transform(copy.begin(), copy.end(), m._data.begin(), copy.begin(),
                 std::plus<double>());

  return Matrix(copy, _r, _c);
}

Matrix Matrix::minus(const Matrix &m) const {
  if (_r != m._r || _c != m._c) {
    std::cerr << "Can't subtract the matrices!" << std::endl;
    throw "Dimension error";
  }
  std::vector<double> copy = _data;
  std::transform(copy.begin(), copy.end(), m._data.begin(), copy.begin(),
                 std::minus<double>());

  return Matrix(copy, _r, _c);
}

Matrix Matrix::times(const Matrix &m) const {
  if (_c != m._r) {
    std::cerr << "Can't multiply the matrices!" << std::endl;
    throw "Dimension error";
  }
  Matrix res(_r, m._c);
  for (int i = 0; i < _r; i++) {
    for (int j = 0; j < m._c; j++) {
      double sum = 0.0;
      for (int k = 0; k < _c; k++) {
        sum += get(i, k) * m.get(k, j);
      }
      res.set(i, j, sum);
    }
  }
  return res;
}

Matrix Matrix::times(double scalar) const {
  std::vector<double> copy = _data;
  std::transform(
      copy.begin(), copy.end(), copy.begin(),
      std::bind(std::multiplies<double>(), std::placeholders::_1, scalar));

  return Matrix(copy, _r, _c);
}

Matrix Matrix::reshape(int r, int c) {
  if (r * c != _r * _c) {
    std::cerr << "Can't reshape the matrix!" << std::endl;
    throw "Dimension error";
  }
  std::vector<double> copy = _data;
  return Matrix(copy, r, c);
}

Matrix Matrix::transpose() {
  Matrix res(_c, _r);
  for (int i = 0; i < _c; i++) {
    for (int j = 0; j < _r; j++) {
      res.set(i, j, get(j, i));
    }
  }
  return res;
}

double Matrix::minor(int i, int j) {
  std::vector<double> data;
  for (int k = 0; k < _r; k++) {
    for (int l = 0; l < _c; l++) {
      if (k == i || l == j) {
        continue;
      }
      data.push_back(get(k, l));
    }
  }
  return Matrix(data, _r - 1, _c - 1).det();
}

double Matrix::cofactor(int i, int j) {
  std::vector<double> data;
  for (int k = 0; k < _r; k++) {
    for (int l = 0; l < _c; l++) {
      if (k == i || l == j) {
        continue;
      }
      data.push_back(get(k, l));
    }
  }
  return std::pow(-1, i + j) * Matrix(data, _r - 1, _c - 1).det();
}

Matrix Matrix::cofactor() {
  std::vector<double> data;
  for (int k = 0; k < _r; k++) {
    for (int l = 0; l < _c; l++) {
      data.push_back(cofactor(k, l));
    }
  }
  return Matrix(data, _r, _c);
}

Matrix Matrix::adjoint() { return cofactor().transpose(); }

double Matrix::det() {
  if (_r != _c) {
    std::cerr << "Can't compute the determinant!" << std::endl;
    throw "Dimension error";
  }

  if (_r == 1) {
    return get(0, 0);
  }

  double d = 0;
  for (int j = 0; j < _c; j++) {
    d += get(0, j) * cofactor(0, j);
  }

  return d;
}

Matrix Matrix::inverse() {
  std::vector<double> data;
  double d = det();
  if (d == 0) {
    std::cerr << "Can't compute the inverse!" << std::endl;
    throw "Singular matrix";
  }

  return adjoint().times(1.0 / d);
}

std::string Matrix::to_string() const {
  std::vector<double>::const_iterator beg = _data.cbegin();
  std::vector<double>::const_iterator end = _data.cend();
  std::string res = "";
  for (auto it = beg; it != end; it++) {
    res += std::to_string(*it);
    int i = (it - beg) / _c;
    int j = (it - beg) % _c;
    if (j == _c - 1 && i != _r - 1) {
      res += '\n';
    } else if (j != _c - 1 || i != _r - 1) {
      res += ' ';
    }
  }
  return res;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
  os << m.to_string() << std::endl;
  return os;
}