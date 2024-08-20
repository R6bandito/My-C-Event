#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include "Menu.h"
#include "function.h"

#define FILE_CANT_CREATE 2

int main(int argc,const char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    FILE *fp = fopen("Database.bin","ab");  //新建一个空数据库文件
    if(fp == NULL){     //检测文件是否创建成功。若失败则终止程序
        perror("Something Wrong!");
        exit(FILE_CANT_CREATE);
    }
    fclose(fp);     //关闭文件

    int press;
    while(1)
    {
        Menu_A(); //显示主菜单
        press = Do_MenuA(); //菜单操作

        switch(press)
        {
            case 1:addStudentInfo();system("cls");break;  //添加学生信息
            case 2:deleteStudentInfo();system("cls");break; //删除学生信息
            case 3:fixStudentInfo();system("cls");break; //修改学生信息
            case 4:searchStudentInfo();system("cls");break; //查询学生信息
            case 5:break;
            case 6:break;
            case 7:break;
            case 8:readStudentInfo();system("cls");break; //读取学生信息
            case 9:exit(1);   //退出系统
        }
    }
}