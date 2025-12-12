#include <iostream>
#include "expressionSolver.hpp"


int main(int argc, char** argv) {
	ExpressionSolver solver;
	std::string exp;
	std::cin >> exp;

	std::cout << solver.solve(exp) << std::endl;

	return 0;
}