#include "phoneticdialog.h"
#include <QStackedLayout>
#include "phoneticedit.h"
#include "phoneticpreview.h"
#include "phonetictitle.h"

#include <QVBoxLayout>
#include <QFile>

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

    QFile file(":/UIDialog/style.qss");
    if(file.open(QFile::ReadOnly))
    {
        setStyleSheet(file.readAll());
        file.close();
    }
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
//    m_stackLayout->setCurrentIndex(1);

    connectSignals();
}

void PhoneticDialog::connectSignals()
{
    connect(m_preview,&PhoneticPreview::sigInsert,this,&PhoneticDialog::sltInsert);
}

void PhoneticDialog::sltInsert(const QList<QPair<QString, QString> > &hzpy)
{
    emit sigInsert(hzpy);
    close();
}

