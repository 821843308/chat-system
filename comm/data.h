#pragma once
#include <iostream>
#include <json/json.h>

class data
{
public:
    data();
    void serialize(std::string& output);
    void unserialize(std::string& input);
    ~data();
public:
    std::string name;
    std::string school;
    std::string msg;
    std::string cmd;
};
