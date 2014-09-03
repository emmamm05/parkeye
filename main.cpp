#include "samples/canny_detector.h"
#include "samples/background_subtraction.h"
#include "samples/smoothing.h"
#include "samples/laplace.h"
#include <Qt/qapplication.h>
#include "mainwindow.h"

//pasar como argumento el path completo de la imagen lana.jpg
int main( int argc, char** argv )
{
    QApplication a(argc, argv);
    MainWindow m;
    m.show();
    return a.exec();
}
