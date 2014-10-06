#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include  "canny_detector.h"

using namespace cv;
using namespace std;

/// Global variables
Mat cd_src1, src_gray1, cd_src2, src_gray2;
Mat cd_dst1, detected_edges1, cd_dst2, detected_edges2;

int edgeThresh = 1;
int lowThreshold=80;
int const max_lowThreshold = 100;
int size_blur=0;
int const max_size_blur = 10;
int ratio_ = 3;
int kernel_size = 3;
const char* cd_window_name = "Edge Map";

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
static void CannyThreshold(int, void*)
{
    /// Reduce noise with a kernel 3x3
    blur( src_gray1, detected_edges1, Size(size_blur+1,size_blur+1) );
    blur( src_gray2, detected_edges2, Size(size_blur+1,size_blur+1) );

    /// Canny detector
    Canny( detected_edges1, detected_edges1, lowThreshold, lowThreshold*ratio_, kernel_size );
    Canny( detected_edges2, detected_edges2, lowThreshold, lowThreshold*ratio_, kernel_size );

    /// Using Canny's output as a mask, we display our result
    cd_dst1 = Scalar::all(0);
    cd_dst2 = Scalar::all(0);

    cd_src1.copyTo( cd_dst1, detected_edges1);
    cd_src2.copyTo( cd_dst2, detected_edges2);

    absdiff(cd_dst1,cd_dst2,cd_dst2);

    imshow( cd_window_name, cd_dst2 );
}


/**
 * @function main
 */
int subtration_demo( int, char** argv )
{
  /// Load an image
    cd_src1 = imread(argv[1]);
    cd_src2 = imread(argv[2]);

  if( !cd_src1.data && !cd_src2.data )
    { return -1; }

  /// Create a matrix of the same type and size as src (for dst)
  cd_dst1.create( cd_src1.size(), cd_src1.type() );
  cd_dst2.create( cd_src2.size(), cd_src2.type() );

  /// Convert the image to grayscale
  cvtColor( cd_src1, src_gray1, COLOR_BGR2GRAY );
  cvtColor( cd_src2, src_gray2, COLOR_BGR2GRAY );

  /// Create a window
  namedWindow( cd_window_name, WINDOW_AUTOSIZE );

  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", cd_window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
  createTrackbar( "Min Blur:", cd_window_name, &size_blur, max_size_blur, CannyThreshold );

  /// Show the image
  CannyThreshold(0, 0);

  /// Wait until user exit program by pressing a key
  waitKey(0);

  return 0;
}
