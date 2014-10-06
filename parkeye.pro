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


SOURCES += \
    main.cpp \
    samples/canny_detector.cpp \
    samples/smoothing.cpp \
    samples/laplace.cpp \
    samples/background_subtraction.cpp \
    imageprocessingstrategy.cpp \
    constants.cpp \
    samples/contours.cpp


## OpenCV settings for Unix/Linux
unix:!mac {
    message("* Using settings for Unix/Linux.")
    INCLUDEPATH += /usr/local/include/opencv

    LIBS += -L/usr/local/lib/ \
        -lopencv_core \
        -lopencv_highgui \
        -lopencv_imgproc
}

HEADERS += \
    samples/canny_detector.h \
    samples/smoothing.h \
    samples/laplace.h \
    samples/background_subtraction.h \
    imageprocessingstrategy.h \
    constants.h \
    samples/contours.h

FORMS += \
    mainwindow.ui

