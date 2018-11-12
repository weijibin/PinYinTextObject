#ifndef PHONETICDIALOG_H
#define PHONETICDIALOG_H
#include <QDialog>

class QStackedLayout;
class PhoneticTitle;
class PhoneticEdit;
class PhoneticPreview;

class PhoneticDialog : public QDialog
{
    Q_OBJECT
public:
    PhoneticDialog(QWidget *parent = nullptr);

    void initUI();
private:
    void initTitle();
    void initBody();

private:
    PhoneticPreview * m_preview = nullptr;
    PhoneticEdit * m_edit = nullptr;
    PhoneticTitle * m_title = nullptr;
    QStackedLayout * m_stackLayout = nullptr;
};

#endif // PHONETICDIALOG_H
