#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QObject::connect(ui->button, &QPushButton::clicked, this, &Dialog::close);
}

Dialog::~Dialog()
{
    delete ui;
    QString a;
}

void Dialog::setText(const char *text)
{
    ui->msg->setText(text);
}
