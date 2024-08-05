#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"
#include "function.h"

Link phead;

int main()
{
    short i;
    //short I;
    phead = NewList();
Menu1:    Menu_A();
back:    scanf("%hd",&i);
    if(i == -1){
        exit(1);
    }

// 判断键盘输入
    switch(i){
        case 1:Distinguish(1);goto Menu1;
        case 2:Distinguish(2);goto Menu1;
        case 3:Distinguish(3);goto Menu1;
        case 4:Distinguish(4);goto Menu1;
        default:printf("无匹配项，请重新输入\n");goto back;
    }
}