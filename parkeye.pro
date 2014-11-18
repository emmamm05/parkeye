#-------------------------------------------------
#
# Project created by QtCreator 2014-08-18T21:21:41
#
#-------------------------------------------------

QT       += core

TARGET = parkeye
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
QMAKE_MAC_SDK = macosx10.9

SOURCES += \
    main.cpp \
    samples/canny_detector.cpp \
    samples/smoothing.cpp \
    samples/laplace.cpp \
    samples/background_subtraction.cpp \
    constants.cpp \
    samples/contours.cpp \
    ips_with_opencl.cpp \
    ips_simple.cpp \
    ips_with_cuda.cpp

INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /usr/local/include/opencv2

LIBS += -L/usr/local/lib \
	-lX11 \
        -lopencv_core \
        -lopencv_highgui \
        -lopencv_imgproc \
       	-lopencv_ocl \
	-lopencv_gpu \
        -lopencv_nonfree \
	-lopencv_features2d

HEADERS += \
    samples/canny_detector.h \
    samples/smoothing.h \
    samples/laplace.h \
    samples/background_subtraction.h \
    imageprocessingstrategy.h \
    constants.h \
    samples/contours.h \
    ips_with_opencl.h \
    ips_simple.h \
    ips_with_cuda.h

FORMS += \
    mainwindow.ui
