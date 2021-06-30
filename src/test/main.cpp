#include "../util/math/matrix.h"
#include <iostream>

int main(){

	Matrix m(4, 5, 4.0);
	m = m.times(7);
	//m = m.reshape(3, 2);
	std::vector<double> v = {3, 2, 7, 8, 2 ,5, 4, 0};
	Matrix mm(v,2,4);
	std::cout<<m<<std::endl;
	std::cout<<mm<<std::endl;

	std::cout<<mm.times(m);
	return 1;
}