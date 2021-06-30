#pragma once

#include <ostream>
#include <vector>

class Matrix {
public:
  Matrix(int r, int c, double val = 0.0);
  Matrix(const std::vector<double> &data, int r, int c);

  double get(int i, int j) const;
  void set(int i, int j, double val);

  Matrix plus(const Matrix &m) const;
  Matrix minus(const Matrix &m) const;
  Matrix times(const Matrix& m) const;
  Matrix times(double scalar) const;
  Matrix reshape(int r, int c);

  std::string to_string() const;

  friend std::ostream &operator<<(std::ostream &os, const Matrix &m);

private:
  std::vector<double> _data;
  int _r;
  int _c;
};

std::ostream &operator<<(std::ostream &os, const Matrix &m);