#ifndef IMAGECOMPRESSION_RECTANGLEMODEL_H
#define IMAGECOMPRESSION_RECTANGLEMODEL_H

#include <vector>
#include <armadillo>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using  namespace arma;

class RectangleModel {
private:
    int startX;
    int startY;
    vector<double> vectorX;
private:
    mat X;
public:
    RectangleModel(int, int);
    ~RectangleModel();
    void createMatrixX();
    void addElement(double);
    int getStartX();
    int getStartY();
    mat getX();
};



#endif //IMAGECOMPRESSION_RECTANGLEMODEL_H
