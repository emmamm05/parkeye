#include "samples/canny_detector.h"
#include "samples/background_subtraction.h"
#include "samples/smoothing.h"
#include "samples/laplace.h"
#include "constants.h"
#include "imageprocessingstrategy.h"

ImageProcessingStrategy* strategy = new ImageProcessingStrategy();

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
            strategy->processEdge();
            //next state
            Constants::STEP_STATE = Constants::CONTOURNS;
            break;
        case Constants::SUBS:
            strategy->processSubs();
            //next state
            Constants::STEP_STATE = Constants::EDGES;
            break;
        case Constants::CONTOURNS:
            strategy->processContourns();
            break;
    }
}

//pasar como argumento el path completo de la imagen lana.jpg
int main( int argc, char** argv )
{

    int i;
    for ( i=0; i<6; i++){
        step();
    }
}
