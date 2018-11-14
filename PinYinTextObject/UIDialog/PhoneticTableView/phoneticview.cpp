#include "phoneticview.h"
#include "phoneticmodel.h"

PhoneticView::PhoneticView(QWidget *parent) : QTableView(parent)
{
    m_model = new PhoneticModel(this);
}

void PhoneticView::initData(const QList<int> indexs, const QList<QPair<QString, QString> > datas)
{
    if(m_model != nullptr)
    {
        m_model->setPhoneticData(indexs,datas);
        this->setModel(m_model);
    }
}

const QList<QPair<QString,QString>>& PhoneticView::getPhoneticData()
{
    if(m_model != nullptr)
    {
        return m_model->getPhoneticData();
    }
}
