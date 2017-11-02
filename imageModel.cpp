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
    cv::Mat image = imread(path, CV_LOAD_IMAGE_COLOR);
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
    cv::Mat image(iWidth, iHeight, CV_8UC3);
    float color[3];
    for (int index = 0; index < L; index++){
        int startX = rectangles[index].getStartX();
        int startY = rectangles[index].getStartY();
        mat X = rectangles[index].getX();
        mat Y = X * W;
        mat X_ = Y * W_;
        int pixel = 0;
        for (int i = startX; i < m + startX; i++) {
            for (int j = startY; j < n + startY; j++) {
                color[0] = convertRGBToImg(X_(0, pixel++));
                color[1] = convertRGBToImg(X_(0, pixel++));
                color[2] = convertRGBToImg(X_(0, pixel++));
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

void ImageModel::compressedImage() {
    int width, height, count;
    width = height = (int)sqrt(p/3);
    count = iHeight / n;
    cv::Mat image(height * count, width * count, CV_8UC3);
    float color[3];
    mat X;
    mat Y;
    int startX = 0;
    int startY = 0;
    for (auto rectangle : rectangles) {
        X = rectangle.getX();
        Y = X * W;
        int pixel = 0;
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                color[0] = convertRGBToImg(Y(0, pixel++));
                color[1] = convertRGBToImg(Y(0, pixel++));
                color[2] = convertRGBToImg(Y(0, pixel++));
                int x = startX + i;
                int y = startY + j;
                if (x < image.size().height && y < image.size().height) {
                    image.at<Vec3b>(y, x)[0] = static_cast<uchar>(color[0]);
                    image.at<Vec3b>(y, x)[1] = static_cast<uchar>(color[1]);
                    image.at<Vec3b>(y, x)[2] = static_cast<uchar>(color[2]);
                }
            }
        }
        startX +=width;
        if (startX >= width*count) {
            startX = 0;
            startY+=3;
        }
    }
    imwrite("/Users/alexeisevko/CLionProjects/ImageCompression/compressed.png", image);
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
            mat X = rectangles[index].getX();
            mat Y = X * W;
            mat X_ = Y * W_;
            mat deltaX = X_ - X;
            if (a) {
                step_ = step = a;
            } else {
                step_ = adaptiveLearningStep(Y);
                step = adaptiveLearningStep(X);
            }
            W = W - (step * X.t() * deltaX * W_.t()); ///обучение нейронов первого слоя
            W_ = W_ - (step_ * Y.t()  * deltaX); ///корректировка весов нейронов на втором слое
            normalizeMatrixes();
        }
        for (int index = 0; index < L; index++){
            mat X = rectangles[index].getX();
            mat Y = X * W;
            mat X_ = Y * W_;
            mat deltaX = X_ - X;
            E += getErrorDegree(deltaX);
        }
        iteration++;
        cout << "Iteration: " << iteration << " Error: " << E << endl;
    } while (E > e);
    double z = (1.0 * n * m * RGB * L) / ((n * m * RGB + L) * p + 2);
    cout << "Z = " << z << endl;;
}


double ImageModel::adaptiveLearningStep(mat matrix) {
    mat temp = (matrix * matrix.t());
    double sum = 50;
    for (unsigned int i = 0; i < temp.n_rows; i++) {
        for (unsigned int j = 0; j < temp.n_cols; j++) {
            sum += temp(i,j);
        }
    }
    return  1.0 / sum;
}

void ImageModel::normalizeMatrixes() {
    normalizeMatrix(W);
    normalizeMatrix(W_);
}

void ImageModel::normalizeMatrix(mat matrix) {
    for (unsigned int i = 0; i < matrix.n_cols; i ++) {
        double sum = 0;
        for (unsigned int j = 0; j < matrix.n_rows; j++) {
            sum += (matrix(j, i) * matrix(j, i));
        }
        sum = sqrt(sum);
        for (unsigned int j = 0; j < matrix.n_rows; j++) {
            matrix(j, i) = matrix(j, i) / sum;
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

double ImageModel::getErrorDegree(mat deltaX) {
    double e = 0;
    for (int i = 0; i < nmRGB; i++) {
        e += (deltaX(0, i) * deltaX(0, i));
    }
    return e;
}

void ImageModel::createWeightMatrix() {
    srand(time(NULL));
    W = randu<mat>(nmRGB,p);
    for (int i = 0; i < nmRGB; i++) {
        for (int j = 0; j < p; j++) {
            W(i,j) = (((double)rand() / RAND_MAX)*2 - 1 )*0.1;;
        }
    }
    W_ = W.t();
}