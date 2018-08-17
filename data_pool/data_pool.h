#pragma once
#include <iostream>
#include <string.h>
#include <semaphore.h>
#include <vector>

#define CAPACITY 1024

class data_pool
{
public:
    data_pool();
    void put_msg(const std::string &msg);
    void get_msg(std::string &msg);
    ~data_pool();
private:
    sem_t put_sem;
    sem_t get_sem;
    std::vector<std::string> msgpool;
    int start;
    int end;
};
