#ifndef PHONETICDELEGATE_H
#define PHONETICDELEGATE_H
#include <QStyledItemDelegate>

class PhoneticDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    PhoneticDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};



#endif // PHONETICDELEGATE_H
