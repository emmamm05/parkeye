#include "ips_with_opencl.h"

struct timespec startOcl, stopOcl;

IPS_with_opencl::IPS_with_opencl()
{
}


Mat IPS_with_opencl::applyBlur(Mat src){
    Mat dst = src.clone();

    /* cv::Mat --> cv::ocl::oclMat */
    ocl::oclMat oclmat_src(src);
    ocl::oclMat oclmat_dst;

    clock_gettime( CLOCK_REALTIME, &startOcl);
    ocl::GaussianBlur( oclmat_src, oclmat_dst, Size( Constants::BLUR_KERNEL_LENGTH, Constants::BLUR_KERNEL_LENGTH ), 0, 0 );
    clock_gettime( CLOCK_REALTIME, &stopOcl);
    double elapsedStep = (double)( stopOcl.tv_sec - startOcl.tv_sec )+ ( stopOcl.tv_nsec - startOcl.tv_nsec );
    printf("Tiempo de ejecucion de GaussianBlur:\t%f\tns \n", std::abs(elapsedStep) );

    /* cv::Mat <-- cv::ocl::oclMat */
    oclmat_dst.download(dst);
    return dst;
}

Mat IPS_with_opencl::applyLaplacian(Mat src){
    Mat dst = src.clone();

    /* cv::Mat --> cv::ocl::oclMat */
    ocl::oclMat oclmat_src(src);
    ocl::oclMat oclmat_dst;

    clock_gettime( CLOCK_REALTIME, &startOcl);
    Laplacian( oclmat_src, oclmat_dst, Constants::LAPLACE_DDEPTH, Constants::LAPLACE_KERNEL_SIZE, Constants::LAPLACE_SCALE,
               Constants::LAPLACE_DELTA, BORDER_DEFAULT );
    clock_gettime( CLOCK_REALTIME, &stopOcl);
    double elapsedStep = (double)( stopOcl.tv_sec - startOcl.tv_sec )+ ( stopOcl.tv_nsec - startOcl.tv_nsec );
    printf("Tiempo de ejecucion de Laplacian:\t%f\tns \n", std::abs(elapsedStep) );

    /* cv::Mat <-- cv::ocl::oclMat */
    oclmat_dst.download(dst);

    return dst;
}

Mat IPS_with_opencl::applyEdge(Mat src){
    Mat dst = src.clone();
    Canny( src, dst, Constants::EDGES_LOW_THRESHOLD, Constants::EDGES_LOW_THRESHOLD*Constants::EDGES_RATIO, Constants::EDGES_KERNEL_SIZE );
    return dst;
}

Mat IPS_with_opencl::applySubs(Mat raw_src, Mat ref_src){
    Mat dst = raw_src.clone();
    absdiff(raw_src,ref_src,dst);
    return dst;
}

Mat IPS_with_opencl::applyContourns(Mat src){
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    RNG rng(12345);
    Mat src2 = src.clone();
    Mat dst = src.clone();
    Mat src_gray = src.clone();
    Mat final = imread(Constants::IMG_RAW);

    cvtColor( src, src_gray, CV_BGR2GRAY );
    // Eliminar ruido
    src2 = applyBlur(src_gray);
    findContours( src2, contours, hierarchy,CV_CHAIN_APPROX_SIMPLE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    // iterate through all the top-level contours,
       // draw each connected component with its own random color
//       int idx = 0;
//       for( ; idx >= 0; idx = hierarchy[idx][0] )
//       {
//           Scalar color( rand()&255, rand()&255, rand()&255 );
//           drawContours( dst, contours, idx, color, CV_FILLED, 1, hierarchy );
//       }

    qDebug() << contours.data();
    // Rotar los rectangulos buscando el area minima
    vector<RotatedRect> minRect( contours.size() );
    for( int i = 0; i < contours.size(); i++ ){
         minRect[i] = minAreaRect( Mat(contours[i]) );
     }

    //  Dibujar rectangulos
     Scalar color = Scalar( rng.uniform(0,0), rng.uniform(250,250), rng.uniform(0,0) );
     for( int i = 0; i< contours.size(); i++ ){
         Point2f rect_points[4]; minRect[i].points( rect_points );

         if( pow((int)(rect_points[0].x-(rect_points[1]).x), 2.0) + pow((int)(rect_points[0].y-(rect_points[1]).y), 2.0) > pow(Constants::CONTOURS_MIN_CONTOURS, 2.0) &&
             pow((int)(rect_points[1].x-(rect_points[2]).x), 2.0) + pow((int)(rect_points[1].y-(rect_points[2]).y), 2.0) > pow(Constants::CONTOURS_MIN_CONTOURS, 2.0))
             {
            for(int j = 0; j < 4; j++ ){
                line( dst, rect_points[j], rect_points[(j+1)%4], color, 2, 8 );
                line( final, rect_points[j], rect_points[(j+1)%4], color, 2, 8 );
            }
         }
     }
     imwrite(Constants::IMG_FINAL,final);
    return dst;
}


int IPS_with_opencl::processBlur(){
    //Raw Image
    Mat src = imread( Constants::IMG_RAW_LAPLACE );
    if (!src.data) return 1;
    Mat dst = applyBlur(src);
    imwrite( Constants::IMG_RAW_BLUR, dst );

    //Ref Image
    src = imread( Constants::IMG_REF_LAPLACE );
    if (!src.data) return 1;
    dst = applyBlur(src);
    imwrite( Constants::IMG_REF_BLUR, dst );
    return 0;
}

int IPS_with_opencl::processLaplacian(){
    //Raw Image
    Mat src = imread( Constants::IMG_RAW );
    if (!src.data) return 1;
    Mat dst = applyLaplacian(src);
    imwrite( Constants::IMG_RAW_LAPLACE, dst );

    //Ref Image
    src = imread( Constants::IMG_REF );
    if (!src.data) return 1;
    dst = applyLaplacian(src);
    imwrite( Constants::IMG_REF_LAPLACE, dst );
    return 0;
}

int IPS_with_opencl::processEdge(){
     Mat src = imread( Constants::IMG_SUBS );
     if (!src.data) return 1;
     Mat dst = applyEdge(src);
     imwrite( Constants::IMG_EDGES, dst );
    return 0;
}

int IPS_with_opencl::processSubs(){
    Mat src_raw = imread( Constants::IMG_RAW_BLUR );
    Mat src_ref = imread( Constants::IMG_REF_BLUR );
    if (!src_raw.data || !src_ref.data) return 1;
    Mat dst = applySubs(src_raw,src_ref);
    imwrite( Constants::IMG_SUBS, dst );
}

int IPS_with_opencl::processContourns(){
    Mat src = imread( Constants::IMG_EDGES );
    if (!src.data) return 1;
    Mat dst = applyContourns(src);
    imwrite( Constants::IMG_CONTOURNS, dst );
}
