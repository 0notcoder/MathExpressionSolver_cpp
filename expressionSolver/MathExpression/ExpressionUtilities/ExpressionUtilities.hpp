#pragma once

const enum class tokenType : int {
	firstSign, secondSign, number
};

const enum class symbolType : int {
	end = 0, digit = 1, signFirst = 2, signSecond = 3, point = 4
};

const enum class returnCode : int {
	error = -1, success = 1
};

inline int getNumberFromChar(const char &symbol);

struct Token {
private:
	double value;
	tokenType type;

public:
	Token() = default;
	Token(double value, tokenType type) : value(value), type(type) {};
	Token(const Token &other) : value(other.getValue()), type(other.getType()) {};
	Token(Token &&other) : value(other.getValue()), type(other.getType()) {};

	void operator=(Token &other);

	double getValue() const;
	tokenType getType() const;

	static symbolType typifySymbol(const char &symbol);
};