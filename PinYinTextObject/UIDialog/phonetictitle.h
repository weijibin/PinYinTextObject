#ifndef PHONETICTITLE_H
#define PHONETICTITLE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class PhoneticTitle : public QWidget
{
    Q_OBJECT
public:
    explicit PhoneticTitle(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent *) override;

private:
    void initUI();
    void connetSignals();
private:
    QLabel *m_label = nullptr;
    QPushButton *m_close = nullptr;
    QPushButton *m_title = nullptr;
    QPushButton *m_helper = nullptr;

    QWidget			*m_pTopParent = nullptr;	//顶层窗体
    QPoint			m_PressPoint;	//鼠标按下时位置
};

#endif // PHONETICTITLE_H
