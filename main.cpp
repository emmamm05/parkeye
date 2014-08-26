#include "samples/canny_detector.h"
#include "samples/background_subtraction.h"
#include "samples/smoothing.h"
#include "samples/laplace.h"


//pasar como argumento el path completo de la imagen lana.jpg
int main( int argc, char** argv )
{
   //demo de varios algoritmos de blur para reducir ruido
   //smoothing_demo(argc,argv);

   //demo del algoritmo de canny detection para encontrar bordes
   //canny_demo(argc,argv);

   //laplace_demo(argc,argv);

   subtration_demo(argc,argv);
}
