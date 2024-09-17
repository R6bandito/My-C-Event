#include "Menu.h"

void print_lace()
{
    using namespace std;
    system("cls");

    cout<<HEADER1<<endl;
    for(int i=0;i<11;i++)  cout<<endl;
    cout<<HEADER1<<endl;
}

void print_text()
{
    using namespace std;
    __ANSI_MOV_CURSOR(2,30);    cout<<"职工管理系统";
    __ANSI_MOV_CURSOR(4,30);    cout<<"1.添加职工信息";
    __ANSI_MOV_CURSOR(5,30);     cout<<"2.显示职工信息";
    __ANSI_MOV_CURSOR(6,30);     cout<<"3.删除职工信息";
    __ANSI_MOV_CURSOR(7,30);     cout<<"4.修改职工信息";
    __ANSI_MOV_CURSOR(8,30);     cout<<"5.查找职工信息";
    __ANSI_MOV_CURSOR(9,30);     cout<<"6.按编号排序";
    __ANSI_MOV_CURSOR(10,30);    cout<<"7.清空所有文档";
    __ANSI_MOV_CURSOR(11,30);    cout<<"0.退出程序";
    __ANSI_MOV_CURSOR(12,60);    cout<<"版本: v1.0";
    __ANSI_MOV_CURSOR(11,55);    cout<<"[";__ANSI_CUR_SAVE();cout<<" ]";
}

int user_input()
{
    int arr[1];
    int cnt = 0;
    __ANSI_CUR_GET();   //读取光标
    while(true)
    {
        char ch = _getch();
        if(ch >= '0' && ch <= '9' && cnt<1)
        {
            std::cout<<ch;
            arr[cnt++] = ch;
        }
        else if(ch == '\b' && cnt > 0)
        {
            std::cout<<"\b \b";
            arr[--cnt] = 0;
            __ANSI_CUR_ENABLE();
        }
        if(cnt == 1)    __ANSI_CUR_DISABLE();//禁用光标
        if(ch == '\r')  break;  //回车按下
    }
    __ANSI_CUR_ENABLE();    //启用光标
    return arr[0];
}

//显示菜单
int show_menu()
{
    using namespace std;
    thread th1(print_lace);
    if(th1.joinable())  th1.join();
    
    thread th2(print_text);
    if(th2.joinable())  th2.join();

    return user_input();
}