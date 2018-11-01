#include "chinesecharacterobject.h"
#include "widget.h"
#include <QPainter>
#include <QVariantMap>
#include <QVariant>
#include <QDebug>
#include <QFont>
#include <QFontMetrics>
#include <QFontMetricsF>
#include <QColor>
#include <QBrush>

const int margin = 3;
ChineseCharacterObject::ChineseCharacterObject()
{
    m_pinyin.setPointSizeF(15);
    m_pinyin.setFamily("Roman");

    m_hanzi.setPointSizeF(20);
    m_hanzi.setFamily("KaiTi");

//    m_metricsPY
}

QSizeF ChineseCharacterObject::intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
    QFont f = format.toCharFormat().font();
    QVariantMap map = qvariant_cast<QVariantMap>(format.property(Widget::CharacterData));
    QFontMetricsF metrics(f);

    qreal t_w = metrics.width(map.firstKey());
    qreal b_w = metrics.width(map.first().toString());
    qreal h = metrics.height();

    QSizeF size(qMax(t_w,b_w)+2*margin,2*h+2*margin);
    return size;
}

void ChineseCharacterObject::drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
    QFont f = format.toCharFormat().font();
    QVariantMap map = qvariant_cast<QVariantMap>(format.property(Widget::CharacterData));
    QFontMetricsF metrics(f);

    qreal t_w = metrics.width(map.firstKey());
    qreal b_w = metrics.width(map.first().toString());
    qreal h = metrics.height();

    qreal w = qMax(t_w,b_w);

    painter->save();
    painter->setFont(f);
    painter->setBrush(format.foreground());
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->drawText(QRectF(rect.topLeft()+QPointF(margin+((w-t_w)/2),margin),QSizeF(t_w,h)),map.firstKey());
    painter->drawText(QRectF(rect.topLeft()+QPointF(margin+((w-b_w)/2),margin+h),QSizeF(b_w,h)),map.first().toString());
    painter->restore();
}
