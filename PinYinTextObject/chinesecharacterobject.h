#ifndef CHINESECHARACTEROBJECT_H
#define CHINESECHARACTEROBJECT_H

#include <QTextObjectInterface>

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
};

#endif // CHINESECHARACTEROBJECT_H
