#include "phoneticpreview.h"
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include "PhoneticEdit/phonetictextedit.h"

PhoneticPreview::PhoneticPreview(QWidget *parent) : QWidget(parent)
{
    initUI();
    connectSignals();
    setObjectName("phoneticPreview");
}

void PhoneticPreview::setChineseChars(const QList<QPair<QString, QString> > &hzpy)
{
    if(m_preview != nullptr)
    {
        m_preview->setChinesePhoneticNotation(hzpy);
    }
}

void PhoneticPreview::setCurrentHZPY(const QList<QPair<QString, QString> > &hzpy)
{
    if(m_preview != nullptr)
    {
        QString str = getStringFromHZPY(hzpy);
        m_textEdit->setText(str);
        m_preview->setChinesePhoneticNotation(hzpy);
    }
}

QString PhoneticPreview::getStringFromHZPY(const QList<QPair<QString, QString> > &hzpy)
{
    QString str;

    if(hzpy.count()>0)
    {
        for(QPair<QString,QString> i : hzpy)
        {
            str += i.second;
        }
    }

    return str;
}

void PhoneticPreview::connectSignals()
{
    connect(m_clear,&QPushButton::clicked,[=]()
    {
        m_textEdit->clear();
    });

    connect(m_insert,&QPushButton::clicked,[=]()
    {
        if(m_preview->getHZPY().count()>1)
        {
            emit sigInsert(m_preview->getHZPY());
        }
    });

    connect(m_phonetic,&QPushButton::clicked,[=]()
    {
        if(m_textEdit->toPlainText()>1)
        {
            m_preview->setChineseString(m_textEdit->toPlainText());
        }
    });

    connect(m_edit,&QPushButton::clicked,[=]()
    {
        if(m_preview->getHZPY().count()>1)
        {
            emit sigEdit(m_preview->getHZPY());
        }
    });

    connect(m_textEdit, &QTextEdit::textChanged,[=]()
    {
        this->updateBtnState();
    });

    connect(m_preview, &PhoneticTextEdit::textChanged,[=]()
    {
        this->updateBtnState();
    });
}

void PhoneticPreview::initUI()
{
    m_clear = new QPushButton;
    m_clear->setText("清除");
    m_phonetic = new QPushButton;
    m_phonetic->setText("注音");
    m_edit = new QPushButton;
    m_edit->setText("编辑");

    m_clear->setFixedSize(60,24);
    m_phonetic->setFixedSize(60,24);
    m_edit->setFixedSize(60,24);

    m_insert = new QPushButton;
    m_insert->setText("插入白板");
    m_insert->setFixedSize(100,30);

    m_textEdit = new QTextEdit;
    m_preview = new PhoneticTextEdit;

    m_textEdit->setFixedHeight(190);
    m_preview->setFixedHeight(192);

    {
        m_phonetic->setObjectName("phoneticBtn");
        m_edit->setObjectName("preDefaultBtn");
        m_clear->setObjectName("preClearBtn");
        m_insert->setObjectName("insertBtn");

        m_textEdit->setObjectName("preTextEdit");
        m_preview->setObjectName("prePhonetic");
    }

    m_textEdit->setLineWrapMode(QTextEdit::NoWrap);
    m_textEdit->setPlaceholderText("Please input the Chinese Characters..........");
    m_textEdit->document()->setDefaultFont(QFont("KaiTi",15));

    QVBoxLayout * layout = new QVBoxLayout;
    QHBoxLayout * layout1 = new QHBoxLayout;
    QHBoxLayout * layout2 = new QHBoxLayout;
    QHBoxLayout * layout3 = new QHBoxLayout;

    layout1->addWidget(m_textEdit);

    QPushButton * btn1 = new QPushButton;
    btn1->setObjectName("segment1");
    btn1->setFixedWidth(2);
    btn1->setFixedHeight(190);
    btn1->setEnabled(false);
    layout1->addWidget(btn1);

    QVBoxLayout *layout11 = new QVBoxLayout;
    layout11->addWidget(m_phonetic);
    layout11->addWidget(m_clear);
    layout1->addLayout(layout11);

    QWidget * w1 = new QWidget(this);
    w1->setObjectName("inputWidget");
    w1->setLayout(layout1);
    w1->setContentsMargins(20,0,0,0);
    layout1->setContentsMargins(0,0,0,0);
    layout11->setContentsMargins(20,0,20,0);

    layout2->addWidget(m_preview);

    QPushButton * btn2 = new QPushButton;
    btn2->setObjectName("segment2");
    btn2->setFixedWidth(2);
    btn2->setFixedHeight(190);
    btn2->setEnabled(false);
    layout2->addWidget(btn2);

    QVBoxLayout *layout21 = new QVBoxLayout;
    layout21->addStretch();
    layout21->addWidget(m_edit);
    layout21->addStretch();
    layout2->addLayout(layout21);

    QWidget * w2 = new QWidget(this);
    w2->setObjectName("previewWidget");
    w2->setLayout(layout2);
    w2->setContentsMargins(20,0,0,0);
    layout2->setContentsMargins(0,0,0,0);
    layout21->setContentsMargins(20,0,20,0);

    layout3->addStretch();
    layout3->addWidget(m_insert);
    layout3->addSpacing(20);
    layout3->setContentsMargins(0,10,0,10);

    layout->addWidget(w1);
    layout->addWidget(w2);
    layout->addLayout(layout3);
    this->setLayout(layout);

    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    this->setContentsMargins(0,0,0,0);
    updateBtnState();
}


void PhoneticPreview::updateBtnState()
{
    bool phoneticState = m_textEdit->toPlainText().count()>0;
    bool editState = m_preview->getHZPY().count()>0;
    bool clearState = phoneticState;
    bool insertState = editState;

    m_phonetic->setEnabled(phoneticState);
    m_clear->setEnabled(clearState);
    m_edit->setEnabled(editState);
    m_insert->setEnabled(insertState);
}

void PhoneticPreview::paintEvent(QPaintEvent* )
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
