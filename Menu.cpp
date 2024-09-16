#include <iostream>
#include "unlock.h"
#include <windows.h>

int main(int argc,const char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    //显示客户端解锁界面
    display_unlock_menu();

    return 0;
}