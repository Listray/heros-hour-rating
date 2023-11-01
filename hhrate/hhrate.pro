QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    hhrate.cpp \
    matchresultadder.cpp \
    matchupstatistics.cpp \
    showstatistics.cpp \
    upcomingmatch.cpp \
    utils.cpp

HEADERS += \
    hhrate.h \
    matchresultadder.h \
    matchupstatistics.h \
    showstatistics.h \
    upcomingmatch.h \
    utils.h

FORMS += \
    hhrate.ui \
    matchresultadder.ui \
    matchupstatistics.ui \
    showstatistics.ui \
    upcomingmatch.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
