#ifndef _ERROR
#define _ERROR

//输入错误处理
void error_input_cope();

#endif  //_ERROR

#ifndef _FUNCTION
#define _FUNCTION

//由用户进行的菜单输入
char input_data();

//回到光标位置清除输入
void clearInput();

#endif  //_FUNCTION

#ifndef _DELAY
#define _DELAY
#if defined(_WIN32) || defined(_WIN64)
//Windows系统下的延时函数
#include <windows.h>

void delayMs(unsigned int iTime);

#elif defined(_linux_) || defined(_unix_) || defined(_APPLE_)
//Linux等系统下的延时函数
#include <unistd.h>

void delayMs(unsigned int iTime);
#else
#error "不支持的操作系统"
#endif

#endif //_DELAY



#if defined (_WIN32) || defined (_WIN64)
#include <conio.h>

//启用原始模式
void enableRawMode();

//Windows下读取字符
char getChar();

#elif defined(_linux_) || defined(_unix_) || defined(_APPLE_)
#include <termios.h>
#include <unistd.h>
struct termios orig_termios;

void disableRawMode();

void enableRawMode();

//linux等系统下获取字符
char getChar();
#else
#error "不支持此操作系统"
#endif
