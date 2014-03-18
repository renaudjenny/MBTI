#-------------------------------------------------
#
# Project created by QtCreator 2014-03-07T23:59:29
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MBTI
TEMPLATE = app


SOURCES += main.cpp\
        question.cpp \
    spectrum.cpp \
    typedescription.cpp \
    typedescriptions.cpp

HEADERS  += question.h \
    spectrum.h \
    typedescription.h \
    typedescriptions.h

OTHER_FILES +=

RESOURCES += \
    Resources.qrc
