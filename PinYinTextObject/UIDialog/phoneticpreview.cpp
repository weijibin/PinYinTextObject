#include "phoneticpreview.h"
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "PhoneticEdit/phonetictextedit.h"

PhoneticPreview::PhoneticPreview(QWidget *parent) : QWidget(parent)
{
    initUI();
    connectSignals();
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
}

void PhoneticPreview::initUI()
{
    m_clear = new QPushButton;
    m_clear->setText("清除");
    m_phonetic = new QPushButton;
    m_phonetic->setText("注音");
    m_edit = new QPushButton;
    m_edit->setText("编辑");
    m_insert = new QPushButton;
    m_insert->setText("插入白板");

    m_textEdit = new QTextEdit;
    m_preview = new PhoneticTextEdit;

    m_textEdit->setLineWrapMode(QTextEdit::NoWrap);
    m_textEdit->setPlaceholderText("Please input the Chinese Characters..........");
    m_textEdit->document()->setDefaultFont(QFont("KaiTi",15));

    QVBoxLayout * layout = new QVBoxLayout;
    QHBoxLayout * layout1 = new QHBoxLayout;
    QHBoxLayout * layout2 = new QHBoxLayout;
    QHBoxLayout * layout3 = new QHBoxLayout;

    layout1->addWidget(m_textEdit);
    QVBoxLayout *layout11 = new QVBoxLayout;
    layout11->addWidget(m_phonetic);
    layout11->addWidget(m_clear);
    layout1->addLayout(layout11);


    layout2->addWidget(m_preview);
    QVBoxLayout *layout21 = new QVBoxLayout;
    layout21->addStretch();
    layout21->addWidget(m_edit);
    layout21->addStretch();
    layout2->addLayout(layout21);

    layout3->addStretch();
    layout3->addWidget(m_insert);

    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    this->setLayout(layout);
}
