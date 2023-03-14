QT += widgets

win32 {
    CONFIG += console
    QMAKE_CXXFLAGS_WARN_ON += /std:c++latest
}
unix {
    QMAKE_CXXFLAGS += -std=c++2a
}
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
