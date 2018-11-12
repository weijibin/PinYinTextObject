#include "phoneticdialog.h"
#include <QStackedLayout>
#include "phoneticedit.h"
#include "phoneticpreview.h"
#include "phonetictitle.h"

#include <QVBoxLayout>

PhoneticDialog::PhoneticDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    setFixedSize(638,470);
    initUI();
}

void PhoneticDialog::initUI()
{
    initTitle();
    initBody();
    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(m_title);
    layout->addLayout(m_stackLayout);
    this->setLayout(layout);
    this->setContentsMargins(0,0,0,0);
}

void PhoneticDialog::initTitle()
{
    m_title = new PhoneticTitle(this);
}

void PhoneticDialog::initBody()
{
    m_preview = new PhoneticPreview;
    m_edit = new PhoneticEdit;
    m_stackLayout = new QStackedLayout;
    m_stackLayout->addWidget(m_preview);
    m_stackLayout->addWidget(m_edit);
    m_stackLayout->setCurrentIndex(1);
}
