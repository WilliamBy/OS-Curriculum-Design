#include "progressor.h"
#include "ui_progressor.h"

Progressor::Progressor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Progressor)
{
    ui->setupUi(this);
}

Progressor::~Progressor()
{
    delete ui;
}

void Progressor::setTitle(QString str)
{
    ui->title->setText(str);
}

void Progressor::setProgress(int rate)
{
    ui->bar->setValue(rate);
}

int Progressor::getProgress()
{
    return ui->bar->value();
}
