#pragma once
#include <iostream>
#include "../data_pool/data_pool.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <map> 
#include <unistd.h>
#include <stdlib.h>

#define MAX_MSG_SIZE 512

class udp_server
{
public:
    udp_server(unsigned short _port);
    int init_server();
    int recv_msg();
    int _recv_msg(std::string & out_msg);
    int send_msg();
    int _send_msg(const std::string&msg,const struct sockaddr_in &client,socklen_t len);

    void add_onlie_user(struct sockaddr_in & client);
    ~udp_server();

private:
    int sock;
    unsigned short port;
    data_pool pool;
    std::map<std::string,struct sockaddr_in> online_user;
};
