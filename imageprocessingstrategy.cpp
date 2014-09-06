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

Mat ImageProcessingStrategy::applySubs(Mat raw_src, Mat ref_src){
    Mat dst = raw_src.clone();
    absdiff(raw_src,ref_src,dst);
    return dst;
}

Mat ImageProcessingStrategy::applyContourns(Mat src){
    Mat dst = src.clone();

}

int ImageProcessingStrategy::processBlur(){
    //Raw Image
    Mat src = imread( Constants::IMG_RAW );
    if (!src.data) return 1;
    Mat dst = applyBlur(src);
    imwrite( Constants::IMG_RAW_BLUR, dst );

    //Ref Image
    src = imread( Constants::IMG_REF );
    if (!src.data) return 1;
    dst = applyBlur(src);
    imwrite( Constants::IMG_REF_BLUR, dst );
    return 0;
}

int ImageProcessingStrategy::processLaplacian(){
    //Raw Image
    Mat src = imread( Constants::IMG_RAW_BLUR );
    if (!src.data) return 1;
    Mat dst = applyLaplacian(src);
    imwrite( Constants::IMG_RAW_LAPLACE, dst );

    //Ref Image
    src = imread( Constants::IMG_REF_BLUR );
    if (!src.data) return 1;
    dst = applyLaplacian(src);
    imwrite( Constants::IMG_REF_LAPLACE, dst );
    return 0;
}

int ImageProcessingStrategy::processEdge(){
    //Raw Image
     Mat src = imread( Constants::IMG_RAW_LAPLACE );
     if (!src.data) return 1;
     Mat dst = applyEdge(src);
     imwrite( Constants::IMG_RAW_EDGES, dst );

     //Ref Image
     src = imread( Constants::IMG_REF_LAPLACE );
     if (!src.data) return 1;
     dst = applyEdge(src);
     imwrite( Constants::IMG_REF_EDGES, dst );
    return 0;
}

int ImageProcessingStrategy::processSubs(){
    Mat src_raw = imread( Constants::IMG_RAW_EDGES );
    Mat src_ref = imread( Constants::IMG_REF_EDGES );
    if (!src_raw.data || !src_ref.data) return 1;
    Mat dst = applySubs(src_raw,src_ref);
    imwrite( Constants::IMG_SUBS, dst );
}

int ImageProcessingStrategy::processContourns(){

}
