#include <stdio.h>
#include "editor.h"
#include "Menu.h"

void saveMouse()
{
    //用于保存当前的光标位置
    printf("\033[s");
}

void accessMouse()
{
    //读取保存的光标位置
    printf("\033[u");
}

void enable_cursor()
{
    //启用终端光标
    printf("\033[?25l");
}

void disable_cursor()
{
    //禁用终端光标
    printf("\033[?25h");
}

char printMenu_A()  //打印菜单
{
    //清屏
    printf("\033[2J\033[H");

    printf("-------------------------------------------------------------------------------------\n");
     printf("                                                                                      \n");
    printf("                                    1.打开文件                                        \n");
    printf("                                                                                      \n");
    printf("                                    2.新建文件                                        \n");
    printf("                                                                   [ "); //将光标位置保存到此
    saveMouse();
    printf("  ]\n");
    printf("-------------------------------------------------------------------------------------\n");

    char cInput;
    accessMouse();  //将光标读取到指定输入位置
    cInput = input_data();   //用户的菜单输入
    return cInput;
}




