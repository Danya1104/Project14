#include "Stack.h"

Stack::Stack(size_t sz) : max_size(sz), cur_size(0) {
	elements = new double[sz];
}

Stack::Stack(const Stack& other) : max_size(other.max_size), cur_size(other.cur_size) {
	elements = new double[max_size];
	for (int i = 0; i < cur_size; i++) {
		elements[i] = other.elements[i];
	}
}

Stack::~Stack() {
	delete elements;
}

bool Stack::is_empty() {
	if (cur_size == 0)
		return true;
	return false;
}

bool Stack::is_full() {
	if (cur_size == max_size)
		return true;
	return false;
}

void Stack::push(double elem) {
	elements[cur_size++] = elem;
}

double Stack::pop() {
	return elements[--cur_size];
}

double Stack::top() {
	return elements[cur_size - 1];
}