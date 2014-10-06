#ifndef IPS_SIMPLE_H
#define IPS_SIMPLE_H
#include "imageprocessingstrategy.h"

class IPS_simple
{
public:
    IPS_simple();
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

#endif // IPS_SIMPLE_H
