#ifndef PHONETICPREVIEW_H
#define PHONETICPREVIEW_H

#include <QWidget>

class QPushButton;
class QTextEdit;
class PhoneticTextEdit;
class QLabel;

class PhoneticPreview : public QWidget
{
    Q_OBJECT
public:
    explicit PhoneticPreview(QWidget *parent = nullptr);

signals:
    void sigInsert(const QList<QPair<QString,QString>> & hzpy);
    void sigEdit(const QList<QPair<QString,QString>> & hzpy);
public slots:

private slots:

private:
    void initUI();
    void connectSignals();

private:
    QPushButton * m_clear = nullptr;
    QPushButton * m_phonetic = nullptr;
    QPushButton * m_edit = nullptr;
    QPushButton * m_insert = nullptr;

    QTextEdit * m_textEdit = nullptr;
    PhoneticTextEdit * m_preview = nullptr;

};

#endif // PHONETICPREVIEW_H
