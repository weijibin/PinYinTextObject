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
    if(role == Qt::UserRole)
    {
        int row = index.row();
        int col = index.column();
        QString info = "";
        int pos = m_phoneticIndex.at(row);
        if(col == 1)
        {
            info = m_phoneticData.at(pos).second;
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
    if(index.column() ==1)
        return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
    else
        return QAbstractTableModel::flags(index);
}

QVariant PhoneticModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        QVariant var;
        if(section == 0)
        {
            var = "汉字";
        }
        else
        {
            var = "拼音";
        }
        return var;
    }
    else
    {
            return QAbstractTableModel::headerData(section, orientation, role);
    }
}

void PhoneticModel::setPhoneticData(const QList<int> &indexs, const QList<QPair<QString, QString>> &data)
{
    this->beginResetModel();
    m_phoneticIndex = indexs;
    m_phoneticData = data;
    this->endResetModel();
}

const QList<QPair<QString,QString>>& PhoneticModel::getPhoneticData()
{
    return m_phoneticData;
}
