#include "expressionSolver.hpp"

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





