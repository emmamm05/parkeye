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
    static const int BLUR_KERNEL_LENGTH = 15;
    static const int LAPLACE_KERNEL_SIZE = 3;
    static const int LAPLACE_SCALE = 1;
    static const int LAPLACE_DELTA = 0;
    static const int LAPLACE_DDEPTH = CV_16S;
    enum STATES{
        RAW, BLUR, LAPLACE,EDGES,SUBS
    };
    static const int STEP_STATE = RAW;
};

#endif // CONSTANTS_H
