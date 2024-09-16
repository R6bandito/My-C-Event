#include "unlock.h"

void loop()
{
    using namespace std;
    for (int i = 0; i < 30; i++)
    {
        cout << "--";
    }
}

void display()
{
    using namespace std;
    loop();
    for (int i = 0; i < 4; i++)
    {
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
    size_t password;
    using namespace std;
    // 移动光标
    __ANSI_MOV_CURSOR(3, 9);
    cout << "请输入8位密码: ";
    __ANSI_CUR_SAVE();
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
            cout << "密码错误";
            delay_sec(1);
            Cin_Error_Handle();
            __ANSI_CUR_RESET();
        }
        else break;
    }
}
// 客户端解锁界面显示
void display_unlock_menu()
{
    using namespace std;
    __ANSI_CLR_TERM(); // ANSI清屏

    thread th1(display);
    th1.join();

    thread th2(password_input);
    th2.join();
}