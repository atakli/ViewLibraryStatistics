#include <QApplication>

#include "viewstatistics.h"
#include "windows.h"

//#include <iostream>

//#ifdef _WIN32
//  #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")   // TODO: bu en iyisi mi bakmak lazım. bi de bu sadece msvc için heralde.
////  For linux I know how to create a .desktop file so I can launch the app that does not show a terminal when it is launched.
//#endif
// edit: buna gerek yok. o zaman pro'daki console'u bilmiyomusum demek ki. dikkat! console ozelligi acik olmasina ragmen burdan calistirinca console'u acmiyor.
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    ViewStatistics viewstatistics;
	viewstatistics.show();
    return a.exec();
}
