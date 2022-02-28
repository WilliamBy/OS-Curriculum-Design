#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>

namespace Ui {
class ConfirmDialog;
}

class ConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmDialog(QWidget *parent = nullptr);
    ~ConfirmDialog();
    void setSrc(QString srcPath);
    void setDes(QString desPath);

signals:
    void accept();

private:
    Ui::ConfirmDialog *ui;
};

#endif // CONFIRMDIALOG_H
