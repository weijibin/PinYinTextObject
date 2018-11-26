#include "widget.h"
#include "ui_widget.h"

#include <QSvgRenderer>
#include <QMessageBox>
#include <QPainter>
#include <QTextCharFormat>
#include <QDebug>
#include <QTextCodec>
#include <QFont>
#include <QTextDocumentFragment>
#include <QTextFrame>
#include <QTextBlock>
#include <QFile>
#include <QMap>
#include <QStringList>
#include <QtConcurrent>
#include <QFuture>
#include <QTime>

#include "UIDialog/phoneticdialog.h"
#include "UIDialog/PhoneticEdit/phonetictextedit.h"


QMap<QString,QStringList> Widget::m_PinYinAll = QMap<QString,QStringList>();

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QtConcurrent::run(&Widget::readPinYinData);

    m_phoneticEdit = new PhoneticTextEdit;
    ui->verticalLayout->addWidget(m_phoneticEdit);

//    ui->comboBox->addItem("hello");
//    QRegExp rx("^[a-z|A-Z|\u00e0-\u01dc]*$");

//    QRegExp rx("^[āáǎàēéěèīíǐìōóǒòūúǔùǖǘǚǜüêɑńňǹ]*$");
//    QRegExp rx(QString::fromUtf8("^[a-zA-Zāáǎàēéěèīíǐìōóǒòūúǔùǖǘǚǜüêɑńňǹ]*$"));
    QRegExp rx(QString::fromLocal8Bit("^[a-zA-Zāáǎàēéěèīíǐìōóǒòūúǔùǖǘǚǜüêɑńňǹ]*$"));

//    QRegExp rx("^[\u31A0-\u312F]*$");
//    QRegExp rx("^[\ua8a0-\ua8b0]*$");
//    QRegExp rx("^[a-z|A-Z]*$");
    QValidator *validator = new QRegExpValidator(rx);
//    ui->comboBox->setEditText("ǒ123");
    ui->comboBox->setEditable(true);
    ui->comboBox->setValidator(validator);
    ui->comboBox->setCurrentText(QString::fromLocal8Bit("ǒab"));
//    ui->comboBox->setCurrentText("absd");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::readPinYinData()
{
    QFile file(":/word.pyd");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    m_PinYinAll.clear();

    while (!file.atEnd()) {
        QString line = QString::fromUtf8(file.readLine()).trimmed();
        QStringList lst = line.split("|");
        QStringList lstYin = lst.last().split(",");
        m_PinYinAll.insert(lst.first(),lstYin);
    }
}

void Widget::on_test_clicked()
{
        QList<QPair<QString,QString>> hzpy;
        QString str = QString::fromLocal8Bit("你");
        hzpy.append(QPair<QString,QString>(("ni"),str));
        hzpy.append(QPair<QString,QString>(("ni"),str));
        hzpy.append(QPair<QString,QString>(("ni"),str));
        hzpy.append(QPair<QString,QString>(("ni"),str));
        hzpy.append(QPair<QString,QString>(("ni"),("\n")));
        hzpy.append(QPair<QString,QString>(("ni"),str));
        hzpy.append(QPair<QString,QString>(("ni"),str));
        hzpy.append(QPair<QString,QString>(("ni"),("\n")));
        hzpy.append(QPair<QString,QString>(("ni"),str));
        hzpy.append(QPair<QString,QString>(("ni"),str));

        QVariant var = QVariant::fromValue(hzpy);

        qDebug()<<var.value<QList<QPair<QString,QString>>>();

    PhoneticDialog dlg;
    connect(&dlg,&PhoneticDialog::sigInsert,[=](const QList<QPair<QString,QString>> & hzpy){
        m_phoneticEdit->setChinesePhoneticNotation(hzpy);
    });
    dlg.exec();
}

void Widget::on_edit_clicked()
{
    if(m_phoneticEdit->getHZPY().count() > 0)
    {
        PhoneticDialog dlg;
        dlg.setCurrentHZPY(m_phoneticEdit->getHZPY());
        connect(&dlg,&PhoneticDialog::sigInsert,[=](const QList<QPair<QString,QString>> & hzpy){
            m_phoneticEdit->setChinesePhoneticNotation(hzpy);
        });
        dlg.exec();
    }
}
