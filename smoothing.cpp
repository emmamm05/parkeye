#include <QCoreApplication>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

/// Global Variables
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;

Mat sm_src; Mat sm_dst;
char sm_window_name[] = "Filter Demo 1";

/// Function headers
int display_caption( char* caption );
int display_dst( int delay );

/**
 * function main
 */
 int smoothing_demo( int argc, char** argv )
 {
   namedWindow( sm_window_name, CV_WINDOW_AUTOSIZE );

   /// Load the source image
   sm_src = imread( argv[1], 1 );

   if( display_caption( "Original Image" ) != 0 ) { return 0; }

   sm_dst = sm_src.clone();
   if( display_dst( DELAY_CAPTION ) != 0 ) { return 0; }

   /// Applying Homogeneous blur
   if( display_caption( "Homogeneous Blur" ) != 0 ) { return 0; }

   for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
       { blur( sm_src, sm_dst, Size( i, i ), Point(-1,-1) );
         if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }

    /// Applying Gaussian blur
    if( display_caption( "Gaussian Blur" ) != 0 ) { return 0; }

    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
        { GaussianBlur( sm_src, sm_dst, Size( i, i ), 0, 0 );
          if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }

     /// Applying Median blur
     if( display_caption( "Median Blur" ) != 0 ) { return 0; }

     for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
         { medianBlur ( sm_src, sm_dst, i );
           if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }

     /// Applying Bilateral Filter
     if( display_caption( "Bilateral Blur" ) != 0 ) { return 0; }

     for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
         { bilateralFilter ( sm_src, sm_dst, i, i*2, i/2 );
           if( display_dst( DELAY_BLUR ) != 0 ) { return 0; } }

     /// Wait until user press a key
     display_caption( "End: Press a key!" );

     waitKey(0);
     return 0;
 }

 int display_caption( char* caption )
 {
   sm_dst = Mat::zeros( sm_src.size(), sm_src.type() );
   putText( sm_dst, caption,
            Point( sm_src.cols/4, sm_src.rows/2),
            CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255) );

   imshow( sm_window_name, sm_dst );
   int c = waitKey( DELAY_CAPTION );
   if( c >= 0 ) { return -1; }
   return 0;
  }

  int display_dst( int delay )
  {
    imshow( sm_window_name, sm_dst );
    int c = waitKey ( delay );
    if( c >= 0 ) { return -1; }
    return 0;
  }
