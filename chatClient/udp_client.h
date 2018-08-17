
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class udp_client
{
public:
    udp_client(const std::string &ip,const int& port);
    int init_client();
    int recv_msg(std::string &outdata);
    int send_msg(const std::string &indata);
    ~udp_client();
        
private:
    int sock;
    struct sockaddr_in server;

};
