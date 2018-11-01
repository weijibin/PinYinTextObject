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

#include "chinesecharacterobject.h"
#include "svgobject.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setupTextObject();
    setupSvgObject();

//    ui->textEdit->setReadOnly(true);
    ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);

    ui->textEdit->setPlaceholderText("Please input the Chinese Characters..........");

    ui->textEdit->document()->setDefaultFont(QFont("KaiTi",40));
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
    QString key_t = QString::fromLocal8Bit("nǐ");
    QString value_t = QString::fromLocal8Bit("你");
    QString key_t1 = QString::fromLocal8Bit("hǎo");
    QString value_t1 = QString::fromLocal8Bit("好");

    insertChineseChar(key_t,value_t);
    insertChineseChar(key_t1,value_t1);
}

void Widget::insertChineseChar(QString pinyin, QString hanzi)
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

    //=========================
//    QString str = ui->lineEdit->text();
//    qDebug()<<str;
    //========================
}

void Widget::on_Text_clicked()
{
    insertTextObject();
}

void Widget::on_test_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if(cursor.hasSelection())
    {
        qDebug()<<"selected text object";
//        qDebug()<<cursor.selectedText();
//        qDebug()<<cursor.selectedText().size();
//        qDebug()<<cursor.selection().toPlainText();

        int current = cursor.position();
        int start = cursor.selectionStart();
        int end = cursor.selectionEnd();


        for(int i = start+1; i <= end ; i++)
        {
            cursor.setPosition(i);
            auto charFormat = cursor.charFormat();
            QVariantMap map = charFormat.property(Widget::CharacterData).toMap();
            qDebug()<<map.firstKey();
            qDebug()<<map.first().toString();
        }

        cursor.setPosition(start);
        cursor.setPosition(end,QTextCursor::KeepAnchor);

        //待定
        ui->textEdit->setTextCursor(cursor);
        ui->textEdit->setFocus();
        qDebug()<<"end";
    }
}
