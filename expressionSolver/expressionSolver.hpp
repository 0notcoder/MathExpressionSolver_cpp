#pragma once
#include <string>
#include <vector>

extern const enum class tokenType;
extern const enum class symbolType;

inline int getNumberFromChar(const char &symbol);

struct Token {
private:
	double value;
	tokenType type;

public:
	Token(double value, tokenType type) : value(value), type(type) {};

	double getValue() const;
	tokenType getType() const;

	static symbolType typifySymbol(const char &symbol);
};

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
