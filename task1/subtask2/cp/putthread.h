#ifndef PUTTHREAD_H
#define PUTTHREAD_H

#include <QObject>
#include <QThread>

class PutThread : public QThread
{
    Q_OBJECT

public:
    explicit PutThread(QObject *parent, int shmid);
    ~PutThread();

signals:
    void rate(int);
    void err();

public slots:
    void errHandle();

private:
    int shmid;
    void run();
};

#endif // PUTTHREAD_H
