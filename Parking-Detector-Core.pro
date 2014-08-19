#-------------------------------------------------
#
# Project created by QtCreator 2014-08-18T21:21:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Parking-Detector-Core
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.cpp \
    canny_detector.cpp \
    smoothing.cpp


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
    canny_detector.h \
    smoothing.h

