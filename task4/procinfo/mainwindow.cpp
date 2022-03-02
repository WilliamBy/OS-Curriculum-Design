#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QTime>
#include <sys/sysinfo.h>
#include <string.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("System Monitor");
    timer = new QTimer(this);
    // set basic info
    QProcess p;
    QStringList flags;
    flags << "-c" << "cat /proc/sys/kernel/hostname";
    p.start("/bin/bash", flags);
    p.waitForFinished();
    p.waitForReadyRead();
    QString str = p.readLine();
    ui->hostname->setText(str.trimmed());
    p.close();
    flags.clear();
    refreshUpTime();
    flags << "-c" << "cat /proc/sys/kernel/ostype";
    p.start("/bin/bash", flags);
    p.waitForFinished();
    p.waitForReadyRead();
    str = p.readLine();
    ui->kernel->setText(str.trimmed());
    p.close();
    flags.clear();
    flags << "-c" << "cat /proc/sys/kernel/osrelease";
    p.start("/bin/bash", flags);
    p.waitForFinished();
    p.waitForReadyRead();
    str = p.readLine();
    ui->kernel->setText(ui->kernel->text() + " " + str);
    p.close();
    flags.clear();
    flags << "-c" << "cat /proc/cpuinfo | grep 'model name'";
    p.start("/bin/bash", flags);
    p.waitForFinished();
    p.waitForReadyRead();
    str = p.readLine();
    int ind = str.indexOf(':');
    str = str.mid(ind + 2, str.length() - ind - 3);
    ui->cpuinfo->setText(str);

    QObject:;connect(timer, &QTimer::timeout, this, &MainWindow::refreshUpTime);
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshUpTime()
{
    struct sysinfo info;
    sysinfo(&info);
    struct tm *ptm=nullptr;
    ptm=gmtime(&info.uptime);
    char time_buf[30];
    sprintf(time_buf,"%02d:%02d:%02d",ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
    ui->uptime1->setText(time_buf);

    time_t cur_time=0;
    time_t boot_time=0;
    time(&cur_time);
    boot_time=cur_time-info.uptime;
    ptm=localtime(&boot_time);
    char boot_buf[30];
    sprintf(boot_buf,"%d.%d.%d %02d:%02d:%02d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,
            ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
    ui->uptime2->setText(boot_buf);
}
