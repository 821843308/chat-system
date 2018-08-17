#include "udp_server.h"
#include <stdlib.h>
#include <stdio.h>

udp_server::udp_server(unsigned short _port)
    :sock(-1),port(_port)
{}

void udp_server::add_onlie_user(struct sockaddr_in & client)
{
    std::string addr = inet_ntoa(client.sin_addr);
    char port[10]={0};
    sprintf(port,"%d",client.sin_port);
    addr+=port;
    online_user.insert(std::pair<std::string,struct sockaddr_in>(addr,client));
}
void print_log(const std::string _log)
{
    std::cerr<<_log<<std::endl;
}

int udp_server::init_server()
{
    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0)
    {
        print_log(strerror(errno));
        exit(1);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(sock,(struct sockaddr*)&server,sizeof(server)) < 0)
    {
        print_log(strerror(errno));
        exit(1);
    }
    return 0;
}
int udp_server::_recv_msg(std::string & out_msg)
{
    char buf[MAX_MSG_SIZE];
    memset(buf,'\0',sizeof(buf));
    struct sockaddr_in client;
    socklen_t client_len = sizeof(client);
    ssize_t size = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&client_len);
    if(size > 0)
    {
        buf[size] = 0;
        out_msg = buf;
        print_log(out_msg);
        pool.put_msg(out_msg);
        add_onlie_user(client);
    }
    return size;
}

int udp_server::recv_msg()
{
    std:: string out_msg;
    int ret = _recv_msg(out_msg);
    if(ret > 0)
    {
        print_log(out_msg);
        pool.put_msg(out_msg);
    }
    return ret;
}
int udp_server::_send_msg(const std::string&msg,const struct sockaddr_in &client,socklen_t len)
{

    ssize_t size = sendto(sock,msg.c_str(),msg.size(),0,(struct sockaddr*)&client,len);    
    if(size < 0)
    {
        print_log(strerror(errno));
        exit(1);
    }
    else
    {
        if(size == 0)
            std::cout<<"size = 0"<<std::endl;
        else
            std::cout<<"send down"<<std::endl;
        print_log(msg);
    }

    return 0;
}
int udp_server::send_msg()
{
    std::string msg;
    pool.get_msg(msg);
    std::cout<<"get_msg = "<<msg<<std::endl;
    std::map<std::string,struct sockaddr_in>::iterator it = online_user.begin();
    for(;it!= online_user.end();it++)
    {
        _send_msg(msg,it->second,sizeof(it->second));
    }
    return 0;
}

udp_server::~udp_server()
{
    if(sock != -1)
    {
        close(sock);
    }
}
