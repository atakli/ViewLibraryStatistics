#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>

class Button : public QToolButton
{
	Q_OBJECT
private:
	QString m_text;
public:
	explicit Button(const QString &text, QWidget *parent = nullptr);
	explicit Button(QWidget *parent = nullptr);
	void set_Text(const QString &text);

	QSize sizeHint() const override;
};

#endif
