#include "samples/canny_detector.h"
#include "samples/background_subtraction.h"
#include "samples/smoothing.h"
#include "samples/laplace.h"
#include "constants.h"
#include "imageprocessingstrategy.h"
#include <stdio.h>
#include <time.h>
#include <cmath>

ImageProcessingStrategy* strategy = new ImageProcessingStrategy();

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
