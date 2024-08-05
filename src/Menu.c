#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Menu.h"

void Menu_A(){  //主菜单函数
    SetConsoleOutputCP(CP_UTF8);
    unsigned short i,k;
    for(k=1;k<14;k++){      //利用循环画出边框
        for(i=1;i<61;i++){
            if(k == 1 || k == 2 || k == 13 || k == 12){
            printf("%c",42);
          }
        }

    //显示菜单选项
        if(k == 4)
            printf("                    1.查询学生信息          ");
        if(k == 6)
            printf("                    2.添加学生信息          ");
        if(k == 8)
            printf("                    3.删除学生信息          ");
        if(k == 10)
            printf("                    4.显示所有信息          ");
        printf("\n");
    }
    printf("请进行输入(按-1返回)\n");
}