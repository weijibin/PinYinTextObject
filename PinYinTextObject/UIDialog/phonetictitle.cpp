#include "phonetictitle.h"
#include <QLabel>
#include <QMouseEvent>
#include <QHBoxLayout>

PhoneticTitle::PhoneticTitle(QWidget *parent) : QWidget(parent)
{
    initUI();
    connetSignals();
}

void PhoneticTitle::initUI()
{
    int fixHeight = 32;
    this->setMouseTracking(true);
    setObjectName("phonetictitle");
    setFixedHeight(fixHeight);

    m_title = new QPushButton;
    m_title->setText("注音");
    m_title->setFixedWidth(50);
    m_title->setFixedHeight(fixHeight);

    m_helper = new QPushButton;
    m_helper->setText("helper");
    m_helper->setFixedWidth(fixHeight);
    m_helper->setFixedHeight(fixHeight);
    m_label = new QLabel;
    m_label->setText("Phonetic Title");
    m_label->setFixedHeight(fixHeight);
    m_close = new QPushButton;
    m_close->setText("close");
    m_close->setFixedWidth(fixHeight);
    m_close->setFixedHeight(fixHeight);

    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->addWidget(m_title);
    layout->addWidget(m_helper);
    layout->addWidget(m_label);
    layout->addStretch();
    layout->addWidget(m_close);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    this->setLayout(layout);

    this->setContentsMargins(0,0,0,0);

    this->setFixedHeight(fixHeight);

    m_pTopParent = this;
    if(m_pTopParent->parent())
    {
        m_pTopParent = (QWidget*) m_pTopParent->parent();
    }
}

void PhoneticTitle::connetSignals()
{
    connect(m_close,&QPushButton::clicked , [=](){
       m_pTopParent->close();
    });
}

void PhoneticTitle::mousePressEvent(QMouseEvent *e)
{
    m_PressPoint = e->pos();
}

void PhoneticTitle::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        QPoint pos = e->globalPos();
        m_pTopParent->move(pos - m_PressPoint);
    }
}

