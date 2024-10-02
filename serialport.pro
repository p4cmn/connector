QT += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/FCSOperations.cpp \
    source/frame.cpp \
    source/logger.cpp \
    source/main.cpp \
    source/mainwindow.cpp \
    source/serialportcontroller.cpp \
    source/serialportmodel.cpp

HEADERS += \
    source/FCSOperations.h \
    source/bytestuffing.h \
    source/formatEscape.h \
    source/fragmentation.h \
    source/frame.h \
    source/logger.h \
    source/mainwindow.h \
    source/serialportcontroller.h \
    source/serialportmodel.h \
    source/serialportscanner.h \
    source/serialporttester.h \
    source/textwidgetoutput.h

FORMS += \
    other\mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
  other\resources.qrc

DISTFILES += \
  other\applicationIcon.rc

RC_FILE += other\applicationIcon.rc
