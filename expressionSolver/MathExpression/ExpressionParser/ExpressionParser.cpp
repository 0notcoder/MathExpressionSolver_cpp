#include "ExpressionParser.hpp"

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

void (ExpressionParser:: *ExpressionParser::getNextMethod())() {
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

	void (ExpressionParser:: * nextMethod)() = getNextMethod();

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

	case symbolType::signFirst:
		currentType = tokenType::firstSign;
		
		break;

	case symbolType::signSecond:
		currentType = tokenType::secondSign;

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