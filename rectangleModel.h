#ifndef IMAGECOMPRESSION_RECTANGLEMODEL_H
#define IMAGECOMPRESSION_RECTANGLEMODEL_H

#include <vector>
#include "matrix.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

class RectangleModel {
private:
    int startX;
    int startY;
    vector<double> vectorX;
    Matrix X;
public:
    RectangleModel(int, int);
    ~RectangleModel();
    void createMatrixX();
    void addElement(double);
    int getStartX();
    void setStartX(int);
    int getStartY();
    void setStartY(int);
    vector<double> getVectorX();
    void setVectorX(vector<double>&);
    void setX(Matrix);
    Matrix getX();
};



#endif //IMAGECOMPRESSION_RECTANGLEMODEL_H
