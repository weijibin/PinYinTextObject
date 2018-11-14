#include "phoneticview.h"
#include "phoneticmodel.h"
#include "phoneticdelegate.h"
#include <QHeaderView>

PhoneticView::PhoneticView(QWidget *parent) : QTableView(parent)
{
    this->verticalHeader()->hide();
    m_model = new PhoneticModel(this);
    m_delegate = new PhoneticDelegate(this);

    this->setModel(m_model);
    this->setItemDelegateForColumn(1,m_delegate);

    setColumnWidth(0,250);
    setColumnWidth(1,250);
}

void PhoneticView::initData(const QList<int> indexs, const QList<QPair<QString, QString> > datas)
{
    if(m_model != nullptr)
    {
        m_model->setPhoneticData(indexs,datas);
    }
}

const QList<QPair<QString,QString>>& PhoneticView::getPhoneticData()
{
    if(m_model != nullptr)
    {
        return m_model->getPhoneticData();
    }
}
