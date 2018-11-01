#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextFormat>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    enum { SvgTextFormat = QTextFormat::UserObject + 1 ,
                 ChineseCharFormat = QTextFormat::UserObject + 2   };
    enum ObjectProperties { SvgData = 1 ,CharacterData = 2};

    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void insertTextObject();
    void insertChineseChar(QString pinyin,QString hanzi);

    void insertSvgObject();

    void setupTextObject();
    void setupSvgObject();

private slots:
    void on_Svg_clicked();
    void on_Text_clicked();

    void on_test_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
