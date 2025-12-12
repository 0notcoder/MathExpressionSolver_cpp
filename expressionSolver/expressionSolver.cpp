#include "expressionSolver.hpp"

const enum class tokenType : int {
	sign = 1, number = 2
};

const enum class symbolType : int {
	end = 0, digit = 1, signFirst = 2, signSecond = 3, point = 4
};

bool ExpressionSolver::checkEnd(const std::string &str, const std::string::iterator &strIt) {
	return (strIt == str.end()) || (*strIt == '\0');
}

double ExpressionSolver::solve(const std::string &expression) {
	this->expression = expression;
	currentIt = this->expression.begin();
	double left = (*currentIt) - 48;

	if (checkEnd(this->expression, currentIt)) return left;

	++currentIt;
	char op = *currentIt;

	switch (op) {
	case ('+'):
	case ('-'):
		return firstPrior(left);

	case ('*'):
	case ('/'):
		return secondPrior(left);
	}

	throw "Error..";
	return 0;
}

double ExpressionSolver::firstPrior(const double& left) {
	double right;
	char op = *currentIt;
	right = *(currentIt+1)-48; 
	if (!checkEnd(expression, currentIt + 2)) {
		currentIt += 2;
		switch (*currentIt) {
		case ('+'):
		case ('-'):
			right = firstPrior(right);
			break;
		case ('*'):
		case ('/'):
			right = secondPrior(right);
		}
	}

	switch (op) {
	case '+':
		return left + right;
		break;
	case '-':
		return left - right;
		break;
	}

	throw "Error on ...";
	return 0;
}

double ExpressionSolver::secondPrior(const double& left) {
	char op = *currentIt;
	
	double right = *(currentIt + 1)-48;
	
	double result;

	switch (op) {
	case '*':
		result = left * right;
		break;
	case '/':
		result = left / right;
		break;

	default:
		result = 0;

		throw "Error calculating second prior expression at ... " + op;
		break;
	}

	if (checkEnd(expression, currentIt+2)) return result;

	currentIt += 2;
	char nextOp = *currentIt;
	switch (nextOp) {
	case ('+'):
	case ('-'):
		return firstPrior(result);
		break;
	
	case ('*'):
	case ('/'):
		return secondPrior(result);
		break;
	}

	throw "Error...";

	return 0;
}

double Token::getValue() const {
	return value;
}

tokenType Token::getType() const {
	return type;
}

symbolType Token::typifySymbol(const char &symbol) {
	int num = getNumberFromChar(symbol);
	if ((num >= 0) && (num <= 9)) return symbolType::digit;

	switch (symbol) {
	case '+': case '-':
		return symbolType::signFirst;

		break;

	case '.':
		return symbolType::point;

	case '*': case '/':
		return symbolType::signSecond;
		
		break;

	case '\0':
		break;

	default:
		throw "Symbol type is not defined: " + symbol;

		break;
	}
}

void ExpressionParser::addToken(const Token &token) {
	tokens.push_back(token);
}

std::vector<Token> ExpressionParser::parse(const std::string &expression) {
	tokens.clear();
	this->expression = expression;
	currentSymbolIt = this->expression.begin();

	(this->*getNextMethod())();

	return this->tokens;
}

char ExpressionParser::getCurrentSymbol() const {
	if (currentSymbolIt == expression.end()) return -1;

	return *currentSymbolIt;
}

void ExpressionParser::shiftCurrentSymbol() {
	currentSymbolIt++;
}

char ExpressionParser::getCurrentSymbolShift() {
	return *(currentSymbolIt++);
}

void (ExpressionParser::*ExpressionParser::getNextMethod())() {
	char currentSymbol = getCurrentSymbol();
	if (currentSymbol == -1) return &ExpressionParser::endState;

	symbolType currentSymbolType = Token::typifySymbol(currentSymbol);
	
	switch (currentSymbolType) {

	// digit or point (possible floating point number)
	case symbolType::digit: case symbolType::point:
		return &ExpressionParser::numberToken;

		break;

	case symbolType::signFirst: case symbolType::signSecond:
		return &ExpressionParser::oneSymbolToken;
		
		break;

	default:
		throw "Error finding next method at " + currentSymbol;

		break;
	}

	throw "Error parsing at " + currentSymbol;
	return nullptr;
}

void ExpressionParser::numberToken() {
	char currentSymbol = getCurrentSymbolShift();
	int number = getNumberFromChar(currentSymbol);

	symbolType currentType = Token::typifySymbol(currentSymbol);

	switch (currentType) {

	case symbolType::point:
		overPoint = 1;
		break;

	case symbolType::digit:
		if (overPoint) {
			buff += pow(10, -1 * overPoint) * number;
			++overPoint;
		}
		else {
			buff *= 10;
			buff += number;
		}

		break; 

	default:
		throw "Error parsing string at " + currentSymbol;
		break;
	}

	void (ExpressionParser::*nextMethod)() = getNextMethod();

	// number ended
	if (nextMethod != &ExpressionParser::numberToken) {
		if (currentSymbol == '.') {
			throw "Unexpected end of floating point number. Expected at least one digit after point.";
		}

		addToken(Token(buff, tokenType::number));

		buff = 0;
		overPoint = 0;
	}
	
	// calling the next method
	(this->*nextMethod)();
}

void ExpressionParser::oneSymbolToken() {
	char currentSymbol = getCurrentSymbolShift();
	symbolType currentSymbolType = Token::typifySymbol(currentSymbol);
	tokenType currentType;

	switch (currentSymbolType) {
	
	case symbolType::signFirst: case symbolType::signSecond:
		currentType = tokenType::sign;
	
		break;

	default:
		currentType = static_cast<tokenType>(-1);

		throw "This symbol is not allowed! " + currentSymbol;
		break;
	}

	addToken(Token(currentSymbol, currentType));

	// calling the next method
	(this->*getNextMethod())();
}

void ExpressionParser::endState() {
	// ...
}

int getNumberFromChar(const char &symbol) {
	return symbol - 48;
}
