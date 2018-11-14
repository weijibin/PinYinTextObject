#ifndef PHONETICEDIT_H
#define PHONETICEDIT_H

#include <QWidget>
class QPushButton;
class QWidget;
class PhoneticTextEdit;
class PhoneticView;

class PhoneticEdit : public QWidget
{
    Q_OBJECT
public:
    explicit PhoneticEdit(QWidget *parent = nullptr);

    void setChineseChars(const QList<QPair<QString, QString> > &hzpy);

signals:
    void sigSave(const QList<QPair<QString, QString> > &hzpy);
    void sigCancel();

public slots:

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void initUI();
    void connectSignals();

    void updateBtnState();

private:
    QPushButton * m_change = nullptr;
    QPushButton * m_default = nullptr;
    QPushButton * m_clear = nullptr;
    QPushButton *m_save = nullptr;
    QPushButton * m_cancel = nullptr;

    PhoneticTextEdit * m_phonetic = nullptr;
    PhoneticView * m_edit = nullptr;

    bool m_isHaveChanged = false;
};

#endif // PHONETICEDIT_H
