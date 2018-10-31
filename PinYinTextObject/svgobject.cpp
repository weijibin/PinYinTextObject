#include <QPainter>
#include "svgobject.h"
#include "widget.h"

SvgObject::SvgObject()
{

}

QSizeF SvgObject::intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
    QImage bufferedImage = qvariant_cast<QImage>(format.property(Widget::SvgData));
    QSize size = bufferedImage.size();

    if (size.height() > 25)
        size *= 25.0 / (double) size.height();

    return QSizeF(size);
}

void SvgObject::drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
    QImage bufferedImage = qvariant_cast<QImage>(format.property(Widget::SvgData));
    painter->drawImage(rect, bufferedImage);
}
