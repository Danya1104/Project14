#include "Set.h"
#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");
	int exit, menu;
	exit = 1;
	Queue exp;
	bool vector_type;

	while (exit == 1) {
		system("CLS");
		try {
			cout << "������� ���������:" << endl;
			cin >> exp;
			cout << exp << endl;
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
		cout << "������� 1, ����� ����������" << endl;
		cin >> exit;
	}
}