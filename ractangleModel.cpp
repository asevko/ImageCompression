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

Matrix RectangleModel::getX() {
    return this->X;
}

