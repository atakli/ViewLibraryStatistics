QT += widgets

CONFIG += console

QMAKE_CXXFLAGS_WARN_ON += /std:c++latest

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#        button.cpp \
        main.cpp \
        viewstatistics.cpp

HEADERS += \
    viewstatistics.h

FORMS += \
    viewform.ui

win32{
INCLUDEPATH += "C:\\Users\\Emre ATAKLI\\Documents\\qt\\UpdateController\\include"
CONFIG(release, debug|release): LIBS += -L"C:\\Users\\Emre ATAKLI\\Documents\\qt\\UpdateController\\build-UpdateController-Desktop_Qt_6_4_1_MSVC2019_64bit-Release\\release\\static" -lupdatecontroller
else:CONFIG(debug, debug|release): LIBS += -L"C:\\Users\\Emre ATAKLI\\Documents\\qt\\UpdateController\\build-UpdateController-Desktop_Qt_6_4_1_MSVC2019_64bit-Debug\\debug\\static" -lupdatecontroller
}
unix{
INCLUDEPATH += /home/b720/qt-projects/UpdateController/include
CONFIG(debug, debug|release): LIBS += -L/home/b720/qt-projects/UpdateController/build-UpdateController-Desktop_Qt_5_14_2_GCC_64bit-Debug/debug/static -lUpdateController
else:CONFIG(release, debug|release): LIBS += -L/home/b720/qt-projects/UpdateController/build-UpdateController-Desktop_Qt_5_14_2_GCC_64bit-Release/release/static -lUpdateController
}
