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

#include "chinesecharacterobject.h"
#include "svgobject.h"
#include "UIDialog/phoneticdialog.h"

QMap<QString,QStringList> Widget::m_PinYinAll = QMap<QString,QStringList>();

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    QTime t;
//    t.start();
//    readPinYinData();
//    qDebug()<<"Spend Time:::"<<t.elapsed(); // maximum time 2 second

    QtConcurrent::run(&Widget::readPinYinData);

    setupTextObject();
    setupSvgObject();

    ui->textEdit_Source->setLineWrapMode(QTextEdit::NoWrap);
    ui->textEdit_Source->setPlaceholderText("Please input the Chinese Characters..........");
    ui->textEdit_Source->document()->setDefaultFont(QFont("KaiTi",15));

//    ui->textEdit->setReadOnly(true);
    ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
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

void Widget::setupSvgObject()
{
    QObject *svgInterface = new SvgObject;
    svgInterface->setParent(this);
    ui->textEdit->document()->documentLayout()->registerHandler(SvgTextFormat, svgInterface);
}

void Widget::setupTextObject()
{
    QObject *textInterface = new ChineseCharacterObject;
    textInterface->setParent(this);
    ui->textEdit->document()->documentLayout()->registerHandler(ChineseCharFormat, textInterface);
}

void Widget::insertSvgObject()
{
    QString fileName = ":/leaf.svg";
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error Opening File"),
                             tr("Could not open '%1'").arg(fileName));
    }

    QByteArray svgData = file.readAll();

    QTextCharFormat svgCharFormat;
    svgCharFormat.setObjectType(SvgTextFormat);
    QSvgRenderer renderer(svgData);

    QImage svgBufferImage(renderer.defaultSize(), QImage::Format_ARGB32);
    QPainter painter(&svgBufferImage);
    renderer.render(&painter, svgBufferImage.rect());

    svgCharFormat.setProperty(SvgData, svgBufferImage);

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.insertText(QString(QChar::ObjectReplacementCharacter), svgCharFormat);
    ui->textEdit->setTextCursor(cursor);
}

void Widget::insertTextObject()
{
    QString key_t = QString::fromLocal8Bit("nǐ");
    QString value_t = QString::fromLocal8Bit("你");
    QString key_t1 = QString::fromLocal8Bit("hǎo");
    QString value_t1 = QString::fromLocal8Bit("好");

    insertChineseChar(key_t,value_t);
    insertChineseChar(key_t1,value_t1);
}

void Widget::insertChineseChar(const QString &pinyin, const QString &hanzi)
{
    QVariantMap map;
    map.insert(pinyin,hanzi);
    QTextCharFormat chineseCharFormat;
    chineseCharFormat.setObjectType(ChineseCharFormat);
    QTextCursor cursor = ui->textEdit->textCursor();
    chineseCharFormat.setProperty(CharacterData, map);
    cursor.insertText(QString(QChar::ObjectReplacementCharacter), chineseCharFormat);
}

void Widget::on_Svg_clicked()
{
    insertSvgObject();
}

void Widget::on_Text_clicked()
{
    m_HZPY.clear();
    ui->textEdit->clear();
    QString str = ui->textEdit_Source->toPlainText();
    int count = str.count();
    QString key_t;
    QString value_t ;
    for(int i = 0; i< count; i++)
    {
        key_t = "";
        value_t = str.at(i);
        if(m_PinYinAll.contains(value_t))
        {             
            key_t = m_PinYinAll.value(value_t).first();
        }
        if(value_t == "\n")
        {
            insertSystemChar(key_t,value_t);
        }
        else
        {
            insertChineseChar(key_t,value_t);
        }
        m_HZPY.append(QPair<QString,QString>(key_t,value_t));
    }
}

void Widget::insertSystemChar(const QString & key, const QString &value)
{
    QVariantMap map;
    map.insert(key,value);
    QTextCharFormat format;
    format.setProperty(CharacterData, map);
    QTextCursor cur = ui->textEdit->textCursor();
    cur.insertText(value, format);
}

void Widget::changeTextColor(QString color)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.select(QTextCursor::Document);
    QTextCharFormat tcf;
    tcf.setForeground(QColor(color));
    cursor.mergeCharFormat(tcf);
}

void Widget::on_test_clicked()
{

    PhoneticDialog dlg;
    dlg.exec();

//    changeTextColor("#aa00ff");

//    QTextCursor cursor = ui->textEdit->textCursor();
//    if(cursor.hasSelection())
//    {
//        int start = cursor.selectionStart();
//        int end = cursor.selectionEnd();
//        qDebug()<<"start::"<<start<<"end::"<<end;
//        for(int i = start; i < end ; i++)
//        {
//            QString str = m_HZPY.at(i).first;
//            QString str1 = m_HZPY.at(i).second;
//            qDebug()<<"str::"<<str<<"===="<<str1;
//        }
//        qDebug()<<"end";
//    }
}
