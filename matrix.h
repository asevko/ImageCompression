#ifndef IMAGECOMPRESSION_MATRIX_H
#define IMAGECOMPRESSION_MATRIX_H

#include <vector>
#include <cassert>
#include <iostream>

using  namespace std;

class Matrix {
private:
    int n;
    int m;
    double **matrix;
public:
    Matrix(){};
    Matrix(int n, int m);
    Matrix(int n, int m, double **array);
    Matrix(int n, int m, bool random);
    virtual double getValue(int i, int j);
    virtual void changeValue(int i, int j, double newValue);
    virtual int getM() { return this->m; };
    virtual int getN() { return this->n; };
    explicit Matrix(vector<double>);
    ~Matrix();
    Matrix transpose();

//    friend Matrix operator=(Matrix &l, const Matrix &r){
//        for (int i = 0; i < l.n; ++i) {
//            delete []l.matrix[i];
//        }
//        return  Matrix(r.n, r.m, r.matrix);
//    }
    friend Matrix operator+(const Matrix &l, const Matrix &r){
        assert(l.m == r.m && l.n == r.n);
        for (int i = 0; i < l.n; i++) {
            for (int j = 0; j < l.m; j++) {
                l.matrix[i][j] += r.matrix[i][j];
            }
        }
        return Matrix(l.n, l.m, l.matrix);
    }
    friend Matrix operator+(const Matrix &l, double x){
        for (int i = 0; i < l.n; i++) {
            for (int j = 0; j < l.m; j++) {
                l.matrix[i][j] += x;
            }
        }
        return Matrix(l.n, l.m, l.matrix);
    }
    friend Matrix operator*(const Matrix &l, const double x){
        for (int i = 0; i < l.n; i++) {
            for (int j = 0; j < l.m; j++) {
                l.matrix[i][j] *= x;
            }
        }
        return Matrix(l.n, l.m, l.matrix);
    }

    friend Matrix operator*(const Matrix &l, const Matrix &r){
        assert(l.m == r.n);
        int n = l.n, m = r.m;
        auto mat = new double* [n];
        for (int i = 0; i < n; i++) {
            mat[i] = new double [m];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                double sum = 0;
                for (int k = 0; k < r.n; k++) {
                    sum += l.matrix[i][k] * r.matrix[k][j];
                }
                mat[i][j] = sum;
            }
        }
        return Matrix(n, m, mat);
    }
    friend Matrix operator-(const Matrix &l, const Matrix &r){
        assert(l.m == r.m && l.n == r.n);
        for (int i = 0; i < l.n; i++) {
            for (int j = 0; j < l.m; j++) {
                l.matrix[i][j] -= r.matrix[i][j];
            }
        }
        return Matrix(l.n, l.m, l.matrix);
    }
    void show();
};


#endif //IMAGECOMPRESSION_MATRIX_H
