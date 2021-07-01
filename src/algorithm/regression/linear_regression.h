#pragma once
#include "util/math/matrix.h"

class linear_regression{
public:
	void fit(std::vector<double> x, std::vector<double> y, double reg = 0.0);
	double predict(double x);
};