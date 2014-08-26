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

int edgeThresh1 = 1;
int lowThreshold1;
int const max_lowThreshold1 = 100;
int ratio1 = 3;
int kernel_size1 = 3;
const char* cd_window_name1 = "Edge Map";

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
static void CannyThreshold(int, void*)
{
    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );

    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold1, lowThreshold1*ratio1, kernel_size1 );

    /// Using Canny's output as a mask, we display our result
    cd_dst = Scalar::all(0);

    cd_src.copyTo( cd_dst, detected_edges);
    imshow( cd_window_name1, cd_dst );
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
  namedWindow( cd_window_name1, WINDOW_AUTOSIZE );

  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", cd_window_name1, &lowThreshold1, max_lowThreshold1, CannyThreshold );

  /// Show the image
  CannyThreshold(0, 0);

  /// Wait until user exit program by pressing a key
  waitKey(0);

  return 0;
}

