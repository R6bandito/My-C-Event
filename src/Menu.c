#include <stdio.h>
#include "Menu.h"
#include "function_IO.h"

void Menu_A() // 主菜单
{
    printf("欢迎使用学生成绩管理系统\n");
    printf(" 1.添加学生信息\n");
    printf(" 2.删除学生信息\n");
    printf(" 3.修改学生信息\n");
    printf(" 4.查询学生信息\n");
    printf(" 5.总成绩和平均成绩\n");
    printf(" 6.按成绩排序学生信息\n");
    printf(" 7.保存到文件\n");
    printf(" 8.从文件中读取学生信息\n");
    printf(" 9.退出系统\n");
}

int Do_MenuA() // 主菜单操作
{
    int i;
    while (1)
    {
        printf("请输入功能键继续\n");
        if (scanf("%d", &i) != 1)
        {
            printf("非数值型输入，请重试\n");
            clearInputBuff();   //清空输入缓冲区
            continue;
        }
        else if(i<1 || i>9)
        {
            printf("错误输入，请重试\n");
            continue;
        }
        break;
    }
    return i;
}

