#include "udp_client.h"

void print_log(std::string str)
{
    std::cout<<str<<std::endl;
}

 udp_client::udp_client(const std::string &ip,const int& port)
    :sock(-1)
{
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    
}
int udp_client::init_client()
{
    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0)
    {
       // print_log(strerror(errno));
        return -1;
    }
    return 0;
}

int udp_client::recv_msg(std::string &outdata)
{
    char buf[1024];
    memset(buf,'\0',sizeof(buf));
    struct sockaddr_in peer;
    socklen_t len = sizeof(peer);
    ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
    if(s > 0)
    {
        buf[s]=0;
        outdata = buf;
    }
    return s;
}

int udp_client::send_msg(const std::string &indata)
{
    socklen_t len = sizeof(server);
    ssize_t s = sendto(sock,indata.c_str(),indata.size(),0,(struct sockaddr*)&server,len);
    return s;
}

udp_client::~udp_client()
{
    if(sock > 0)
    {
        close(sock);
    }
}
