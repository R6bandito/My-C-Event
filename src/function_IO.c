#include <stdio.h>
#include <string.h>

void clearInputBuff()   //清空输入缓冲区
{
    char ch ;
    while((ch =getchar()) != '\n' && ch != EOF){}
}

void stringInput(char* ptr,size_t size)     //字符串的输入
{
    if(fgets(ptr,size,stdin) != NULL)
    {
        ptr[strcspn(ptr,"\n")] = '\0';  //查找到换行符的位置并将其替换为结束符
    }
}