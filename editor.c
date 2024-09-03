#include <stdio.h>
#include "Menu.h"
#include "editor.h"
#include <stdbool.h>

void error_input_cope()
{   
    printf("错误输入，请重试");
    //延时1秒
    delayMs(1000);
    //清空该行
    printf("\033[2K");
}

void clearInput()/*Bug*/
{
    //回到光标位置
    accessMouse();
    //输出一个退格
    printf("\b \b");
}

char input_data()
{
    //定义一个input字符数组用于存储输入的数据
    char input[2];
    //count变量用于计数
    int count = 0;
    while(true)
    {
        char ch = getChar();
        if((ch>'0' && ch<'9') && count<1)
        {
            printf("%c",ch);   
            input[count++] = ch;
        }
        else if(ch == '\b' && count > 0)
        {
            //当按下退格时，删除输入的数据
            printf("\b \b");
            input[--count] = 0;
        }

        if(count == 1)
        {
            //输入一个字符后，禁用光标
            disable_cursor();
        }

        if(ch == '\r')
        {
            //当回车被按下后,判断功能键是否正确输入
            if(input[0] != '1' || input[0] != '2')  /*Bug*/
            {
                //光标下移两行并移动到首行
                printf("\033[2B\033[G");
                error_input_cope();
                clearInput();
                continue;
            }
            break;
        }
    }
    //启用光标
    enable_cursor();

    return input[0];
}



/*以下代码为跨平台延时函数实现
*/
#if defined(_WIN32) || defined(_WIN64)
void delayMs(unsigned int iTime)
{
    Sleep(iTime);
}
#elif defined(_linux_) || defined(_unix_) || defined(_APPLE_)
void delayMs(unsigned int iTime)
{
    usleep(iTime * 1000);
}
#endif

/*以下代码为跨平台动态输入代码的实现
*/
#if defined(_WIN32) || defined(_WIN64)
void enableRawMode(){
    //Windows系统下无需进行此操作
}

char getChar(){
    return _getch();
}


#elif defined(_linux_) || defined(_unix_) || defined(_APPLE_)

void enableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &orig_termios);  // 获取当前终端设置
    term = orig_termios;

    term.c_lflag &= ~(ICANON | ECHO);  // 禁用缓冲和回显
    tcsetattr(STDIN_FILENO, TCSANOW, &term);  // 应用新设置

    atexit(disableRawMode);  // 程序结束时恢复终端设置
}

char getChar() {
    return getchar();  // Unix/Linux 下读取字符
}
#else
#error "操作系统有误"
#endif