#pragma once
class Stack {
private:
	size_t max_size;
	size_t cur_size;
	double* elements;
public:
	explicit Stack(size_t = 1000);
	Stack(const Stack&);
	~Stack();
	bool is_empty();
	bool is_full();
	void push(double);
	double pop();
	double top();
};