#include "expressionSolver.hpp"

double ExpressionSolver::solve(const std::string &expression) {
	tokens = parser->parse(expression);
	currentTokenIt = tokens.begin();

	Token left;
	if (getCurrentTokenShift(left) == returnCode::error) return left.getValue();

	Token operatorToken;
	getCurrentToken(operatorToken);

	switch (operatorToken.getType()) {
	case tokenType::firstSign:
		return firstPrior(left.getValue());

	case tokenType::secondSign:
		return secondPrior(left.getValue());
	}

	throw "Error..";
	return 0;
}

double ExpressionSolver::firstPrior(const double& left) {
	Token operatorToken;
	Token right;

	getCurrentTokenShift(operatorToken);
	getCurrentTokenShift(right);

	double rightValue = right.getValue();

	Token nextOperator;
	if (getCurrentToken(nextOperator) != returnCode::error) {
		switch (nextOperator.getType()) {
		case tokenType::firstSign:
			rightValue = firstPrior(rightValue);
			break;

		case tokenType::secondSign:
			rightValue = secondPrior(rightValue);
		}
	}

	switch (static_cast<char>(operatorToken.getValue())) {

	case '+':
		return left + rightValue;
		break;
	case '-':
		return left - rightValue;
		break;
	}

	throw "Error on ...";
	return 0;
}

double ExpressionSolver::secondPrior(const double& left) {
	Token operatorToken;
	Token right;

	getCurrentTokenShift(operatorToken);
	getCurrentTokenShift(right);

	double rightValue = right.getValue();
	
	double result;

	switch (static_cast<char>(operatorToken.getValue())) {

	case '*':
		result = left * rightValue;
		break;
	case '/':
		result = left / rightValue;
		break;

	default:
		result = 0;

		throw "Error calculating second prior expression at ... " + (char)operatorToken.getValue();
		break;
	}

	Token nextOperatorToken;
	if (getCurrentToken(nextOperatorToken) == returnCode::error) return result;

	switch (nextOperatorToken.getType()) {

	case tokenType::firstSign:
		return firstPrior(result);

		break;
	
	case tokenType::secondSign:
		return secondPrior(result);

		break;
	}

	throw "Error...";

	return 0;
}

returnCode ExpressionSolver::getCurrentToken(Token& token) const {
	if (currentTokenIt == tokens.end()) return returnCode::error;

	token = *currentTokenIt;
	
	return returnCode::success;
}

void ExpressionSolver::shiftCurrentToken() {
	currentTokenIt++;
}

returnCode ExpressionSolver::getCurrentTokenShift(Token &token) {
	if (currentTokenIt == tokens.end()) return returnCode::error;

	token = *currentTokenIt;
	currentTokenIt++;

	return returnCode::success;
}

bool ExpressionSolver::checkEndOfTokens() const {
	return currentTokenIt == tokens.end();
}
