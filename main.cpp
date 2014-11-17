#include "constants.h"
#include "ips_simple.h"
#include "ips_with_opencl.h"
#include <unistd.h>
#include <stdio.h>

//IPS_simple* strategy = new IPS_simple();
IPS_with_opencl* strategy = new IPS_with_opencl();

struct timespec start, stop;

void step(){

    switch(Constants::STEP_STATE){
        case Constants::RAW:
            //next state
            Constants::STEP_STATE = Constants::LAPLACE;
            break;
        case Constants::BLUR:
            strategy->processBlur();
            //next state
            Constants::STEP_STATE = Constants::SUBS;
            break;
        case Constants::LAPLACE:
            strategy->processLaplacian();
            //next state
            Constants::STEP_STATE = Constants::BLUR;
            break;
        case Constants::EDGES:
            //strategy->processEdge();
            //next state
            Constants::STEP_STATE = Constants::CONTOURNS;
            break;
        case Constants::SUBS:
            strategy->processSubs();
            //next state
            Constants::STEP_STATE = Constants::EDGES;
            break;
        case Constants::CONTOURNS:
            //strategy->processContourns();
            break;
    }
}

//pasar como argumento el path completo de la imagen lana.jpg
int main( int argc, char** argv )
{
    printf("Begin creating ocl context...\n");

    // Platform Info
    cv::ocl::PlatformsInfo plat_info;
    cv::ocl::getOpenCLPlatforms( plat_info );

    // initialise of ocl
    ocl::DevicesInfo param;
    ocl::getOpenCLDevices(param);

    ocl::setDevice(param[0]);
    printf("End creating ocl context...\n");
    remove(Constants::IMG_RAW_BLUR);
    remove(Constants::IMG_RAW_LAPLACE);
    remove(Constants::IMG_REF_BLUR);
    remove(Constants::IMG_REF_LAPLACE);
    remove(Constants::IMG_SUBS);
    remove(Constants::IMG_EDGES);
    remove(Constants::IMG_CONTOURNS);
    remove(Constants::IMG_FINAL);

    /*	*/
    printf("inicio de la ejecucion\n");
    clock_t startProgram = clock();


    for ( int j=0; j<6; j++){
        step();
    }

    clock_t stopProgram = clock();
    double elapsedProgram = (double)difftime(startProgram, stopProgram) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion TOTAL:\t\t%f\tms \n", std::abs(elapsedProgram) );
    printf("fin  de la ejecucion\n");

}
