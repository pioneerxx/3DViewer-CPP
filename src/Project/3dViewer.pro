QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cc \
    View/MainWindow/mainwindow.cc \
    View/GLWidget/glwidget.cc \
    Model/Affine/Affine.cc \
    Model/Parser/Parser.cc \
    Model/Figure/Figure.cc \
    Model/Facade/Facade.cc \
    Model/Memento/Memento.cc \
    Controller/Controller/Controller.cc \
    Model/SingletonModel/SingletonModel.cc \
    View/SingletonView/SingletonView.cc \
    Controller/SingletonController/SingletonController.cc


HEADERS += \
    View/MainWindow/mainwindow.h \
    View/GLWidget/glwidget.h \
    Model/Affine/Affine.h \
    Model/Parser/Parser.h \
    Model/Figure/Figure.h \
    Model/Facade/Facade.h \
    Model/Memento/Memento.h \
    Controller/Controller/Controller.h \
    Model/SingletonModel/SingletonModel.h \
    Controller/SingletonController/SingletonController.h \
    View/SingletonView/SingletonView.h

FORMS += \
    View/MainWindow/mainwindow.ui \

INCLUDEPATH += \
    $$PWD/View/GLWidget



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(Libs/QtGifImage/src/gifimage/qtgifimage.pri)
