#include "data_pool.h"

data_pool::data_pool()
    :msgpool(CAPACITY),start(0),end(0)
{
    int sem_init(&put_msg,0,CAPACITY);
    int sem_init(&get_msg,0,0);
}

void data_pool::put_msg(const std::string& msg)
{
    sem_wait(&put_msg);
    msgpool[end++] = msg;
    end %= CAPACITY;
    sem_post(&get_msg);
}

void data_pool::get_msg(const std::string& msg)
{
    sem_wait(&get_msg);
    msgpool[start++] = msg;
    start %= CAPACITY;
    sem_post(&put_msg);
}

data_pool::~data_pool()
{}
