#ifndef VIEWSTATISTICS_H
#define VIEWSTATISTICS_H

#include "updatecontroller.h"

#include <QWidget>

class QLabel;

class ViewStatistics : public QWidget
{
	Q_OBJECT
public:
	ViewStatistics(QWidget *parent = nullptr);
private:
	enum { NumCountLabelsRows = 5, NumCountLabelsCols = 8, NumAgeLabels = 4, NumGenderLabels = NumAgeLabels * 2, NumIntentLabels = 5, NumSumLabels = NumGenderLabels + 1};
//    UpdateController update;

	std::vector<std::vector<int>> parseFile();
    QString readFile() const;
	void view(QLabel *countLabels[NumCountLabelsRows][NumCountLabelsCols], QLabel *sumLabels[NumSumLabels][1]);
};

#endif // VIEWSTATISTICS_H
