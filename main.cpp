#include <QApplication>

#include "viewstatistics.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ViewStatistics viewstatistics;
	viewstatistics.show();

	return a.exec();
}
