#include "chatWindow.h"

chatWindow::chatWindow()
    :header(NULL),output(NULL),input(NULL),flist(NULL)
{}
void chatWindow::init()
{
    initscr();
    curs_set(0);
}
WINDOW* chatWindow::creat_win(const int &h,const int &w,const int &y,const int &x)
{
    WINDOW* win = newwin(h,w,y,x);
    return win;
}

void chatWindow::win_refresh(WINDOW *_win)
{
    box(_win,0,0);
    wrefresh(_win);
}

void chatWindow::clear_win_line(WINDOW *_win,int begin,int num)
{
    while(num--)
    {
        wmove(_win,begin++,0);
        wclrtoeol(_win);//将当前位置到窗口低端的所有字符清除
    }
}

void chatWindow::put_str_to_header(std::string &_str)
{
    int step = 5;
    int y,x;
    getmaxyx(header,y,x);
    while(1)
    {
        mvwaddstr(header,y/2,step++,_str.c_str());
        wrefresh(header);
        step %=(COLS-5-_str.size());
        if(step == 0)
            step = 5;
        sleep(1);

        wmove(header,y/2,1);
        wclrtoeol(header);//将当前位置到这一行末所以字符全清除
        /* wclrtobot(this->header);//将当前位置到窗口低端的所有字符清除 */
        box(header,0,0);
    }
}

void chatWindow::put_str_to_win(WINDOW *_win,int y,int x,std::string &_str)
{
    mvwaddstr(_win,y,x,_str.c_str());
    wrefresh(_win);
}

void chatWindow::get_str_from_win(WINDOW *_win,std::string&_out)
{
    char buf[MAX];
    memset(buf,'\0',sizeof(buf));
    wgetnstr(_win,buf,sizeof(buf));
    _out = buf;

}

chatWindow::~chatWindow()
{
    delwin(this->header);
    endwin();
}

void chatWindow::draw_header()
{
    int h = LINES/10;
    int w = COLS;
    int y = 0;
    int x = 0;
    this->header = creat_win(h,w,y,x);
    this->win_refresh(header);
}

void chatWindow::draw_output()
{
    int h = 3*LINES/5;
    int w = 3*COLS/4;
    int y = LINES/10;
    int x = 0;
    this->output = creat_win(h,w,y,x);
    this->win_refresh(output);

}

void chatWindow::draw_input()
{
    int h = 3*LINES/10;
    int w = 3*COLS/4;
    int y = 7*LINES/10;
    int x = 0;
    this->input = creat_win(h,w,y,x);
    this->win_refresh(this->input);
}

void chatWindow::draw_flist()
{
    int h = 9*LINES/10;
    int w = COLS/4;
    int y = LINES/10;
    int x = 3*COLS/4;
    this->flist = creat_win(h,w,y,x);
    this->win_refresh(this->flist);
}

/* int main() */
/* { */
/*     chatWindow _win; */
/*     _win.init(); */

/*     _win.draw_header(); */
/*     /1* sleep(1); *1/ */
/*     _win.draw_output(); */
/*     /1* sleep(1); *1/ */
/*     _win.draw_input(); */
/*     /1* sleep(1); *1/ */
/*     _win.draw_flist(); */
/*     /1* sleep(1); *1/ */

/*     std::string str; */
/*     str = "Welcome Chat System"; */

/*     _win.put_str_to_header(str); */ 
/*     /1* sleep(1); *1/ */

/*     return 0; */
/* } */
