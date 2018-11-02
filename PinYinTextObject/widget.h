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

    static QMap<QString,QStringList> m_PinYinAll;

private:

    static void readPinYinData();

    void insertTextObject();
    void insertChineseChar(const QString &pinyin,const QString &hanzi);

    void insertEnterChar(const QString & key, const QString &value);

    void insertSvgObject();

    void setupTextObject();
    void setupSvgObject();

private slots:
    void on_Svg_clicked();
    void on_Text_clicked();

    void on_test_clicked();

private:

    QList<QPair<QString,QString>> m_HZPY;

    Ui::Widget *ui;
};

#endif // WIDGET_H
