#include "matrix.h"
#include "imageModel.h"

char const *srcImg;
int main(int argc, char** argv) {
//    if (argc != 2) {
//        printf("Not correct argument\n");
//        exit(1);
//    }
    //srcImg = strdup(argv[1]);
    srcImg ="/Users/alexeisevko/CLionProjects/ImageCompression/256px-Lenna.png";
    //srcImg ="/Users/alexeisevko/CLionProjects/ImageCompression/test1.png";
//    srcImg ="/Users/alexeisevko/CLionProjects/ImageCompression/test3.bmp";
    ImageModel model(srcImg);
    model.run();
    model.createOutputImage();
//       Mat image =  imread(srcImg, CV_LOAD_IMAGE_COLOR);
//    if(! image.data )                              // Check for invalid input
//    {
//        cout <<  "Could not open or find the image" << std::endl ;
//        return -1;
//    }
//
//    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
//    imshow( "Display window", image );                   // Show our image inside it.
//
//    waitKey(0);
    return 0;
}