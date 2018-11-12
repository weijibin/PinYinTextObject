#include "phoneticedit.h"

#include <QLabel>
PhoneticEdit::PhoneticEdit(QWidget *parent) : QWidget(parent)
{
    QLabel *label = new QLabel(this);
    label->setText("Phonetic Edit");
    setMinimumSize(200,200);
}
