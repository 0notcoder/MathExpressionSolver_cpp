#include "ExpressionUtilities.hpp"

int getNumberFromChar(const char &symbol) {
	return symbol - 48;
}

void Token::operator=(Token &other) {
	this->value = other.getValue();
	this->type = other.getType();
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
