#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QMainWindow>
#include <QObject>
#include <QSharedDataPointer>
#include <QWidget>
#include <QThread>
#include <qthread.h>
#include <qthreadpool.h>

class mythreadData;

class mythread : public QThread
{
    Q_OBJECT
public:
    explicit mythread(QObject *parent = nullptr);
    mythread(const mythread &);
    mythread &operator=(const mythread &);
    ~mythread();

signals:

public slots:

private:
    QSharedDataPointer<mythreadData> data;
};

#endif // MYTHREAD_H
