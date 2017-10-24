#include "matrix.h"

Matrix::Matrix(vector<double> vector) {
    this->n = 1;
    this->m = (int)vector.size();
    matrix = new double* [n];
    matrix[0] = new double [vector.size()];
    for (int i = 0; i < m; i++) {
        matrix[0][i] = vector.at(i);
    }
}

Matrix::Matrix(int n, int m) {
    this->n = n;
    this->m = m;
    matrix = new double* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double [m];
    }
}

Matrix::Matrix(int n, int m, double **array) {
    this->n = n;
    this->m = m;
    matrix = new double* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double [m];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = array[i][j];
        }
    }
}

Matrix::Matrix(int n, int m, bool random){
    srand(time(NULL));
    this->n = n;
    this->m = m;
    matrix = new double* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double [m];
    }
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            matrix[i][j] = ((double) rand() / (RAND_MAX));
//        }
//    }
}

Matrix::~Matrix() {
//    for (int i = 0; i < n; ++i) {
//        delete []matrix[i];
//    }
//    delete[] matrix;
}

Matrix Matrix::transpose() {
    Matrix mat(m, n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            mat.matrix[i][j] = matrix[j][i];
        }
    }

    return mat;
}

void Matrix::show() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; ++j) {
            std::cout << matrix[i][j] << " ";
            if (j == m - 1)
                std::cout << endl;
        }
    }
}

void Matrix::changeValue(int i, int j, double newValue) {
    matrix[i][j] = newValue;
}

double Matrix::getValue(int i, int j) {
    return matrix[i][j];
}