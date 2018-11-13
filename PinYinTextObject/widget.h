#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextFormat>

namespace Ui {
class Widget;
}

class PhoneticTextEdit;
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    static QMap<QString,QStringList> getPinYinAll() {return m_PinYinAll;}
    static QMap<QString,QStringList> m_PinYinAll;
    static void readPinYinData();

private:


private slots:
    void on_test_clicked();

    void on_edit_clicked();

private:
    Ui::Widget *ui;

    PhoneticTextEdit * m_phoneticEdit = nullptr;
};

#endif // WIDGET_H
