#include "error.h"

void Cin_Error_Handle()
{
    using namespace std;
    // 清除错误标记
    cin.clear();
    // 忽略掉直到换行符的字符
    cin.ignore(1024, '\n');
    cout << "Wrong!!";
}