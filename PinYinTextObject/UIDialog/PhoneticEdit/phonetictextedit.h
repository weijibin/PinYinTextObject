#ifndef PHONETICTEXTEDIT_H
#define PHONETICTEXTEDIT_H
#include <QTextEdit>

class PhoneticTextEdit : public QTextEdit
{
public:
    PhoneticTextEdit();
    void setChineseString(QString str);
    void setChinesePhoneticNotation(const QList<QPair<QString,QString>> &hzpy);
    void changeTextColor(QString color);
    const QList<QPair<QString,QString>>& getHZPY() const;
    QList<int> getSelectedHZPY() const;

private:
    void setupTextObject();
    void insertChineseChar(const QString &pinyin,const QString &hanzi);
    void insertSystemChar(const QString & key, const QString &value);

private:
    QList<QPair<QString,QString>> m_HZPY;

    QString m_color = "";
};

#endif // PHONETICTEXTEDIT_H
