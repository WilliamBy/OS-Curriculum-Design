#ifndef COPYTHREAD_H
#define COPYTHREAD_H

#include <QObject>
#include <QThread>

class CopyThread : public QThread
{
    Q_OBJECT

public:
    explicit CopyThread(QObject *parent, int shmid);
    ~CopyThread();

signals:
    void rate(int);
    void err();

public slots:
    void errhandle();

private:
    int shmid;
    void run();
};

#endif // COPYTHREAD_H
