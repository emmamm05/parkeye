/**
 * @file CannyDetector_Demo.cpp
 * @brief Sample code showing how to detect edges using the Canny Detector
 * @author OpenCV team
 */

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include  "canny_detector.h"

using namespace cv;
using namespace std;

/// Global variables
Mat cd_src, src_gray;
Mat cd_dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
const char* cd_window_name = "Edge Map";

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
static void CannyThreshold(int, void*)
{
    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );

    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

    /// Using Canny's output as a mask, we display our result
    cd_dst = Scalar::all(0);

    cd_src.copyTo( cd_dst, detected_edges);
    imshow( cd_window_name, cd_dst );
}


/**
 * @function main
 */
int canny_demo( int, char** argv )
{
  /// Load an image
  cd_src = imread( argv[1] );

  if( !cd_src.data )
    { return -1; }

  /// Create a matrix of the same type and size as src (for dst)
  cd_dst.create( cd_src.size(), cd_src.type() );

  /// Convert the image to grayscale
  cvtColor( cd_src, src_gray, COLOR_BGR2GRAY );

  /// Create a window
  namedWindow( cd_window_name, WINDOW_AUTOSIZE );

  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", cd_window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

  /// Show the image
  CannyThreshold(0, 0);

  /// Wait until user exit program by pressing a key
  waitKey(0);

  return 0;
}

