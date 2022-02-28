#ifndef PROGRESSER_H
#define PROGRESSER_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class Progressor;
}

class Progressor : public QDialog
{
    Q_OBJECT

public:
    explicit Progressor(QWidget *parent = nullptr);
    ~Progressor();
    void setTitle(QString);
    void setProgress(int);

private:
    Ui::Progressor *ui;
};

#endif // PROGRESSER_H
