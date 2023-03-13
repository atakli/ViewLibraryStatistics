#include "viewstatistics.h"

#include <QMessageBox>
#include <QGridLayout>
#include <algorithm>
//#include <QSizePolicy>
#include <QLabel>
#include <QFile>
#include <QDir>

#include <iostream>

const QString statisticsFile = QDir::homePath() + QDir::separator() + ".kutuphaneIstatistikleri.csv";
const QString appName = "İstatistik Görüntüleme Programı";

//template<typename T = int, int cols>
//void createLabels(QLabel* (*label)[cols], T rows)//, int width=100, int height=100)
template<int rows, int cols>
void createLabels(QLabel* (&label)[rows][cols])//, int width=100, int height=100)
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
    createLabels(ageLabels);//,200);
    createLabels(genderLabels);
    createLabels(intentLabels);
//	createLabels(sumLabels, );
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

//    update.setParameters("https://api.github.com/repos/atakli/ViewLibraryStatistics/releases/latest", appName, "istatistikGoruntule.exe");
//    update.isNewVersionAvailable();
}
QString ViewStatistics::readFile() const
{
    QFile file(statisticsFile);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox msgBox(QMessageBox::Question, appName, statisticsFile + " dosyasi bulunamadı!", QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok, "Tamam");
        msgBox.exec();
        exit(EXIT_FAILURE);
    }
    return file.readAll();
}
std::vector<std::vector<int>> ViewStatistics::parseFile()
{
    const QStringList lines = readFile().split('\n');

//	std::vector<std::vector<int>> statistics(ROW_COUNT, std::vector<int>(COLUMN_COUNT));
	std::vector<std::vector<int>> statistics;
    statistics.reserve(NumCountLabelsCols);
    std::vector<int> sonuc;
    sonuc.reserve(NumCountLabelsRows);

    for (const QString& line : lines)
    {
        QStringList elemanlar = line.split(',');
        std::for_each(elemanlar.cbegin(), elemanlar.cend(), [&sonuc](const auto& eleman){sonuc.emplace_back(eleman.toInt());});
        statistics.emplace_back(sonuc);
        sonuc.clear();
    }
	return statistics;
}
void ViewStatistics::view(QLabel *countLabels[NumCountLabelsRows][NumCountLabelsCols], QLabel *sumLabels[NumSumLabels][1])
{
	std::vector<std::vector<int>> savedStatistics = parseFile();
	for (int i = 0; i < NumCountLabelsRows; ++i)
		for (int j = 0; j < NumCountLabelsCols; ++j)
			countLabels[i][j]->setText(QString::number(savedStatistics[j][i]));
	for(int j = 0; j < NumCountLabelsCols; ++j)
	{
        int total = 0;
		for(int i = 0; i < NumCountLabelsRows; ++i)
			total += countLabels[i][j]->text().toInt();
		sumLabels[j+1][0]->setText(QString::number(total));
	}
}
