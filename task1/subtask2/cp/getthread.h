#ifndef GETTHREAD_H
#define GETTHREAD_H

#include <QObject>
#include <QThread>

class GetThread : public QThread
{
    Q_OBJECT

public:
    explicit GetThread(QObject *parent, int shmid);
    ~GetThread();

signals:
    void rate(int);
    void err();
    void complete();

public slots:
    void errHandle();

private:
    int shmid;
    void run();
};

#endif // GETTHREAD_H
