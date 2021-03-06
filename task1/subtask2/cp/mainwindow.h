#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QApplication>
#include <QThread>
#include "confirmdialog.h"
#include "dialog.h"
#include "progressor.h"
#include "getthread.h"
#include "putthread.h"
#include "copythread.h"
#include "pv.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ConfirmDialog *cDialog;
    Dialog *popup;
    Dialog *debug;
    Progressor *getProg;
    Progressor *copyProg;
    Progressor *putProg;
    GetThread *getThread;
    CopyThread *copyThread;
    PutThread *putThread;
    int cp(const char*, const char*);

public slots:
    void recConfirm();
    void copyCompleted();

private:
    Ui::MainWindow *ui;
    int shmid = -1;
    shm_struct *shm_handle = nullptr;
};

#endif // MAINWINDOW_H
