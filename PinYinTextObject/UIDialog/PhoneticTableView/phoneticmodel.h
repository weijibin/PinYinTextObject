#ifndef PHONETICMODEL_H
#define PHONETICMODEL_H
#include <QAbstractTableModel>

class PhoneticModel :public QAbstractTableModel
{
    Q_OBJECT
public:
    PhoneticModel(QObject * parent = nullptr);
    void setPhoneticData(const QList<int> &indexs, const QList<QPair<QString,QString>> &data);
    const QList<QPair<QString,QString>>& getPhoneticData();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex & index) const override ;
private:
    QList<int> m_phoneticIndex;
    QList<QPair<QString,QString>> m_phoneticData;
};

#endif // PHONETICMODEL_H
