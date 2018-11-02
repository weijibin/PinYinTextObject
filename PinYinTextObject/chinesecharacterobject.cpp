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

const int margin = 1;
ChineseCharacterObject::ChineseCharacterObject()
{
    m_pinyin.setPointSizeF(15);
    m_pinyin.setFamily("Times New Roman");

    m_hanzi.setPointSizeF(20);
    m_hanzi.setFamily("KaiTi");

    m_metricsPY = new QFontMetricsF(m_pinyin);
    m_metricsHZ = new QFontMetricsF(m_hanzi);

//    m_fontColor.setNamedColor("#aa00ff");

    m_fixedWidth = m_metricsPY->width("chong");
}

ChineseCharacterObject::~ChineseCharacterObject()
{
    delete m_metricsPY;
    delete m_metricsHZ;
}

QSizeF ChineseCharacterObject::intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
    QVariantMap map = qvariant_cast<QVariantMap>(format.property(Widget::CharacterData));

    qreal t_w = m_metricsPY->width(map.firstKey());
    qreal b_w = m_metricsHZ->width(map.first().toString());

    if(Widget::m_PinYinAll.contains(map.first().toString()))
        b_w = m_fixedWidth;

    qreal t_h = m_metricsPY->height();
    qreal b_h = m_metricsHZ->height();

    QSizeF size(qMax(t_w,b_w)+2*margin,t_h+b_h+2*margin);
    return size;
}

void ChineseCharacterObject::drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
    QVariantMap map = qvariant_cast<QVariantMap>(format.property(Widget::CharacterData));

    qreal t_w = m_metricsPY->width(map.firstKey());
    qreal b_w = m_metricsHZ->width(map.first().toString());
    qreal t_h = m_metricsPY->height();
    qreal b_h = m_metricsHZ->height();

    qreal temp = b_w;
    if(Widget::m_PinYinAll.contains(map.first().toString()))
        temp = m_fixedWidth;
    qreal w = qMax(t_w,temp);

    painter->save();
//    painter->setPen(m_fontColor);
    painter->setRenderHint(QPainter::TextAntialiasing);

    painter->setFont(m_pinyin);
    painter->drawText(QRectF(rect.topLeft()+QPointF(margin+((w-t_w)/2),margin),QSizeF(t_w,t_h)),map.firstKey());

    painter->setFont(m_hanzi);
    painter->drawText(QRectF(rect.topLeft()+QPointF(margin+((w-b_w)/2),margin+t_h),QSizeF(b_w,b_h)),map.first().toString());

    painter->restore();
}
