#ifndef IMAGEPROCESSINGSTRATEGY_H
#define IMAGEPROCESSINGSTRATEGY_H

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class ImageProcessingStrategy
{
public:
    ImageProcessingStrategy();
    Mat applyBlur(Mat src);
    Mat applyLaplacian(Mat src);
    Mat applyEdge(Mat src);
    Mat applySubs(Mat src, Mat ref);
    void processBlur();
    void processLaplacian();
    void processEdge();
    void processSubs();
};

#endif // IMAGEPROCESSINGSTRATEGY_H