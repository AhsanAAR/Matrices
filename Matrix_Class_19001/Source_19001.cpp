#include <iostream>
#include <fstream>
#include <conio.h>
#include "Matrix_19001.h"

using namespace std;

int main() {
	ifstream reader("Input_19001.txt");
	int NOM;
	reader >> NOM;
	Matrix** Ms = new Matrix * [NOM];

	for (int i = 0; i < NOM; i++)
		Ms[i] = new Matrix(reader);
	bool invalid;
	char dummy;
	int in, lv, r1, r2;
	Matrix(Matrix:: * fptr)(const Matrix&) const = nullptr;
	do {
		system("cls");
		invalid = false;
		for (int i = 0; i < NOM; i++) {
			cout << "\n\n\t\tMatrix number " << i + 1;
			Ms[i]->print();
		}
		cout << "\n\n\t\tAssignment Matrix number: ";
		cin >> lv;
		lv--;
		if (lv < 0 || lv >= NOM)
			continue;
		cout << "\n\t\tOperator(+,-,*, ! (transpose), (r)otate, (d)ecrement--, (i)ncrement++: ";
		do {
			cin >> dummy;
			switch (dummy) {
			case '+':
				fptr = &Matrix::operator+;
				break;
			case '-':
				fptr = &Matrix::operator-;
				break;
			case '*':
				fptr = &Matrix::operator*;
				break;
			case '!':
			case 'r':
			case 'd':
			case 'i':
				break;
			default:
				continue;
			}
			break;
		} while (true);
		if (dummy == 'd') {
			--Ms[lv][0];
			continue;
		}
		else if (dummy == 'i') {
			++Ms[lv][0];
			continue;
		}
		if (dummy == 'r') {
			do {
				cout << "\n\n\t\tInput degree: ";
				cin >> in;
			} while (in % 90 != 0);
		}
		cout << "\n\n\t\tMatrix number one: ";
		cin >> r1;
		r1--;
		if (r1 < 0 || r1 >= NOM)
			continue;
		if (dummy == '+' || dummy == '-' || dummy == '*') {
			cout << "\n\n\t\tMatrix number two: ";
			cin >> r2;
			r2--;
			if (r2 < 0 || r2 >= NOM)
				continue;
			Ms[lv][0] = (Ms[r1][0].*fptr)(Ms[r2][0]);
			continue;
		}
		else if (dummy == '!')
			Ms[lv][0] = !Ms[r1][0];
		else if (dummy == 'r')
			Ms[lv][0] = Ms[r1]->rotate(in);
	} while (true);
	return _getch();
}