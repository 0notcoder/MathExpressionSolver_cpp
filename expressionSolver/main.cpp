#include <iostream>
#include "expressionSolver.hpp"


int main(int argc, char** argv) {
	ExpressionSolver solver;
	std::string exp;
	std::cin >> exp; // TODO: remove spaces

	//std::cout << solver.solve(exp) << std::endl;

	ExpressionParser parser;

	std::vector<Token> tokens = parser.parse(exp);

	for (std::vector<Token>::const_iterator it = tokens.begin(); it != tokens.end(); it++) {
		std::cout << "Type: " << static_cast<int>(it->getType()) << "\nValue: " << it->getValue() << "\n\n";
	}

	return 0;
}