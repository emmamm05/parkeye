#include "imageprocessingstrategy.h"
#include "constants.h"
#include "QDebug"

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
    Laplacian( src, dst, Constants::LAPLACE_DDEPTH, Constants::LAPLACE_KERNEL_SIZE, Constants::LAPLACE_SCALE,
               Constants::LAPLACE_DELTA, BORDER_DEFAULT );
    return dst;
}

Mat ImageProcessingStrategy::applyEdge(Mat src){
    Mat dst = src.clone();
   Canny( src, dst, Constants::EDGES_LOW_THRESHOLD, Constants::EDGES_LOW_THRESHOLD*Constants::EDGES_RATIO, Constants::EDGES_KERNEL_SIZE );
    return dst;
}

int ImageProcessingStrategy::processBlur(){
    Mat src = imread( Constants::IMG_RAW );
    if (!src.data) return -1;
    qDebug() << "###PROCESSSING###";
    qDebug() << src.data;
    Mat dst = applyBlur(src);
    imwrite( Constants::IMG_BLUR, dst );
    return 0;
}

int ImageProcessingStrategy::processLaplacian(){
    Mat src = imread( Constants::IMG_BLUR );
    if (!src.data) return -1;
    Mat dst = applyLaplacian(src);
    imwrite( Constants::IMG_LAPLACE, dst );
    return 0;
}

int ImageProcessingStrategy::processEdge(){
    Mat src = imread( Constants::IMG_LAPLACE );
    if (!src.data) return -1;
    Mat dst = applyEdge(src);
    imwrite( Constants::IMG_EDGES, dst );
    return 0;
}
