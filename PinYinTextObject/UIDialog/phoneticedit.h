#ifndef PHONETICEDIT_H
#define PHONETICEDIT_H

#include <QWidget>
class QPushButton;
class QWidget;
class PhoneticTextEdit;

class PhoneticEdit : public QWidget
{
    Q_OBJECT
public:
    explicit PhoneticEdit(QWidget *parent = nullptr);

signals:

public slots:

private:
    void initUI();

private:
    QPushButton * m_change = nullptr;
    QPushButton * m_default = nullptr;
    QPushButton * m_clear = nullptr;
    QPushButton *m_save = nullptr;
    QPushButton * m_cancel = nullptr;

    PhoneticTextEdit * m_phonetic = nullptr;
    QWidget *  m_edit = nullptr;
};

#endif // PHONETICEDIT_H
