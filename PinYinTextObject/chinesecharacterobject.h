#ifndef CHINESECHARACTEROBJECT_H
#define CHINESECHARACTEROBJECT_H

#include <QTextObjectInterface>
#include <QFont>
#include <QFontMetricsF>


QT_BEGIN_NAMESPACE
class QTextDocument;
class QTextFormat;
class QPainter;
class QRectF;
class QSizeF;
QT_END_NAMESPACE

class ChineseCharacterObject : public QObject , public QTextObjectInterface
{
    Q_OBJECT
    Q_INTERFACES(QTextObjectInterface)
public:
    ChineseCharacterObject();

    virtual QSizeF intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format) override;
    virtual void drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc,
                             int posInDocument, const QTextFormat &format) override;

private:

    QFontMetricsF m_metricsPY;
    QFontMetricsF m_metricsHZ;

    QFont m_pinyin;
    QFont m_hanzi;

    qreal m_widthPY;
    qreal m_heightPY;
    qreal m_widthHZ;
    qreal m_heightHZ;
};

#endif // CHINESECHARACTEROBJECT_H
