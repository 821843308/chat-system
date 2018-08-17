#pragma once

#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#define MAX 1024

class chatWindow
{
public:
    chatWindow();
    void init();
    WINDOW* creat_win(const int &h,const int &w,const int &y,const int &x);
    void win_refresh(WINDOW *_win);
    void put_str_to_header(std::string &_str);
    void put_str_to_win(WINDOW *_win,int y,int x,std::string &_str);

    void get_str_from_win(WINDOW *_win,std::string &_str);
    void clear_win_line(WINDOW *_win,int begin,int num);

    ~chatWindow();

    void draw_header();
    void draw_output();
    void draw_input();
    void draw_flist();

public:
    WINDOW *header;
    WINDOW *output;
    WINDOW *input;
    WINDOW *flist;
};
