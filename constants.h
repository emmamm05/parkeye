#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class Constants
{
public:
    static char* IMG_RAW;
    static const char* IMG_BLUR;
    static const char* IMG_LAPLACE;
    static const char* IMG_EDGES;
    static const char* IMG_SUBS;
    static const int BLUR_DELAY = 100;
    static const int BLUR_KERNEL_LENGTH = 5;
    static const int LAPLACE_KERNEL_SIZE = 3;
    static const int LAPLACE_SCALE = 1;
    static const int LAPLACE_DELTA = 0;
    static const int LAPLACE_DDEPTH = CV_16S;
    static const int EDGES_LOW_THRESHOLD = 40;
    static const int EDGES_RATIO = 3;
    static const int EDGES_KERNEL_SIZE = 3;
    enum STATES{
        RAW, BLUR, LAPLACE,EDGES,SUBS
    };
    static  STATES STEP_STATE;
};

#endif // CONSTANTS_H
