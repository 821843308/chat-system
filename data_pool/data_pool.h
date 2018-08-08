#pragma once
#include <iostream>
#include <string.h>
#include <semaphore.h>
#include <vector>

#define CAPACITY 1024;

class data_pool
{
public:
    data_pool();
    void put_msg();
    void get_msg();
    ~data_pool();
private:
    sem_t put_msg;
    sem_t get_msg;
    std::vector<std::string> msgpool;
    int start;
    int end;
};
