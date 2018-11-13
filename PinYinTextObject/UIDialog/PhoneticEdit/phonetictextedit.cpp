#include "phonetictextedit.h"
#include "chinesecharacterobject.h"
#include "../../widget.h"
#include <QDebug>

PhoneticTextEdit::PhoneticTextEdit()
{
//    ui->textEdit_Source->setLineWrapMode(QTextEdit::NoWrap);
//    ui->textEdit_Source->setPlaceholderText("Please input the Chinese Characters..........");
//    ui->textEdit_Source->document()->setDefaultFont(QFont("KaiTi",15));

    this->setLineWrapMode(QTextEdit::NoWrap);
    this->setReadOnly(true);
    setupTextObject();
}

void PhoneticTextEdit::setupTextObject()
{
    QObject *textInterface = new ChineseCharacterObject;
    textInterface->setParent(this);
    this->document()->documentLayout()->registerHandler(ChineseCharacterObject::ChineseCharFormat, textInterface);
}

void PhoneticTextEdit::insertChineseChar(const QString &pinyin, const QString &hanzi)
{
    QVariantMap map;
    map.insert(pinyin,hanzi);
    QTextCharFormat chineseCharFormat;
    chineseCharFormat.setObjectType(ChineseCharacterObject::ChineseCharFormat);
    QTextCursor cursor = this->textCursor();
    chineseCharFormat.setProperty(ChineseCharacterObject::CharacterData, map);
    cursor.insertText(QString(QChar::ObjectReplacementCharacter), chineseCharFormat);
}

void PhoneticTextEdit::insertSystemChar(const QString & key, const QString &value)
{
    QVariantMap map;
    map.insert(key,value);
    QTextCharFormat format;
    format.setProperty(ChineseCharacterObject::CharacterData, map);
    QTextCursor cur = this->textCursor();
    cur.insertText(value, format);
}

void PhoneticTextEdit::changeTextColor(QString color)
{
    m_color = color;
    QTextCursor cursor = this->textCursor();
    cursor.select(QTextCursor::Document);
    QTextCharFormat tcf;
    tcf.setForeground(QColor(color));
    cursor.mergeCharFormat(tcf);
}

const QList<QPair<QString, QString> > &PhoneticTextEdit::getHZPY() const
{
    return m_HZPY;
}

QList<int> PhoneticTextEdit::getSelectedHZPY() const
{
    QList<int> lst;
//    QList<QPair<QString,QString>> pinyin;
    QTextCursor cursor = this->textCursor();
    if(cursor.hasSelection())
    {
        int start = cursor.selectionStart();
        int end = cursor.selectionEnd();
//        qDebug()<<"start::"<<start<<"end::"<<end;
        for(int i = start; i < end ; i++)
        {
            QString str = m_HZPY.at(i).first;
            QString str1 = m_HZPY.at(i).second;
            if(Widget::getPinYinAll().keys().contains(str1))
            {
//                pinyin.append(QPair<QString,QString>(str,str1));
                lst.append(i);
                qDebug()<<"i::"<<"str::"<<str<<"===="<<str1;
            }
        }
//       qDebug()<<"end";
   }
    return lst;
}

void PhoneticTextEdit::setChineseString(QString str)
{
    m_HZPY.clear();
    this->clear();
    int count = str.count();
    QString hanzi;
    QString pinyin ;
    for(int i = 0; i< count; i++)
    {
        pinyin = "";
        hanzi = str.at(i);
        if(Widget::getPinYinAll().contains(hanzi))
        {
            pinyin = Widget::getPinYinAll().value(hanzi).first();
        }
        if(hanzi == "\n")
        {
            insertSystemChar(pinyin,hanzi);
        }
        else
        {
            insertChineseChar(pinyin,hanzi);
        }
        m_HZPY.append(QPair<QString,QString>(pinyin,hanzi));
    }
}


void PhoneticTextEdit::setChinesePhoneticNotation(const QList<QPair<QString, QString>> &hzpy)
{
    m_HZPY.clear();
    this->clear();
    int count = hzpy.count();
    QString pinyin;
    QString hanzi;
    for(int i = 0; i < count; i++)
    {
        pinyin = hzpy.at(i).first;
        hanzi = hzpy.at(i).second;

        if(hanzi == "\n")
        {
            insertSystemChar(pinyin,hanzi);
        }
        else
        {
            insertChineseChar(pinyin,hanzi);
        }
        m_HZPY.append(QPair<QString,QString>(pinyin,hanzi));
    }
}
