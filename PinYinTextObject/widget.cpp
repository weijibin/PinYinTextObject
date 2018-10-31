#include "widget.h"
#include "ui_widget.h"

#include <QSvgRenderer>
#include <QMessageBox>
#include <QPainter>
#include <QTextCharFormat>
#include <QDebug>
#include <QTextCodec>

#include "chinesecharacterobject.h"
#include "svgobject.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setupTextObject();
    setupSvgObject();

    QString str = QTextCodec::codecForLocale()->name();

    qDebug()<<str;
//    ui->lineEdit->setText("我");  // 会乱码  //源文件使用的utf8 编码 而 转换的时候使用的 system 转的 所以乱码

//    ui->lineEdit->setText(QString::fromLocal8Bit("我")); // 不会乱码
}

Widget::~Widget()
{
    delete ui;
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
    QTextCharFormat chineseCharFormat;
    chineseCharFormat.setObjectType(ChineseCharFormat);

    QVariantMap map;
    QString key_t = "ni";
    QString value_t = QString::fromLocal8Bit("你");
    map.insert(key_t,value_t);

    QVariantMap map1;
    QString key_t1 = "hao";
    QString value_t1 = QString::fromLocal8Bit("好");
    map1.insert(key_t1,value_t1);

    QTextCursor cursor = ui->textEdit->textCursor();

    chineseCharFormat.setProperty(CharacterData, map);
    cursor.insertText(QString(QChar::ObjectReplacementCharacter), chineseCharFormat);
    chineseCharFormat.setProperty(CharacterData, map1);
    cursor.insertText(QString(QChar::ObjectReplacementCharacter), chineseCharFormat);
}

void Widget::on_Svg_clicked()
{
    insertSvgObject();

    //=========================
    QString str = ui->lineEdit->text();
    qDebug()<<str;
    //========================
}

void Widget::on_Text_clicked()
{
    insertTextObject();
}
