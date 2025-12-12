#pragma once
#include <string>
#include <vector>

extern const enum class tokenType;

struct Token {
private:
	int value;
	tokenType type;

public:
	Token(int value, tokenType type) : value(value), type(type) {};

	int getValue() const;
	tokenType getType() const;
};

class ExpressionParser {
	int buff;
	std::string expression;
	std::string::iterator currentSymbolIt;
	
	int overPoint;

public:
	ExpressionParser() : buff(0), overPoint(0) {};

	static std::vector<Token> parse(const std::string &expression);

	char getCurrentSymbol() const;
	void shiftCurrentSymbol();
	char getCurrentSymbolShift();

	void numberToken();
};

class ExpressionSolver {
private:
	std::string expression;
	std::string::iterator currentIt;
public:
	static bool checkEnd(const std::string &str, const std::string::iterator &strIt);
	double solve(const std::string &expression);
	double firstPrior(const double &left);
	double secondPrior(const double& left);
};
