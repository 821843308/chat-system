#include "udp_client.h"
#include "../chatWindow/chatWindow.h"
#include "../comm/data.h"
#include <signal.h>


udp_client *jsclient;
std::string name;
std::string school;
std::vector<std::string> flist;
pthread_t header,output_flist,input;

void* run_header(void* arg)
{
    chatWindow* window = (chatWindow*)arg;
    std::string strheader = "Welcome to chat system";
    window->draw_header();
    window->put_str_to_header(strheader);
}
static void adduser(std::string &usr)
{
    std::vector<std::string>::iterator it = flist.begin();
    for(;it != flist.end();it++)
    {
        if(*it == usr)
            return;
    }
    flist.push_back(usr);
}
static void deleteuser(std::string &usr)
{
    std::vector<std::string>::iterator it = flist.begin();
    for(;it != flist.end();it++)
    {
        if(*it == usr)
        {
            flist.erase(it);
            break;
        }
    }
    return;
}
void* run_output_flist(void* arg)
{
    chatWindow* window = (chatWindow*)arg;
    window->draw_output();
    window->draw_flist();
    
    std::string JSonstring;
    data d;
    int line = 1;
    int x;
    int y;


    std::string str;
    std::string fliststring;
    while(1)
    {
        jsclient->recv_msg(JSonstring); 
        /* std::cout<<JSonstring<<std::endl; */
        d.unserialize(JSonstring);
        str = d.name;
        str+="-";
        str+=d.school;

        fliststring = str;

        str+="#";
        str+=d.msg;
        
        getmaxyx(window->output,y,x);
        if(d.cmd != "Quit")
        {
            if(line > y -2)
            {
                window->clear_win_line(window->output,1,y-1);
                window->draw_output();
                line = 1;
            }
            window->put_str_to_win(window->output,line++,1,str);
            adduser(fliststring);
            window->win_refresh(window->output);

        }
        else
        {
            deleteuser(fliststring);
        }


        getmaxyx(window->flist,y,x);
        window->clear_win_line(window->flist,1,y-1);
        window->draw_flist();
        int size = flist.size();
        for(int i = 0;i<size;i++)
        {
            window->put_str_to_win(window->flist,i+1,1,flist[i]);
        }
        
        window->win_refresh(window->flist);

    }

}

void* run_input(void* arg)
{
    chatWindow* window = (chatWindow*)arg;
    window->draw_input();
    
    std::string tips;
    tips = "Please Enter# ";
    window->put_str_to_win(window->input,1,1,tips);
    window->win_refresh(window->input);
    
    data d;
    std::string msg;
    std::string jsonstring;

    while(1)
    {
        window->get_str_from_win(window->input,msg);
        /* window->clear_win_line(window->input,1,1); */
        window->draw_input();
        window->put_str_to_win(window->input,1,1,tips);
        window->win_refresh(window->input);

        d.name = name;
        d.school = school;
        d.msg = msg;
        d.cmd = "";

        if(!msg.empty())
        {
            d.serialize(jsonstring);
            jsclient->send_msg(jsonstring); 
        }
        
    }
    

}
void usage(const char* proc)
{
    std::cout<<"usage:\n\t"<<proc<<"[server_ip]"<<"[server_port]\r\n"<<std::endl;
}

void sendQuit(int sig)
{
    std::string sendQuitString;
    data d;
    d.name = name;
    d.school = school;
    d.msg = "";
    d.cmd = "Quit";

    d.serialize(sendQuitString);
    jsclient->send_msg(sendQuitString);

    pthread_cancel(header);
    pthread_cancel(output_flist);
    pthread_cancel(input);
}
int main(int argc,char*argv[])
{
    if(argc != 3)
    {
        usage(argv[0]);
        return 1;
    }
    std::cout<<"Please Enter name# ";
    std::cin >> name;
    std::cout<<"Please Enter school# ";
    std::cin >> school;

    udp_client client(argv[1],atoi(argv[2]));
    client.init_client();

    jsclient = &client;

    chatWindow window;
    window.init();
    std::string outdata;
    std::string indata;

    signal(SIGINT,sendQuit);

    /* pthread_t header,output_flist,input; */

    pthread_create(&header,NULL,run_header,(void*)&window);
    pthread_create(&output_flist,NULL,run_output_flist,(void*)&window);

    pthread_create(&input,NULL,run_input,(void*)&window);

    pthread_join(header,NULL);
    pthread_join(output_flist,NULL);
            
    pthread_join(input,NULL);

    
    return 0;
}
