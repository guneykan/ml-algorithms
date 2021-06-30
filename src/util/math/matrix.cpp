#include "matrix.h"
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
  _r = r;
  _c = c;
}

double Matrix::get(int i, int j) const { return _data[i * _c + j];   }

void Matrix::set(int i, int j, double val) { _data[i * _c + j] = val; }

Matrix Matrix::plus(const Matrix &m) const {
  std::vector<double> copy = _data;
  std::transform(copy.begin(), copy.end(), m._data.begin(), copy.begin(),
                 std::plus<double>());

  return Matrix(copy, _r, _c);
}

Matrix Matrix::minus(const Matrix &m) const {
  std::vector<double> copy = _data;
  std::transform(copy.begin(), copy.end(), m._data.begin(), copy.begin(),
                 std::minus<double>());

  return Matrix(copy, _r, _c);
}

Matrix Matrix::times(const Matrix &m) const{
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