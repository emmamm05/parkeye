#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class Constants
{
public:
    static const char* IMG_RAW;
    static const char* IMG_REF;
    static const char* IMG_RAW_BLUR;
    static const char* IMG_RAW_LAPLACE;
    static const char* IMG_RAW_EDGES;
    static const char* IMG_REF_BLUR;
    static const char* IMG_REF_LAPLACE;
    static const char* IMG_REF_EDGES;
    static const char* IMG_SUBS;
    static const char* IMG_CONTOURNS;
    static const int BLUR_KERNEL_LENGTH = 5;
    static const int LAPLACE_KERNEL_SIZE = 3;
    static const int LAPLACE_SCALE = 1;
    static const int LAPLACE_DELTA = 0;
    static const int LAPLACE_DDEPTH = CV_16S;
    static const int EDGES_LOW_THRESHOLD = 70;
    static const int EDGES_RATIO = 3;
    static const int EDGES_KERNEL_SIZE = 3;
    enum STATES{
        PRE, RAW, BLUR, LAPLACE,EDGES,SUBS,CONTOURNS
    };
    static  STATES STEP_STATE;
};

#endif // CONSTANTS_H
