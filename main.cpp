#include "constants.h"
#include "ips_simple.h"
#include "ips_with_opencl.h"

IPS_simple* strategy = new IPS_simple();
//IPS_with_opencl* strategy = new IPS_with_opencl();

void step(){

    string nameStep;
    clock_t startStep = clock();

    switch(Constants::STEP_STATE){
        case Constants::RAW:
            nameStep = "RAW      ";
            //next state
            Constants::STEP_STATE = Constants::LAPLACE;
            break;
        case Constants::BLUR:
            nameStep = "BLUR     ";
            strategy->processBlur();
            //next state
            Constants::STEP_STATE = Constants::SUBS;
            break;
        case Constants::LAPLACE:
            nameStep = "LAPLACE  ";
            strategy->processLaplacian();
            //next state
            Constants::STEP_STATE = Constants::BLUR;
            break;
        case Constants::EDGES:
            nameStep = "EDGES    ";
            strategy->processEdge();
            //next state
            Constants::STEP_STATE = Constants::CONTOURNS;
            break;
        case Constants::SUBS:
            nameStep = "SUBS     ";
            strategy->processSubs();
            //next state
            Constants::STEP_STATE = Constants::EDGES;
            break;
        case Constants::CONTOURNS:
            nameStep = "CONTOURNS";
            strategy->processContourns();
            break;
    }
    clock_t stopStep = clock();
    double elapsedStep = (double)difftime(startStep, stopStep) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion de %s: %f\tms \n", nameStep.c_str(), std::abs(elapsedStep) );
}

//pasar como argumento el path completo de la imagen lana.jpg
int main( int argc, char** argv )
{
    //cleaning
    std::remove(Constants::IMG_RAW_BLUR);
    std::remove(Constants::IMG_RAW_LAPLACE);
    std::remove(Constants::IMG_REF_BLUR);
    std::remove(Constants::IMG_REF_LAPLACE);
    std::remove(Constants::IMG_SUBS);
    std::remove(Constants::IMG_EDGES);
    std::remove(Constants::IMG_CONTOURNS);
    std::remove(Constants::IMG_FINAL);


    printf("Begin creating ocl context...\n");

    /* Platform Info */
    cv::ocl::PlatformsInfo plat_info;
    cv::ocl::getOpenCLPlatforms( plat_info );

    /* initialise of ocl */
    ocl::DevicesInfo param;
    ocl::getOpenCLDevices(param);

    ocl::setDevice(param[0]);
    printf("End creating ocl context...\n");

    printf("inicio de la ejecucion\n");
    clock_t start = clock();
    int i;
    for ( i=0; i<6; i++){
        step();
    }
    clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion total       : %f\tms \n", elapsed);
    printf("fin  de la ejecucion\n");
}
