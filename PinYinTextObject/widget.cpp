#include "widget.h"
#include "ui_widget.h"

#include <QSvgRenderer>
#include <QMessageBox>
#include <QPainter>

#include "chinesecharacterobject.h"
#include "svgobject.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setupTextObject();
    setupSvgObject();
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
    QString fileName = ":/heart.svg";
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

}

void Widget::on_Svg_clicked()
{
    insertSvgObject();
}

void Widget::on_Text_clicked()
{
    insertTextObject();
}
