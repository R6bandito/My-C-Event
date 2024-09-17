#include "unlock.h"

void loop()
{
    using namespace std;
    for (int i = 0; i < 30; i++)    cout << "--";
}

void display()
{
    using namespace std;
    loop();
    for (int i = 0; i < 5; i++)
    {
        if(i == 1)  cout<<"               欢迎使用职工管理系统 v1.0";
        cout << endl;
    }
    loop();
}

void delay_sec(size_t time_sec)
{
    using namespace std;
    this_thread::sleep_for(chrono::seconds(time_sec));
}

size_t UserPassword = 254788;

void password_input()
{
    size_t count = 0;
    size_t password;
    using namespace std;

    // 移动光标
    __ANSI_MOV_CURSOR(4, 9);
    cout << "请输入8位密码: ";__ANSI_CUR_SAVE();
    while (true)
    {
        while (!(cin >> password))
        {
            Cin_Error_Handle();
            delay_sec(1); // 延迟1秒
            __ANSI_CUR_RESET();
        }
        // 密码不匹配
        if (password != UserPassword)
        {
            if(count == 3)
            {
                cout<<"账号被冻结，请30秒后再试";
                delay_sec(1);  count = 0;
                Cin_Error_Handle();
                __ANSI_CUR_RESET();
                delay_sec(30);
            }
            cout << "密码错误,剩余"<<3-count++<<"次机会";
            delay_sec(1);
            Cin_Error_Handle();
            __ANSI_CUR_RESET();
        }
        else break;
    }
}
// 客户端解锁界面显示
size_t display_unlock_menu()
{
    using namespace std;
    __ANSI_CLR_TERM(); // ANSI清屏

    thread th1(display);
    th1.join();

    thread th2(password_input);
    th2.join();

    return PERMISSION_CONFIRM;
}