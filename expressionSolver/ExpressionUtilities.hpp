#pragma once

const enum class tokenType : int {
	sign = 1, number = 2
};

const enum class symbolType : int {
	end = 0, digit = 1, signFirst = 2, signSecond = 3, point = 4
};

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