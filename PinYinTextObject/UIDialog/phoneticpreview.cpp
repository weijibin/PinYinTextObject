#include "phoneticpreview.h"
#include <QLabel>

PhoneticPreview::PhoneticPreview(QWidget *parent) : QWidget(parent)
{
    QLabel *label = new QLabel(this);
    label->setText("Phonetic Prview");
    setMinimumSize(200,200);
}
