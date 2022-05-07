#include "viewstatistics.h"

#include <QGridLayout>
#include <QSizePolicy>
#include <QLabel>
#include <QDebug>
#include <QFile>

int hrp = 0; // horizontalReferencePoint

template<int rows, int cols>
void createLabels(QLabel* (&label)[rows][cols], int width=100, int height=100)
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
	{
		label[i][j] = new QLabel;
		label[i][j]->setAlignment(Qt::AlignCenter);
		label[i][j]->setFrameShape(QFrame::Panel);
		label[i][j]->setFrameShadow(QFrame::Sunken);
		label[i][j]->setLineWidth(3);
//		label[i][j]->setFixedSize(width, height);
	}
}

ViewStatistics::ViewStatistics(QWidget *parent) : QWidget(parent)
{
	QLabel *ageLabels[NumAgeLabels][1], *genderLabels[NumGenderLabels][1], *intentLabels[NumIntentLabels][1], *countLabels[NumCountLabelsRows][NumCountLabelsCols];
	QLabel *sumLabels[NumSumLabels][1];

	createLabels(countLabels);
	createLabels(ageLabels,200);
	createLabels(genderLabels);
	createLabels(intentLabels);
	createLabels(sumLabels);

	QGridLayout *mainLayout = new QGridLayout;
//	QHBoxLayout *horizontalLayout = new QHBoxLayout;
	mainLayout->setSpacing(0);

	mainLayout->setSizeConstraint(QLayout::SetFixedSize);

	for (int i = 0; i < NumCountLabelsRows; ++i)
		for (int j = 0; j < NumCountLabelsCols; ++j)
			mainLayout->addWidget(countLabels[i][j], i+2,j+1);
	for (int j = 0; j < NumAgeLabels; ++j)
			mainLayout->addWidget(ageLabels[j][0], 0,2*j+1,1,2);
	for (int j = 0; j < NumGenderLabels; ++j)
	{
		if(j % 2 == 0)
			genderLabels[j][0]->setText("ERKEK");
		else
			genderLabels[j][0]->setText("KADIN");
		mainLayout->addWidget(genderLabels[j][0], 1,j+1);
	}
	for (int i = 0; i < NumIntentLabels; ++i)
	{
//		intentLabels[i][0]->setSizePolicy(QSizePolicy::GrowFlag | QSizePolicy::ShrinkFlag | QSizePolicy::ExpandFlag);
//		QSizePolicy::Policy expandingPolicy(QSizePolicy::Expanding);
//		intentLabels[i][0]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//		intentLabels[i][0]->setSizePolicy(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
		mainLayout->addWidget(intentLabels[i][0], i+2,0);
	}
	for (int j = 0; j < NumSumLabels; ++j)
		mainLayout->addWidget(sumLabels[j][0], NumIntentLabels + 2, j);

	ageLabels[0][0]->setText("0-6 yaş");
	ageLabels[1][0]->setText("7-14 yaş");
	ageLabels[2][0]->setText("15-64 yaş");
	ageLabels[3][0]->setText("65 yaş ve üstü");

	intentLabels[0][0]->setText("Kitap/Dergi/Gazete Okumak");
	intentLabels[1][0]->setText("Kitap Ödünç Almak");
	intentLabels[2][0]->setText("Ders Çalışmak");
	intentLabels[3][0]->setText("İnternet kullanmak");
	intentLabels[4][0]->setText("Atölye/Etkinliklere katılmak");

	sumLabels[0][0]->setText("TOPLAMLAR");

	for(int j = 0; j < NumSumLabels; ++j)
		sumLabels[j][0]->setStyleSheet("font-weight: bold;");

//	horizontalLayout->addLayout(mainLayout);
	setLayout(mainLayout);
	setWindowTitle("İstatistik Sonuçları");

	view(countLabels, sumLabels);
}
QString ViewStatistics::openFile()
{
	QFile file("/home/b720/qt-projects/build-librarystatistics-Desktop_Qt_5_14_2_GCC_64bit-Release/istatistikler.csv");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return "";							// TODO: buraya girerse ne olcak?
	QString text = file.readAll();
	file.close();
	return text;
}
std::vector<std::vector<int>> ViewStatistics::parseFile()
{
	QStringList lines = openFile().split('\n');

//	std::vector<std::vector<int>> statistics(ROW_COUNT, std::vector<int>(COLUMN_COUNT));
	std::vector<std::vector<int>> statistics;
	std::vector<int> sonuc;

	foreach(QString line, lines)
	{
//		qDebug() << "line:" << line;
		QStringList elemanlar = line.split(',');
		foreach(auto eleman, elemanlar)
			sonuc.emplace_back(eleman.toInt());
		statistics.emplace_back(sonuc);
//		qDebug() << sonuc;
		sonuc.clear();
	}
//	qDebug() << statistics.size();
//	foreach(auto k1, statistics)
//	{
//		foreach(auto k2, k1)
//			qDebug() << k2;
//		qDebug() << "da";
//	}
	return statistics;
}
void ViewStatistics::view(QLabel *countLabels[NumCountLabelsRows][NumCountLabelsCols], QLabel *sumLabels[NumSumLabels][1])
{
	std::vector<std::vector<int>> savedStatistics = parseFile();
	for (int i = 0; i < NumCountLabelsRows; ++i)
		for (int j = 0; j < NumCountLabelsCols; ++j)
			countLabels[i][j]->setText(QString::number(savedStatistics[j][i]));
	int total = 0;
	for(int j = 0; j < NumCountLabelsCols; ++j)
	{
		for(int i = 0; i < NumCountLabelsRows; ++i)
		{
			total += countLabels[i][j]->text().toInt();
		}
		sumLabels[j+1][0]->setText(QString::number(total));
		total = 0;
	}
}
