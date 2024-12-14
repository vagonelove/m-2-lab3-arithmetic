// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__
#include <string>
#include <vector>
#include <iostream>
#include "stack.h"

using namespace std;

const string Symbols = "0123456789.()+-/* ";

struct Lexema
{
private:
	char operation;
	double value;
	bool type;
public:
	Lexema() = default;
	Lexema(const double& _value)
	{
		value = _value;
		type = true;
	}
	Lexema(const char& _operation)
	{
		operation = _operation;
		type = false;
	}
	void printLexem()
	{
		if (type)
			std::cout << value << " ";
		else
			std::cout << operation << " ";
	}
	double getValue() { return value; }
	char getOperation() { return operation; }
	bool getType() { return type; }
	int priority();
};
class Arithmetic
{
public:
	vector<Lexema> smbls;
	Arithmetic() = default;
	void divide(string& expression);
	void ToPostfix();
	double calculate();
	void print();
};
bool checkBrackets(const string& s);
bool checkSymbols(const string& s);
bool isCorrect(const string& s);
#endif