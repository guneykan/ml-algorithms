#pragma once

#include <ostream>
#include <vector>
#include <exception>

struct DimensionException : public std::exception
{
	const char * what () const throw ()
    {
    	return "Dimension Error";
    }
};


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
  Matrix transpose();
  double minor(int i, int j);
  double cofactor(int i, int j);
  Matrix cofactor();
  Matrix adjoint();
	double det();
	Matrix inverse();

  std::string to_string() const;

  friend std::ostream &operator<<(std::ostream &os, const Matrix &m);

private:
  std::vector<double> _data;
  int _r;
  int _c;
};

std::ostream &operator<<(std::ostream &os, const Matrix &m);