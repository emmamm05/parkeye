//#include "contours.h"


//#include <iostream>
//#include <math.h>

//vector<vector<Point> > contours;
//vector<Vec4i> hierarchy;
//RNG rng(12345);

//int MIN_CONTOURS = 30;


//int contours_demo(int argc, char **argv)
//{

//    /***
//     * cd_dst2: imagen en la ultima etapa
//     * cd_src1: imagen original
//     */

//   // produces out2, a one-channel image (CV_8UC1)
//   cvtColor( cd_dst2,src_gray, CV_BGR2GRAY );

//   // Eliminar ruido
//   blur( src_gray, src_gray, Size(5,5) );

//   // Encontrar contornos
//   findContours( src_gray, contours, hierarchy,CV_CHAIN_APPROX_SIMPLE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

//   // Rotar los rectangulos buscando el area minima
//   vector<RotatedRect> minRect( contours.size() );
//   for( int i = 0; i < contours.size(); i++ ){
//        minRect[i] = minAreaRect( Mat(contours[i]) );
//    }

//    // Dibujar rectangulos
//    Scalar color = Scalar( rng.uniform(0,0), rng.uniform(250,250), rng.uniform(0,0) );
//    for( int i = 0; i< contours.size(); i++ ){
//        Point2f rect_points[4]; minRect[i].points( rect_points );
//        for(int j = 0; j < 4; j++ ){
//          if( pow(rect_points[j].x-(rect_points[(j+1)%4]).x, 2) > pow(MIN_CONTOURS, 2) &&
//              pow(rect_points[j].y-(rect_points[(j+1)%4]).y, 2) > pow(MIN_CONTOURS, 2) ){
//               line( cd_src1, rect_points[j], rect_points[(j+1)%4], color, 2, 8 );
//          }
//        }
//    }

//    // Mostrar imagen
//    imshow( cd_window_name, cd_src1 );
//}

