#include "button.h"

//! [0]
Button::Button(const QString &text, QWidget *parent) : QToolButton(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	setText(text);
}
Button::Button(QWidget *parent) : QToolButton(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

//! [0]

//! [1]
QSize Button::sizeHint() const
//! [1] //! [2]
{
	QSize size = QToolButton::sizeHint();
	size.rheight() += 20;
	size.rwidth() = qMax(size.width(), size.height());
	return size;
}
void Button::set_Text(const QString &text)
{
	m_text = text;
}
//! [2]
