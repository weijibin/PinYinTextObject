#include "phoneticedit.h"

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include "PhoneticEdit/phonetictextedit.h"
#include "PhoneticTableView/phoneticview.h"

PhoneticEdit::PhoneticEdit(QWidget *parent) : QWidget(parent)
{
    initUI();
    connectSignals();
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

    m_phonetic = new PhoneticTextEdit;
    m_phonetic->setFixedHeight(190);

    m_edit = new PhoneticView;
    m_edit->setFixedHeight(192);

    QVBoxLayout * layout = new QVBoxLayout;

    QHBoxLayout * layout1 = new QHBoxLayout;
    QHBoxLayout * layout2 = new QHBoxLayout;
    QHBoxLayout * layout3 = new QHBoxLayout;

    layout1->addWidget(m_phonetic);
    QVBoxLayout * layout11 = new QVBoxLayout;
    layout11->addStretch();
    layout11->addWidget(m_change);
    layout11->addStretch();
    layout1->addLayout(layout11);

    layout2->addWidget(m_edit);
//    layout2->addStretch();
    QVBoxLayout * layout21 = new QVBoxLayout;
    layout21->addWidget(m_default);
    layout21->addWidget(m_clear);
    layout2->addLayout(layout21);

    layout3->addStretch();
    layout3->addWidget(m_save);
    layout3->addWidget(m_cancel);

    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    this->setLayout(layout);
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
        m_edit->initData(lst, m_phonetic->getHZPY());

        m_isHaveChanged = true;
        updateBtnState();
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
