QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += openglwidgets

CONFIG += c++11

include(../QtGifImage/src/gifimage/qtgifimage.pri)



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp\
    ../s21_parser.c\
    ../s21_affine_transform.c\

HEADERS += \
    glwidget.h \
    mainwindow.h\
    ../s21_parser.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    ../QtGifImage/qtgifimage.pro
