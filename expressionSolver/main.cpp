#include <iostream>
#include "MathExpression/ExpressionSolver/ExpressionSolver.hpp"

int main(int argc, char** argv) {
	ExpressionSolver solver;
	std::string exp;
	std::cin >> exp; // TODO: remove spaces

	std::cout << solver.solve(exp) << std::endl;

	return 0;
}