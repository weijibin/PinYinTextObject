#ifndef PHONETICVIEW_H
#define PHONETICVIEW_H

#include <QTableView>

class PhoneticModel;
class PhoneticDelegate;

class PhoneticView : public QTableView
{
    Q_OBJECT
public:
    PhoneticView(QWidget *parent = nullptr);

    void initData(const QList<int> indexs, const QList<QPair<QString,QString>> datas);

    const QList<QPair<QString,QString>>& getPhoneticData();

signals:
    void sigDataChanged();

private:
    PhoneticModel * m_model = nullptr;
    PhoneticDelegate * m_delegate = nullptr;
};

#endif // PHONETICVIEW_H
