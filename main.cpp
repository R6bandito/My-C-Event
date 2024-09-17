#include <iostream>
#include "unlock.h"
#include <windows.h>
#include "Menu.h"

void setConsoleOutputType()
{
    SetConsoleOutputCP(CP_UTF8);
}

int main(int argc,const char* argv[])
{
    setConsoleOutputType();
    int parameter;
    //显示客户端解锁界面
    if(parameter = display_unlock_menu())
    {
        while(true)
        {
            parameter = show_menu();
            switch(parameter)
            {
                case '0':exit(EXIT_SUCCESS);
            }
        }
    }
}