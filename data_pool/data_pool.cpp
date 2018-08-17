#include "data_pool.h"

data_pool::data_pool()
    :msgpool(CAPACITY),start(0),end(0)
{
    sem_init(&put_sem,0,CAPACITY);
    sem_init(&get_sem,0,0);
}

void data_pool::put_msg(const std::string &msg)
{
    sem_wait(&put_sem);
    msgpool[end++] = msg;
    end %= CAPACITY;
    sem_post(&get_sem);
}

void data_pool::get_msg(std::string &msg)
{
    sem_wait(&get_sem);
    msg = msgpool[start++] ;
    start %= CAPACITY;
    sem_post(&put_sem);
}

data_pool::~data_pool()
{
    sem_destroy(&get_sem);
    sem_destroy(&put_sem);
}

