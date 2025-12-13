#pragma once

#include <string>
#include <vector>
#include "ExpressionUtilities.hpp"

class ExpressionParser {
private:
	double buff;
	std::string expression;
	std::string::iterator currentSymbolIt;
	std::vector<Token> tokens;

	int overPoint;

	inline void addToken(const Token &token);
	char getCurrentSymbol() const;
	void shiftCurrentSymbol();
	void numberToken();
	char getCurrentSymbolShift();
	void oneSymbolToken();
	void endState();

	void (ExpressionParser:: *getNextMethod())();

public:
	ExpressionParser() : buff(0), overPoint(0) {};

	std::vector<Token> parse(const std::string &expression);
};