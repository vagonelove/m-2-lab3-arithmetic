// реализация функций и классов для вычисления арифметических выражений

#include "../include/arithmetic.h"

void Arithmetic::divide(string& expression)
{
	unsigned length = expression.length();
	string stringForNumber;
	double doubleNumber;
	unsigned i = 0, unary_minus_Yes = 0;
	while (i < length)
	{
		if (expression[i] == ' ')
			i++;
		if (expression[i] == '+' || expression[i] == '*' || expression[i] == '/')
		{
			Lexema operation(expression[i]);
			smbls.push_back(operation);
			i++;
			unary_minus_Yes = 1;
		}
		else if (expression[i] == '-')
		{
			if (i == 0)
			{
				Lexema unary_minus('_');
				smbls.push_back(unary_minus);
				i++;
				continue;
			}
			if (i > 0)
			{
				if (unary_minus_Yes == 1)
				{
					Lexema unary_minus('_');
					smbls.push_back(unary_minus);
					i++;

				}
				else if (unary_minus_Yes == 0)
				{
					Lexema minus('-');
					smbls.push_back(minus);
					i++;
					unary_minus_Yes = 1;
				}
			}
		}
		else if (expression[i] >= '0' && expression[i] <= '9' || (expression[i] == '.'))
		{
			int pointCounter = 0;
			while (expression[i] >= '0' && expression[i] <= '9' || (expression[i] == '.'))
			{
				stringForNumber += expression[i];
				i++;
				if (expression[i] == '.')
				{
					pointCounter++;
				}
				if (pointCounter > 1)
				{
					throw "More than one point in the number";
				}
			}
			unary_minus_Yes = 0;
			doubleNumber = stof(stringForNumber);
			Lexema number(doubleNumber);
			smbls.push_back(number);
			stringForNumber.clear();
		}
		else if (expression[i] == ')' || expression[i] == '(')
		{
			Lexema bracket(expression[i]);
			smbls.push_back(bracket);
			i++;
			if (expression[i] == ')')
				unary_minus_Yes = 0;
			else
				unary_minus_Yes = 1;
		}
	}
}
void Arithmetic::ToPostfix()
{
	unsigned size = smbls.size();
	vector<Lexema> postfix;
	Stack<Lexema> operations;
	for (unsigned i = 0; i < size; i++)
	{
		if (smbls[i].getType() == true)
			postfix.push_back(smbls[i]);
		else
		{
			if (smbls[i].getOperation() == '(')
			{
				operations.push(smbls[i]);
				continue;
			}
			else if (smbls[i].getOperation() == ')')
			{
				while (operations.getTop().getOperation() != '(')
				{
					postfix.push_back(operations.pop());
				}
				operations.pop();
				continue;
			}
			if (i > 0 && smbls[i].getOperation() == '_' && smbls[i].getOperation() == '_')
				operations.push(smbls[i]);
			else
			{
				while (!operations.isEmpty() && operations.getTop().priority() >= smbls[i].priority())
					postfix.push_back(operations.pop());
				operations.push(smbls[i]);
			}
		}
	}
	while (!operations.isEmpty())
	{
		postfix.push_back(operations.pop());
	}
	smbls = postfix;
}
void Arithmetic::print()
{
	for (size_t i = 0; i < smbls.size(); i++)
	{
		Lexema lexeme(smbls[i]);
		lexeme.printLexem();
	}
}
int Lexema::priority()
{
	if (operation == '(' || operation == ')')
	{
		return 0;
	}
	else if (operation == '+' || operation == '-')
	{
		return 1;
	}
	else if (operation == '*' || operation == '/')
	{
		return 2;
	}
	else if (operation == '_')
	{
		return 3;
	}
	else
		throw "Priority problem";
}
double Arithmetic::calculate()
{
	Stack<Lexema> stack;
	Lexema termOperand1, termOperand2;
	double operand1, operand2, res;
	for (unsigned i = 0; i < smbls.size(); i++)
	{
		if (smbls[i].getType() == true)
			stack.push(smbls[i].getValue());
		else if (smbls[i].getOperation() == '_')
		{
			res = (-1) * stack.pop().getValue();
			stack.push(res);
			continue;
		}
		else
		{
			termOperand2 = stack.pop();
			termOperand1 = stack.pop();
			operand1 = termOperand1.getValue();
			operand2 = termOperand2.getValue();
			if (smbls[i].getOperation() == '+')
				res = operand1 + operand2;
			if (smbls[i].getOperation() == '-')
				res = operand1 - operand2;
			if (smbls[i].getOperation() == '*')
				res = operand1 * operand2;
			if (smbls[i].getOperation() == '/')
			{
				if (operand2 == 0)
					throw "Division by 0";
				res = operand1 / operand2;
			}

			stack.push(res);
		}
	}
	Lexema result = stack.pop();
	return result.getValue();
}
bool checkBrackets(const string& s)
{
	bool flag = true;
	int count = 0, stringSize = s.length();
	for (int i = 0; i < stringSize; i++)
	{
		if (s[i] == '(')
		{
			count++;
			flag = false;
			if (i < stringSize && (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/'))
			{
				throw "Operation after opening bracket";
			}
			if (i > 0 && s[i - 1] >= '0' && s[i] <= '9')
			{
				throw "Number before opening bracket";
			}
		}
		if (s[i] == ')')
		{
			count--;
			flag = true;
		}
	}
	return (flag == true && count == 0);
}
bool checkSymbols(const string& s)
{
	bool flag = false;
	int stringSize = s.length(), allowedTermsSize = Symbols.length();
	for (int i = 0; i < stringSize; i++)
	{
		for (int j = 0; j < allowedTermsSize; j++)
		{
			if (s[i] != Symbols[j])
			{
				flag = false;
				continue;
			}
			else
			{
				flag = true;
				break;
			}
		}
		if (flag)
			continue;
		else
			return false;
	}
	return true;
}
bool isCorrect(const string& s)
{
	if (!checkBrackets(s))
	{
		throw "Bracket in your expression are wrong";
	}
	else if (!checkSymbols(s))
	{
		throw "You should use only allowed symbols: 0123456789.()+-/* ";
	}
	else if (s[0] == '+' || s[0] == '*' || s[0] == '/')
	{
		throw "Operation is on the first place in the expression";
	}
	else if (s[s.length() - 1] == '+' || s[s.length() - 1] == '-' || s[s.length() - 1] == '*' || s[s.length() - 1] == '/')
	{
		throw "Operation is at the end of the expression";
	}
	else
		return true;
}