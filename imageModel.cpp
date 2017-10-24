#include <cmath>
#include "imageModel.h"

void ImageModel::init() {
cout << "Enter height of rectangle(n):" << endl;
cin >> n;
cout << "Enter width of rectangle(m):" << endl;
cin >> m;
cout << "Enter number of neuron for second layer(p):" << endl;
cin >> p;
cout << "Enter error degree(e):" << endl;
cin >> e;
cout << "Enter step(a) (Enter 0 for adaptive learning step):" << endl;
cin >> a;
}

ImageModel::ImageModel(char const *path) {
    Mat image = imread(path, CV_LOAD_IMAGE_COLOR);
    init();
    iWidth = image.size().width;
    iHeight = image.size().height;
    for (int indexW = 0; indexW < iWidth; indexW +=m){
        for (int indexH = 0; indexH < iHeight; indexH +=n){
            RectangleModel bufferRectangle(indexW,indexH);
            for (int i = indexW; i < indexW + m; i++){
                for (int j = indexH; j < indexH + n; j++) {
                    if (i < iWidth && j < iHeight){
                        bufferRectangle.addElement(convertColor(image.at<Vec3b>(i,j)[0]));
                        bufferRectangle.addElement(convertColor(image.at<Vec3b>(i,j)[1]));
                        bufferRectangle.addElement(convertColor(image.at<Vec3b>(i,j)[2]));
                    } else {
                        bufferRectangle.addElement(-1);
                        bufferRectangle.addElement(-1);
                        bufferRectangle.addElement(-1);
                    }
                }
            }
            bufferRectangle.createMatrixX();
            rectangles.push_back(bufferRectangle);
        }
    }
    L = static_cast<int>(rectangles.size());
    nmRGB = n * m * RGB;
    createWeightMatrix();
}

void ImageModel::createOutputImage() {
    Mat image(iWidth, iHeight, CV_8UC3);
    float color[3];
    for (int index = 0; index < L; index++){
        int startX = rectangles[index].getStartX();
        int startY = rectangles[index].getStartY();
        Matrix X = rectangles[index].getX();
        Matrix Y = X * W;
        Matrix X_ = Y * W_;
        int pixel = 0;
        for (int i = startX; i < m + startX; i++) {
            for (int j = startY; j < n + startY; j++) {
                color[0] = convertRGBToImg(X_.getValue(0, pixel++));
                color[1] = convertRGBToImg(X_.getValue(0, pixel++));
                color[2] = convertRGBToImg(X_.getValue(0, pixel++));
                if (i < iWidth && j < iHeight){
                    image.at<Vec3b>(i, j)[0] = static_cast<uchar>(color[0]);
                    image.at<Vec3b>(i, j)[1] = static_cast<uchar>(color[1]);
                    image.at<Vec3b>(i, j)[2] = static_cast<uchar>(color[2]);
                }
            }
        }
    }
    imwrite("/Users/alexeisevko/CLionProjects/ImageCompression/output.png", image);
//    imwrite("/Users/alexeisevko/CLionProjects/ImageCompression/output.bmp", image);
}

void ImageModel::run() {
    double step;
    double step_;
    double E;
    normalizeMatrixes();
    int iteration = 0;
    do {
        E = 0;
        for (int index = 0; index < L; index++){
            Matrix X = rectangles[index].getX();
            Matrix Y = X * W;
            Matrix X_ = Y * W_;
            Matrix deltaX = X_ - X;
            if (a) {
                step_ = step = a;
            } else {
                step_ = adaptiveLearningStep(Y);
                step = adaptiveLearningStep(X);
            }
            Matrix temp = X.transpose() * step;
            W = W - (temp * deltaX * W_.transpose()); ///обучение нейронов первого слоя
            temp = Y.transpose() * step_;
            W_ = W_ - (temp * deltaX); ///корректировка весов нейронов на втором слое
            normalizeMatrixes();
        }
        for (int index = 0; index < L; index++){
            Matrix X = rectangles[index].getX();
            Matrix Y = X * W;
            Matrix X_ = Y * W_;
            Matrix deltaX = X_ - X;
            E += getErrorDegree(deltaX);
        }
        iteration++;
        cout << "Iteration: " << iteration << " Error: " << E << endl;
    } while (E > e);
    double z = (1.0 * n * m * RGB * L) / ((n * m * RGB + L) * p + 2);
    cout << "Z = " << z << endl;;
}


double ImageModel::adaptiveLearningStep(Matrix matrix) {
    Matrix temp = (matrix * matrix.transpose());
    double sum = 50;
    for (unsigned int i = 0; i < temp.getN(); i++) {
        for (unsigned int j = 0; j < temp.getM(); j++) {
            sum += temp.getValue(i,j);
        }
    }
    return  1.0 / sum;
}

void ImageModel::normalizeMatrixes() {
    normalizeMatrix(W);
    normalizeMatrix(W_);
}

void ImageModel::normalizeMatrix(Matrix matrix) {
    int cols = matrix.getM();
    int rows = matrix.getN();
    for (unsigned int i = 0; i < cols; i ++) {
        double sum = 0;
        for (unsigned int j = 0; j < rows; j++) {
            sum += (matrix.getValue(j, i) * matrix.getValue(j, i));
        }
        sum = sqrt(sum);
        for (unsigned int j = 0; j < rows; j++) {
            double newValue = matrix.getValue(j, i) / sum;
            matrix.changeValue(j, i, newValue);
        }
    }
}

double ImageModel::convertColor(int color) {
    return ((2.0 * color / 255) - 1);
}

int ImageModel::convertRGBToImg(double color) {
    double ans = (255 * (color + 1) / 2);
    if (ans < 0){
        ans = 0;
    }
    if (ans > 255){
        ans = 255;

    }
    return (int)ans;
}

double ImageModel::getErrorDegree(Matrix deltaX) {
    double e = 0;
    for (int i = 0; i < nmRGB; i++) {
        e += (deltaX.getValue(0, i) * deltaX.getValue(0, i));
    }
    return e;
}

void ImageModel::createWeightMatrix() {
    srand(time(NULL));
    W = Matrix(nmRGB, p, true);
    for (int i = 0; i < nmRGB; i++) {
        for (int j = 0; j < p; j++) {
            double newValue = (((double)rand() / RAND_MAX)*2 - 1 )*0.1;;
            W.changeValue(i, j, newValue);
        }
    }
    W_ = W.transpose();
}