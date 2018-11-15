#include "phoneticedit.h"

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QStyleOption>
#include <QPainter>
#include "PhoneticEdit/phonetictextedit.h"
#include "PhoneticTableView/phoneticview.h"

PhoneticEdit::PhoneticEdit(QWidget *parent) : QWidget(parent)
{
    initUI();
    connectSignals();
    setObjectName("phoneticEdit");
}

void PhoneticEdit::setChineseChars(const QList<QPair<QString, QString> > &hzpy)
{
    if(m_phonetic != nullptr)
    {
        m_phonetic->setChinesePhoneticNotation(hzpy);
    }
}

void PhoneticEdit::initUI()
{
    m_change = new QPushButton;
    m_change->setText("修改");
    m_default = new QPushButton;
    m_default->setText("默认");
    m_clear = new QPushButton;
    m_clear->setText("清除");
    m_save = new QPushButton;
    m_save->setText("保存");
    m_cancel = new QPushButton;
    m_cancel->setText("取消");

    m_change->setFixedSize(60,24);
    m_default->setFixedSize(60,24);
    m_clear->setFixedSize(60,24);

    m_save->setFixedSize(100,30);
    m_cancel->setFixedSize(100,30);

    m_phonetic = new PhoneticTextEdit;
    m_phonetic->setFixedHeight(190);

    m_edit = new PhoneticView;
    m_edit->setFixedHeight(192);

    {
        m_change->setObjectName("changeBtn");
        m_default->setObjectName("defaultBtn");
        m_clear->setObjectName("clearBtn");

        m_save->setObjectName("saveBtn");
        m_cancel->setObjectName("cancelBtn");

        m_phonetic->setObjectName("changePhonetic");
    }

    QVBoxLayout * layout = new QVBoxLayout;

    QHBoxLayout * layout1 = new QHBoxLayout;
    QHBoxLayout * layout2 = new QHBoxLayout;
    QHBoxLayout * layout3 = new QHBoxLayout;

    layout1->addWidget(m_phonetic);

    QPushButton * btn3 = new QPushButton;
    btn3->setObjectName("segment3");
    btn3->setFixedWidth(2);
    btn3->setFixedHeight(190);
    btn3->setEnabled(false);
    layout1->addWidget(btn3);

    QVBoxLayout * layout11 = new QVBoxLayout;
    layout11->addStretch();
    layout11->addWidget(m_change);
    layout11->addStretch();
    layout1->addLayout(layout11);

    QWidget * w1 = new QWidget(this);
    w1->setObjectName("changeWidget");
    w1->setLayout(layout1);
    w1->setContentsMargins(20,0,0,0);
    layout1->setContentsMargins(0,0,0,0);
    layout11->setContentsMargins(20,0,20,0);


    layout2->addWidget(m_edit);

    QPushButton * btn4 = new QPushButton;
    btn4->setObjectName("segment4");
    btn4->setFixedWidth(2);
    btn4->setFixedHeight(190);
    btn4->setEnabled(false);
    layout2->addWidget(btn4);

    QVBoxLayout * layout21 = new QVBoxLayout;
    layout21->addWidget(m_default);
    layout21->addWidget(m_clear);
    layout2->addLayout(layout21);

    QWidget * w2 = new QWidget(this);
    w2->setObjectName("viewWidget");
    w2->setLayout(layout2);
    w2->setContentsMargins(20,0,0,0);
    layout2->setContentsMargins(0,0,0,0);
    layout21->setContentsMargins(20,0,20,0);

    layout3->addStretch();
    layout3->addWidget(m_save);
    layout3->addWidget(m_cancel);
    layout3->addSpacing(20);
    layout3->setContentsMargins(0,10,0,10);

    layout->addWidget(w1);
    layout->addWidget(w2);
    layout->addLayout(layout3);
    this->setLayout(layout);

    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    this->setContentsMargins(0,0,0,0);
}

void PhoneticEdit::connectSignals()
{
    connect(m_save,&QPushButton::clicked,[=]()
    {
        emit sigSave(m_edit->getPhoneticData());
    });

    connect(m_cancel,&QPushButton::clicked,[=]()
    {
        emit sigCancel();
    });

    connect(m_change,&QPushButton::clicked,[=]()
    {
        QList<int> lst = m_phonetic->getSelectedHZPY();
        if(lst.count()>0)
        {
            m_edit->initData(lst, m_phonetic->getHZPY());
            m_isHaveChanged = true;
            updateBtnState();
        }
    });

    connect(m_phonetic,&PhoneticTextEdit::textChanged,[=]()
    {
        updateBtnState();
    });

    connect(m_phonetic,&PhoneticTextEdit::selectionChanged,[=]()
    {
        updateBtnState();
    });
}

void PhoneticEdit::updateBtnState()
{
    bool changeState = m_phonetic->textCursor().hasSelection();

    bool defaultState = m_isHaveChanged;
    bool clearState = m_isHaveChanged;

    bool saveState = true;
    bool cancelState = true;

    m_change->setEnabled(changeState);
    m_default->setEnabled(defaultState);
    m_clear->setEnabled(clearState);
    m_save->setEnabled(saveState);
    m_cancel->setEnabled(cancelState);
}

void PhoneticEdit::paintEvent(QPaintEvent* )
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
