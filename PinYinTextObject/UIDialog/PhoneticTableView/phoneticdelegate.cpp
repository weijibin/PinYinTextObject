#include "phoneticdelegate.h"
#include <QComboBox>
#include "widget.h"

PhoneticDelegate::PhoneticDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *PhoneticDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 1)
    {
        QComboBox *comboBox = new QComboBox(parent);
        comboBox->setEditable(true);
        QString key = index.model()->data(index,Qt::UserRole).toString();
        QStringList lst = Widget::getPinYinAll().value(key);
        comboBox->addItems(lst);
        return comboBox;
    }
    else
    {
        return QStyledItemDelegate::createEditor(parent,option,index);
    }
}

void PhoneticDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column() == 1)
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        comboBox->setCurrentText(value);
    }
    else
    {
        QStyledItemDelegate::setEditorData(editor,index);
    }
}

void PhoneticDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString value = comboBox->currentText();
    model->setData(index, value, Qt::EditRole);
}

void PhoneticDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
