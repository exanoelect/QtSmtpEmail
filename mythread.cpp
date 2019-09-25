#include "mythread.h"

class mythreadData : public QSharedData
{
public:

};

mythread::mythread(QObject *parent) : QObject(parent), data(new mythreadData)
{

}

mythread::mythread(const mythread &rhs) : data(rhs.data)
{

}

mythread &mythread::operator=(const mythread &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

mythread::~mythread()
{

}
