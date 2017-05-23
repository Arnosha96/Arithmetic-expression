#pragma once
#include <sstream>
#include<stdio.h>
#include <string> 
#include <cstdlib>
#include <conio.h>
#include <iostream>
#include "Stack1.h" 

using namespace std;
int Priority(char op){ // получить приоритет операции
	int Prt;
	switch (op) {
	case '*':
	case '/': Prt = 3; break;
	case '+':
	case '-':  Prt = 2; break;
	case '(':  Prt = 1; break;
	case '=': Prt = 0; break;
	default: Prt = -1;
	}
	return Prt;
}
int IsOperation(char op)
{// проверка на знак операции
	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '=') return 1;
	else return 0;
}
bool IsOperand(char c)
{
	switch (c)
	{
	case '0': return true;
	case '1': return true;
	case '2': return true;
	case '3': return true;
	case '4': return true;
	case '5': return true;
	case '6': return true;
	case '7': return true;
	case '8': return true;
	case '9': return true;
	case ',': return true;
	case '.': return true;
	default: return false;
	}
}

string convert_exp(string &InfixExp)
{
	char ch, t;
	string PolishExp("");
	int pos(0), pos_(0);


	Stack1 <char> OperationStack(10);
	ch = InfixExp[pos];
	do
	{
		
		if (IsOperand(ch)) {
			string operand;
			while ((pos < InfixExp.length()) && IsOperand(ch))
			{
				operand += InfixExp[pos];
				pos++;
				ch = InfixExp[pos];
			}
			PolishExp += " " + operand;
		}
		else if (ch == '(') {
			OperationStack.Put(ch); pos++;
		}
		else if (ch == ')')
		{
			while (1)
			{
				t = OperationStack.Get();
				if (t == '(') {
					
					break; }
				PolishExp += t; 
			}
			pos++;
		}

		else if (IsOperation(ch))
		{
			while (!OperationStack.IsEmpty())
			{
				t = OperationStack.Get();
				if (Priority(ch) <= Priority(t)) PolishExp += t;
				else { OperationStack.Put(t); { break;  } }
			}
			OperationStack.Put(ch);
			pos++;
			
		}
		ch = InfixExp[pos];
	} while (ch != '=');


	while (!OperationStack.IsEmpty())
	{
		t = OperationStack.Get();
		PolishExp += t;	
	};
	
	PolishExp += '=';
	return PolishExp;

}
 double calc(string &PolishExp)
{ 
	Stack1 <double> CalcStack(25);


int pos_(0);
double op_r(0), op_l(0), rez(0);
char ch;
ch = PolishExp[pos_];
	do 
	{
		
		if (ch == ' ') pos_++;
	    if (IsOperand(ch)) {
			string operand;
			while ((pos_ < PolishExp.length()) && IsOperand(ch))
			{
				operand += PolishExp[pos_];
				ch = PolishExp[++pos_];
 			}
			
			double o = atof(operand.c_str());
			CalcStack.Put(o);
			
		}
		
		else if (IsOperation(ch)) {
			 
			op_r = CalcStack.Get();
			op_l = CalcStack.Get();

			switch (ch)
			{
			case '+':CalcStack.Put(op_l + op_r); break;
			case '-':CalcStack.Put(op_l - op_r); break;
			case '*':CalcStack.Put(op_l * op_r); break;
			case '/':CalcStack.Put(op_l / op_r); break;
			}
			pos_++;
		}

		ch = PolishExp[pos_];
	} while (ch != '=');
	 
	rez = CalcStack.Get();
	return rez;

}
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Использование польской нотации для вычисления выражения" << endl << endl;
	cout << "Введите выражение " << endl;
	string s_inf;
	cin >> s_inf;
	cout << endl;
	string str_postf = convert_exp(s_inf);
	cout << "Инфиксная запись: " << s_inf << endl;
	cout << "Постфиксная запись: " << str_postf << endl;
	cout << "Результат " << calc(str_postf) << endl;
	_getch();
	return 0;
}
