#include "chinesecharacterobject.h"
#include "widget.h"
#include <QPainter>
#include <QVariantMap>
#include <QVariant>
#include <QDebug>

ChineseCharacterObject::ChineseCharacterObject()
{

}

QSizeF ChineseCharacterObject::intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
    QSize size(50,50);
    return QSizeF(size);
}

void ChineseCharacterObject::drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
    QVariantMap map = qvariant_cast<QVariantMap>(format.property(Widget::CharacterData));
//    qDebug()<< map.first().toString();

    painter->drawText(QRectF(rect.topLeft(),QSizeF(50,15)),map.firstKey());
    painter->drawText(QRectF(rect.topLeft()+QPointF(0,20),QSizeF(50,30)),map.first().toString());
}
