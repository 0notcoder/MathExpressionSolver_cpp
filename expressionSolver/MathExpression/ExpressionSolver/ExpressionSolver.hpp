#pragma once
#include <string>
#include <memory>

#include "../ExpressionUtilities/ExpressionUtilities.hpp"
#include "../ExpressionParser/ExpressionParser.hpp"

class ExpressionSolver {
private:
	std::vector<Token>::iterator currentTokenIt;

	std::shared_ptr<ExpressionParser> parser;
	std::vector<Token> tokens;

	double firstPrior(const double &left);
	double secondPrior(const double &left);
	returnCode getCurrentToken(Token &token) const;
	void shiftCurrentToken();
	returnCode getCurrentTokenShift(Token &token);
	bool checkEndOfTokens() const;

public:
	ExpressionSolver() : currentTokenIt(tokens.begin()),
		parser(std::make_shared<ExpressionParser>()), tokens(std::vector<Token>()) {};

	double solve(const std::string &expression);
};
