#include "hhphonetictip.h"
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>

HHPhoneticTip::HHPhoneticTip(QWidget *parent) : QWidget(parent)
{
    initUI();
}

void HHPhoneticTip::initUI()
{
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    double fScaleFactor = qApp->property("scalefactor").toDouble();
    if(fScaleFactor < 1.0)
    {
        fScaleFactor = 1.0;
    }

    QFrame *pBorderFrame = new QFrame(this);
    pBorderFrame->setObjectName("baseFrame");
    pBorderFrame->setStyleSheet("QFrame#baseFrame{border:0px solid #cccccc;background-color: rgb(255, 255, 255);border-radius:5px}");
    pBorderFrame->setGeometry(0, 0, this->width(), this->height());

    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *pDropShadowUI = new QGraphicsDropShadowEffect(this);
    pDropShadowUI->setOffset(0, 0);
    pDropShadowUI->setColor(QColor("#CCCCCC"));
    pDropShadowUI->setBlurRadius(10 * fScaleFactor);

    pBorderFrame->setGraphicsEffect(pDropShadowUI);

    QHBoxLayout *pLyt = new QHBoxLayout;
    pLyt->setMargin(5 * fScaleFactor);
    pLyt->setSpacing(0);
    pLyt->addWidget(pBorderFrame);

    this->setLayout(pLyt);

    m_pToolTipLabel = new QLabel(this);

    QFont font = m_pToolTipLabel->font();
    font.setPixelSize(12 * fScaleFactor);
    m_pToolTipLabel->setFont(font);
    m_pToolTipLabel->setText(m_Tip);

    QHBoxLayout *pLayout = new QHBoxLayout(pBorderFrame);
    pLayout->setMargin(5 * fScaleFactor);
    pLayout->setSpacing(0);
    pLayout->addWidget(m_pToolTipLabel);
    pBorderFrame->setLayout(pLayout);

    this->adjustSize();
}

void HHPhoneticTip::setShowText(QString str)
{
    m_Tip = str;
    m_pToolTipLabel->setText(m_Tip);
}
