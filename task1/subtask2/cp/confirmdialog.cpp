#include "confirmdialog.h"
#include "ui_confirmdialog.h"

ConfirmDialog::ConfirmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ConfirmDialog::accept);
}

ConfirmDialog::~ConfirmDialog()
{
    delete ui;
}

void ConfirmDialog::setDes(QString desPath)
{
    ui->desPath->setText(desPath);
}

void ConfirmDialog::setSrc(QString srcPath)
{
    ui->srcPath->setText(srcPath);
}
