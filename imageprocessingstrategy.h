#ifndef IMAGEPROCESSINGSTRATEGY_H
#define IMAGEPROCESSINGSTRATEGY_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "constants.h"
#include "qdebug.h"

using namespace std;
using namespace cv;

class ImageProcessingStrategy
{
public:
    ImageProcessingStrategy();
    Mat applyBlur(Mat src);
    Mat applyLaplacian(Mat src);
    Mat applyEdge(Mat src);
    Mat applySubs(Mat raw_src, Mat ref_src);
    Mat applyContourns(Mat src);
    int processBlur();
    int processLaplacian();
    int processEdge();
    int processSubs();
    int processContourns();
};

#endif // IMAGEPROCESSINGSTRATEGY_H
