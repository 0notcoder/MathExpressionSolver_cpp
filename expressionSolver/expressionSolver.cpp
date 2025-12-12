#include "expressionSolver.hpp"

const enum class tokenType : int {
	sign = 1, number = 2
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

int Token::getValue() const {
	return value;
}

tokenType Token::getType() const {
	return type;
}


std::vector<Token> ExpressionParser::parse(const std::string &expression) {
	std::vector<Token> tokens;
	
	return tokens;
}

char ExpressionParser::getCurrentSymbol() const {
	return *currentSymbolIt;
}

void ExpressionParser::shiftCurrentSymbol() {
	currentSymbolIt++;
}

char ExpressionParser::getCurrentSymbolShift() {
	return *(currentSymbolIt++);
}

void (ExpressionParser::*getNextMethod(const char &symbol))() {
	switch (symbol) {
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '0':
	case '.':
		return &ExpressionParser::numberToken;
		break;

	case '+':
	case '-':
	case '*':
	case '/':

		break;
	}

	throw "Error parsing at " + symbol;
	return nullptr;
}

void ExpressionParser::numberToken() {
	char currentSymbol = getCurrentSymbolShift();
	int number = currentSymbol - 48;

	switch (currentSymbol) {
	case '.':
		overPoint = 1;
		break;

	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '0':
		if (overPoint) {
			buff += pow(10, -overPoint) * number;
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

	void (ExpressionParser::*t)() = getNextMethod(getCurrentSymbol());
	t();
}
