#ifndef IPS_WITH_OPENCL_H
#define IPS_WITH_OPENCL_H
#include "imageprocessingstrategy.h"

class IPS_with_opencl
{
public:
    IPS_with_opencl();
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

#endif // IPS_WITH_OPENCL_H
