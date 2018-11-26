#ifndef HHPHONETICTIP_H
#define HHPHONETICTIP_H

#include <QWidget>
#include <QLabel>

class HHPhoneticTip : public QWidget
{
    Q_OBJECT
public:
    explicit HHPhoneticTip(QWidget *parent = nullptr);

    void setShowText(QString str);

private:
    void initUI();

private:
    QLabel              *m_pToolTipLabel;
    QString              m_Tip;
};

#endif // HHPHONETICTIP_H
