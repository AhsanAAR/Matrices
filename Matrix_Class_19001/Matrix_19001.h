#include <iostream>
#include <fstream>
#pragma once

using namespace std;

class Matrix
{
private:
	int R, C;
	int** Vs;
	void setR(int);
	void setC(int);
	void allocate(int, int, int = 0);
	void deleteM();
	void load(ifstream&);
	void deepCopy(const Matrix&);
	void rotate90();
public:
	void print() const;
	Matrix();
	Matrix(const Matrix&);
	Matrix(int);
	Matrix(int, int);
	Matrix(int, int, int);
	Matrix(ifstream&);
	~Matrix();
	void operator=(const Matrix&);
	void operator--();
	void operator++();
	Matrix operator+(const Matrix&) const;
	Matrix operator+(const int&) const;
	Matrix operator-(const Matrix&)const;
	Matrix operator-(const int&)const;
	Matrix operator*(const Matrix&)const;
	Matrix operator*(const int&)const;
	Matrix operator-()const;
	Matrix operator!() const;
	Matrix rotate(int) const;

	void operator+=(const Matrix&);
	void operator+=(const int&);
	void operator-=(const Matrix&);
	void operator-=(const int&);
	void operator*=(const Matrix&);
	void operator*=(const int&);

	bool operator==(const Matrix&) const;
};

