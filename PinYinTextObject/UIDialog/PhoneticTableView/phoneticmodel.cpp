#include "phoneticmodel.h"

PhoneticModel::PhoneticModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int PhoneticModel::rowCount(const QModelIndex &parent) const
{
    return m_phoneticIndex.count();
}

int PhoneticModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant PhoneticModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        int row = index.row();
        int col = index.column();
        QString info = "";
        int pos = m_phoneticIndex.at(row);
        if(col == 0)
        {
             info = m_phoneticData.at(pos).second;
        }
        else if(col == 1)
        {
            info = m_phoneticData.at(pos).first;
        }
        return info;
    }
    return QVariant();
}

bool PhoneticModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
//    return QAbstractTableModel::setData(index,value,role);
    if (role == Qt::EditRole)
    {
        int row = index.row();
        int col = index.column();
        if(col == 1)
        {
            QString info = value.toString();
            int pos = m_phoneticIndex.at(row);
            m_phoneticData[pos].first = info;
        }
    }
    return true;
}

Qt::ItemFlags PhoneticModel::flags(const QModelIndex &index) const
{
     return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

void PhoneticModel::setPhoneticData(const QList<int> &indexs, const QList<QPair<QString, QString>> &data)
{
    m_phoneticIndex = indexs;
    m_phoneticData = data;
}

const QList<QPair<QString,QString>>& PhoneticModel::getPhoneticData()
{
    return m_phoneticData;
}
