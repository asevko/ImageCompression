#include "rectangleModel.h"

RectangleModel::RectangleModel(int startX, int startY) {
    this->startX = startX;
    this->startY = startY;
}

RectangleModel::~RectangleModel() {
    //delete X;
}

void RectangleModel::createMatrixX() {
    X = Matrix(vectorX); //deleted .transpose()
}

void RectangleModel::addElement(double newElement) {
    vectorX.push_back(newElement);
}

int RectangleModel::getStartX() {
    return this->startX;
}

int RectangleModel::getStartY() {
    return  this->startY;
}
//
//void RectangleModel::setStartX(int startX) {
//    this->startX = startX;
//}
//
//void RectangleModel::setStartY(int startY) {
//    this->startY = startY;
//}
//
//vector<double> RectangleModel::getVectorX() {
//    return this->vectorX;
//}
//
//void RectangleModel::setVectorX(vector<double> &vectorX) {
//    this->vectorX = vectorX;
//}

Matrix RectangleModel::getX() {
    return this->X;
}
//
//void RectangleModel::setX(Matrix X) {
//    this->X = X;
//}