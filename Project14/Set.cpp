#include "Set.h"
#include "Stack.h"
#include <stdexcept>
#include <iostream>
#include <vector>


std::map<char, int> Queue::priority = { {'(', 0}, {')', 1}, {'+', 2}, {'-', 2},
{'*', 3}, {'/', 3} };

Queue::Queue() : infix(""), postfix(""), answer(0) {}

Queue::Queue(Queue& other)
	:infix(other.infix), postfix(other.postfix), answer(other.answer) {}

Queue::Queue(std::string s) :postfix(""), infix(""), answer(0)
{
	int errors_number;
	s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
	errors_number = check_expression(s);
	if (errors_number) {
		std::string error_decritioin = "В выражении неверно расставлены скобки.\nКоличество ошибок : " + std::to_string(errors_number);
		throw std::invalid_argument(error_decritioin);
	}

	infix = s;
}

int Queue::check_expression(std::string expression) {
	Stack s;
	int error_counter = 0;
	int bracket_number = 0;
	std::vector<std::pair<int, int>> brackets;

	for (int i = 0; i < expression.size(); i++) {
		if (expression[i] == '(')
			s.push(++bracket_number);
		else if (expression[i] == ')') {
			bracket_number++;
			if (s.is_empty()) {
				brackets.push_back({ 0, bracket_number });
				error_counter++;
			}
			else
				brackets.push_back({ s.pop(), bracket_number });
		}
	}

	while (!s.is_empty()) {
		brackets.push_back({ s.pop(), 0 });
		error_counter++;
	}
	if (brackets.size()) {
		std::cout << "(\t)\n";
		for (std::pair<int, int> b : brackets) {
			std::cout << b.first << '\t' << b.second << '\n';
		}
	}
	return error_counter;
}

void Queue::to_postfix() {
	Stack s;
	char c, operation;
	bool un_minus = false;
	postfix = "";
	for (int i = 0; i < infix.size(); i++) {
		c = infix[i];
		if (is_operation(c)) {
			if (un_minus) {
				postfix += " - ";
				un_minus = false;
			}
			if (s.is_empty() || priority[c] == 0 || priority[c] > priority[s.top()]) {
				if ((i == 0 || infix[i - 1] == '(') && c == '-') {
					un_minus = true;
					postfix += "0";
				}
				else
					s.push(c);
				if (c != '(' && c != ')' && postfix.size() > 0 &&
					postfix[postfix.size() - 1] != ' ')
					postfix += ' ';
			}
			else {
				while (!s.is_empty() && priority[s.top()] >= priority[c]) {
					operation = s.pop();
					if (operation == ')')
						continue;
					if (postfix[postfix.size() - 1] != ' ')
						postfix += ' ';
					postfix += operation;
				}
				if (postfix.size() > 1 && postfix[postfix.size() - 1] != ' ')
					postfix += ' ';
				if (c != ')')
					s.push(c);
				else
					s.pop();
			}
		}
		else
			postfix += c;
	}
	while (!s.is_empty()) {
		operation = s.pop();
		if (operation == ')' || operation == '(')
			continue;
		if (postfix.size() > 0 && postfix[postfix.size() - 1] != ' ')
			postfix += ' ';
		postfix += operation;
	}
}

double Queue::calculate() {
	std::string expression;
	std::pair<double, double> operands;
	double res, operand;
	Stack s;
	expression = "";
	for (int i = 0; i <= postfix.size(); i++) {
		if (i != postfix.size() && postfix[i] != ' ') {
			expression += postfix[i];
			continue;
		}
		if (expression == "")
			continue;

		if (is_operation(expression[0])) {
			for (int j = 0; j < 2; j++) {
				if (!s.is_empty())
					if (j == 0)
						operands.second = s.pop();
					else
						operands.first = s.pop();
				else
					throw std::logic_error("Недостаточно операндов для вычисления");
			}
			res = execute_operation(expression[0], operands);
			s.push(res);
		}
		else {
			try {
				operand = std::stod(expression);
				s.push(operand);
			}
			catch (std::exception e) {
				throw std::logic_error("Некорректный операнд");
			}
		}
		expression = "";
	}
	if (s.is_empty())
		throw std::logic_error("Произошла ошибка при вычислении выражения");
	answer = s.pop();
	return answer;
}

double Queue::execute_operation(char op, std::pair<double, double>
	operands) {
	double res;
	res = 0;
	if (op == '+')
		res = operands.first + operands.second;
	else if (op == '-')
		res = operands.first - operands.second;
	else if (op == '*')
		res = operands.first * operands.second;
	else if (op == '/') {
		if (operands.second == 0)
			throw std::exception("Деление на ноль");
		res = operands.first / operands.second;
	}
	return res;
}

std::ostream& operator<<(std::ostream& os, const Queue& exp) {
	os << "Инфиксная форма:\n" << exp.infix << '\n';
	os << "Постфиксная форма:\n" << exp.postfix << '\n';
	os << "Ответ: " << exp.answer;
	return os;
}

std::istream& operator>>(std::istream& is, Queue& exp) {
	std::string s;
	std::cin.seekg(std::cin.eof());
	getline(is, s);
	Queue tmp(s);
	exp = tmp;
	exp.to_postfix();
	exp.calculate();
	return is;
}

bool Queue::is_operation(char c) {
	return (priority.count(c));
}

std::string Queue::get_postfix() {
	return postfix;
}

double Queue::get_result() {
	return answer;
}