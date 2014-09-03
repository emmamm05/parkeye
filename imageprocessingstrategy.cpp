#include "imageprocessingstrategy.h"
#include "constants.h"

ImageProcessingStrategy::ImageProcessingStrategy()
{
}

Mat ImageProcessingStrategy::applyBlur(Mat src){
    Mat dst = src.clone();
    GaussianBlur( src, dst, Size( Constants::BLUR_KERNEL_LENGTH, Constants::BLUR_KERNEL_LENGTH ), 0, 0 );
    return dst;
}

Mat ImageProcessingStrategy::applyLaplacian(Mat src){
    Mat dst = src.clone();
    return dst;
}

void ImageProcessingStrategy::processBlur(){
    Mat src = imread( Constants::IMG_RAW );
    Mat dst = applyBlur(src);
    imwrite( Constants::IMG_BLUR, dst );
}

void ImageProcessingStrategy::processLaplacian(){
    Mat src = imread( Constants::IMG_RAW );
    Mat dst = applyBlur(src);
    imwrite( Constants::IMG_BLUR, dst );
}
