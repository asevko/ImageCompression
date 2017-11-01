#include "imageModel.h"
char const *srcImg;
int main(int argc, char** argv) {
//    if (argc != 2) {
//        printf("Not correct argument\n");
//        exit(1);
//    }
    //srcImg = strdup(argv[1]);
    // srcImg ="/Users/alexeisevko/CLionProjects/ImageCompression/256px-Lenna.png";
   srcImg ="/Users/alexeisevko/CLionProjects/ImageCompression/1024.png";
    //srcImg ="/Users/alexeisevko/CLionProjects/ImageCompression/test3.bmp";
    ImageModel model(srcImg);
    model.run();
    model.createOutputImage();
    return 0;
}