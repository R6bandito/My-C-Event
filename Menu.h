#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "ansilib.h"
#include <mingw.thread.h>
#include <windows.h>
#include <conio.h>

#define HEADER1 "------------------------------------------------------------------------------"


//显示菜单
int show_menu();

//打印边框
void print_lace();

//打印文本
void print_text();

//输入
int user_input();

#endif //MENU_H