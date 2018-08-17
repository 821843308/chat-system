#include "udp_server.h"
#include <pthread.h>
#include <stdlib.h>
#include "../data_pool/data_pool.h"
#include "../comm/data.h"

void usage(char* proc)
{
    std::cout<<"usage:\n\t"<<proc<<"[server_port]\r\n"<<std::endl;
}
void *recv_data(void*arg)
{
    udp_server* server = (udp_server*)arg;
    std::string outmsg;
    while(1)
    {
        server->_recv_msg(outmsg);
    }
}

void* send_data(void* arg)
{
    udp_server* server = (udp_server*)arg;
    while(1)
    {
        server->send_msg();
    }
}

int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        usage(argv[0]);
        exit(1);
    }
    in_port_t port = atoi(argv[1]);
    udp_server server(port);
    server.init_server();

    pthread_t thread1,thread2;
    pthread_create(&thread1,NULL,recv_data,(void *)&server);
    pthread_create(&thread2,NULL,send_data,(void *)&server);
    

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    
    return 0;
}
