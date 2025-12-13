#pragma once
#include <string>

#include "ExpressionUtilities.hpp"
#include "ExpressionParser.hpp"

class ExpressionSolver {
private:
	std::string expression;
	std::string::iterator currentIt;
	
	double firstPrior(const double &left);
	double secondPrior(const double& left);
	static bool checkEnd(const std::string &str, const std::string::iterator &strIt);

public:
	double solve(const std::string &expression);
};
