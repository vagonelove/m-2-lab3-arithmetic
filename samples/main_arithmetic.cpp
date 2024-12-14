// реализаци€ пользовательского приложени€
#include "../include/arithmetic.h"

using namespace std;

int main()
{
	string str;
	for (int i = 0; i < 100; i++)
	{
		cout << "Enter your expression:\n";
		getline(cin, str);
		isCorrect(str);
		Arithmetic res;
		cout << "Your expression is:\n";
		res.divide(str);
		res.print();
		cout << endl;
		res.ToPostfix();
		cout << endl;
		double result = res.calculate();
		cout << "Result:\n" << result << endl;
	}
}