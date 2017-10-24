#ifndef IMAGECOMPRESSION_IMAGEMODEL_H
#define IMAGECOMPRESSION_IMAGEMODEL_H

#include <iostream>
#include "rectangleModel.h"
#include <armadillo>

using namespace std;
using namespace cv;
using namespace arma;

class ImageModel {
private:
    int RGB = 3;
    int iWidth;
    int iHeight;
    int n; ///высота прямоугольника
    int m; ///ширина прямоугольника
    int p; ///заданное пользователем число нейронов
    int L; ///количество многоугольников
    int nmRGB;
    double e; ///максимально допустимая ошибка
    double a; ///адаптивный шаг обучения
    mat W; ///матрица весов
    mat W_;
    vector<RectangleModel> rectangles; ///список всех прямоугольников, на которые разбита картинка
    double convertColor(int color);
    int convertRGBToImg(double color);
    double getErrorDegree(mat deltaX);
    void createWeightMatrix();
    void normalizeMatrix(mat matrix);
    void normalizeMatrixes();
    double adaptiveLearningStep(mat matrix);
public:
    explicit ImageModel(char const * path);
    void init();
    void run();
    void createOutputImage();

};

#endif //IMAGECOMPRESSION_IMAGEMODEL_H
