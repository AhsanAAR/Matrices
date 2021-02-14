#include "Matrix_19001.h"
#include <iostream>
#include <fstream>
#include <iomanip>
 
using namespace std;

void Matrix::setC(int Cols) { C = (Cols >= 0) ? Cols : 0; }
void Matrix::setR(int Rows) { R = (Rows>= 0) ? Rows: 0; }
void Matrix::print() const {
    cout << "\n\n\t\tMatrix of size " << R << " x " << C <<"\n\n";
    for (int ri = 0; ri < R; ri++) {
        cout << "\t\t";
        for (int ci = 0; ci < C; ci++)
            cout << setw(2) << Vs[ri][ci] << ' ';
        cout << "\n\n";
    }
}
void Matrix::deepCopy(const Matrix& M) {
    this->allocate(M.R, M.C);
    for (int ri = 0; ri < R; ri++)
        for (int ci = 0; ci < C; ci++)
            Vs[ri][ci] = M.Vs[ri][ci];
}
void Matrix::allocate(int Rows, int Cols, int v) {
    if (Vs != nullptr)
        deleteM();
    setR(Rows);
    setC(Cols);
    Vs = new int* [R];
    for (int ri = 0; ri < R; ri++){
        Vs[ri] = new int[C];
        for (int ci = 0; ci < C; ci++)
            Vs[ri][ci] = v;
    }
}
void Matrix::deleteM() {
    for (int ri = 0; ri < R; ri++)
        delete[] Vs[ri];
    delete[] Vs;
    Vs = nullptr;
    R = C = 0;
}
void Matrix::load(ifstream& reader) {
    for (int ri = 0; ri < R; ri++)
        for (int ci = 0; ci < C; ci++)
            reader >> Vs[ri][ci];
}
Matrix Matrix::operator!() const {
    Matrix ret(C, R);
    for (int ri = 0; ri < R; ri++)
        for (int ci = 0; ci < C; ci++)
            ret.Vs[ci][ri] = Vs[ri][ci];
    return ret;
}
Matrix Matrix::rotate(int n) const {
    Matrix ret = *this;
    n = n % 360;
    n = 360 + n;
    n = n % 360;
    n /= 90;
    for (int i = 0; i < n; i++)
        ret.rotate90();
    return ret;
}

void Matrix::rotate90() {
    Matrix temp(C, R);
    for (int ri = 0; ri < R; ri++)
        for (int ci = 0; ci < C; ci++)
            temp.Vs[ci][temp.C - ri - 1] = Vs[ri][ci];
    *this = temp;
}

Matrix::Matrix() : R (0), C(0), Vs(nullptr){}
Matrix::Matrix(int D) : Matrix() {
    allocate(D, D);
}
Matrix::Matrix(int R, int C) : Matrix() {
    allocate(R, C);
}
Matrix::Matrix(int R, int C, int V) : Matrix() {
    allocate(R, C, V);
}
Matrix::Matrix(ifstream& reader) : Matrix() {
    int Rows, Cols;
    reader >> Rows >> Cols;
    allocate(Rows, Cols);
    load(reader);
}
Matrix::~Matrix() {
    deleteM();
}
Matrix::Matrix(const Matrix& M) : Matrix() {
    deepCopy(M);
}

void Matrix::operator=(const Matrix& M) {
    deepCopy(M);
}

Matrix Matrix::operator+(const Matrix& M) const {
    Matrix ret;
    if(R == M.R && C == M.C) {
        ret.allocate(R, C);
        for (int ri = 0; ri < M.R; ri++)
            for (int ci = 0; ci < M.C; ci++)
                ret.Vs[ri][ci] = this->Vs[ri][ci] + M.Vs[ri][ci];
    }
    return ret;
}
Matrix Matrix::operator+(const int& i)const {
    Matrix plus(R,C,i);
    plus.print();
    Matrix ret = *this + plus;
    return ret;
}
Matrix Matrix::operator-(const Matrix& M)const {
    Matrix ret;
    if (R == M.R && C == M.C) {
        ret.allocate(R, C);
        for (int ri = 0; ri < M.R; ri++)
            for (int ci = 0; ci < M.C; ci++)
                ret.Vs[ri][ci] = this->Vs[ri][ci] - M.Vs[ri][ci];
    }
    return ret;
}
Matrix Matrix::operator-(const int& i)const {
    Matrix sub(R, C, i);
    return *this - sub;
}
Matrix Matrix::operator*(const Matrix& M)const {
    Matrix ret;
    if (C == M.R){
        ret.allocate(R, M.C);
        for (int ri = 0; ri < ret.R; ri++)
            for (int ci = 0; ci < ret.C; ci++)
                for (int i = 0; i < C; i++)
                    ret.Vs[ri][ci] += this->Vs[ri][i] * M.Vs[i][ci];
    }
    return ret;
}
Matrix Matrix::operator*(const int& i)const {
    Matrix ret;
    Matrix mult(R, C, i);
    ret.allocate(R, C);
    for (int ri = 0; ri < R; ri++)
        for (int ci = 0; ci < C; ci++)
            ret.Vs[ri][ci] = this->Vs[ri][ci] * mult.Vs[ri][ci];
    return ret;
}
Matrix Matrix::operator-()const {
    return *this * -1;
}

void Matrix::operator--() {
    *this = *this - 1;
}
void Matrix::operator++() {
    *this = *this + 1;
}
void Matrix::operator+=(const Matrix& M){    *this = *this + M;}
void Matrix::operator+=(const int& i) {     *this = *this + i;}
void Matrix::operator-=(const Matrix& M) { *this = *this - M; }
void Matrix::operator-=(const int& i) { *this = *this - i; }
void Matrix::operator*=(const Matrix& M) {
    *this = *this * M;
}
void Matrix::operator*=(const int&i ) { *this = *this * i; }

bool Matrix::operator==(const Matrix& M) const{
    if (R != M.R || C != M.C)
        return false;
    for (int ri = 0; ri < R; ri++)
        for (int ci = 0; ci < C; ci++)
            if (Vs[ri][ci] != M.Vs[ri][ci])
                return false;
    return true;
}



