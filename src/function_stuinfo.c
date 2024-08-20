#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"
#include <string.h>
#include "function_IO.h"
#include "function.h"
#include <windows.h>
#include <process.h>

#define FILE_CANT_OPEN 3

void Delay_ms(unsigned int time) // 延时函数
{
    Sleep(time);
}

void addStudentInfo() // 新增学生信息
{
    // 临时存储学生信息
    Student st;
    char _name[20];
    int _id;
    int maths, english, chinese;

    FILE *fp = fopen("Database.bin", "ab");
    if (fp == NULL)
    {
        perror("Oops!Cant open the file\n");
        exit(FILE_CANT_OPEN);
    }

    while (1)
    {
        while (1)
        {
            clearInputBuff();
            printf("请输入学生姓名(按E退出)\n");
            stringInput(_name, sizeof(_name));                              // 输入学生姓名
            if ((_name[0] == 'E' || _name[0] == 'e') && strlen(_name) == 1) // 判断用户输入是否为E.strlen用于计算字符串有效长度,确保用户输入为单个E而不是以E开头的字符串
            {
                fclose(fp);
                return; // 结束函数
            }
            while (1)
            {
                printf("请输入学生学号(6位)\n");
                if (scanf("%d", &_id) != 1)
                {
                    printf("非数值型输入，请重试\n");
                    clearInputBuff(); // 清空输入缓冲区，防止死循环
                    continue;
                }
                if (_id < 100000 || _id > 999999) // 检查输入的学号是否为6位
                {
                    printf("输入错误，请重试\n");
                    clearInputBuff();
                    continue;
                }
                break;
            }
            while (1)
            {
                clearInputBuff();
                printf("请输入学生三门课目成绩(语数英)\n");
                if (scanf("%d %d %d", &chinese, &maths, &english) != 3)
                {
                    printf("非数值型输入,请重试\n");
                    continue;
                }
                break;
            }
            // 将学生数据存入，准备写入文件操作
            st.Marks.math_mark = maths;
            st.Marks.english_mark = english;
            st.Marks.chinese_mark = chinese;
            strcpy(st.name, _name);
            st.Id = _id;
            // 写入文件
            size_t write = fwrite(&st, sizeof(st), 1, fp);
            if (write != 1) // 判断是否写入成功
            {
                printf("Wrong!Fail writing\n");
                fclose(fp);
                return;
            }
            printf("Successfully write\n\n");
        }
    }
}

void readStudentInfo() // 文件读取学生信息
{
    Student stu;
    FILE *fp = fopen("Database.bin", "rb"); // 以只读方式打开文件
    if (fp == NULL)
    {
        perror("Oops!Cant open the file\n");
        exit(FILE_CANT_OPEN);
    }

    while (fread(&stu, sizeof(Student), 1, fp) == 1) // 从文件中一次读取一个Student类型的数据
    {
        printf("学号:%d\n", stu.Id);
        printf("姓名:%s\n", stu.name);
        printf("数学:%d   英语:%d   语文:%d\n", stu.Marks.math_mark, stu.Marks.english_mark, stu.Marks.chinese_mark);
        printf("\n");
    }
    fclose(fp);       // 读取操作结束，关闭文件
    clearInputBuff(); // 清空输入缓冲区
    while (1)
    {
        printf("按E退回\n");
        char ch[5];
        stringInput(ch, sizeof(ch));
        if ((ch[0] == 'e' || ch[0] == 'E') && strlen(ch) == 1)
        {
            return; // 终止函数
        }
    }
}

void deleteStudentInfo() // 删除学生信息
{
    int temp_id;
    Student stu;

    FILE *fp = fopen("Database.bin", "rb"); // 只读方式打开文件
    if (fp == NULL)                         // 检测文件是否正确打开
    {
        perror("Oops!Cant open the file\n");
        exit(FILE_CANT_OPEN);
    }
    FILE *fptem = fopen("Temp.bin", "wb"); // 只写方式打开文件
    if (fptem == NULL)
    {
        perror("Oops!Cant open the file\n");
        exit(FILE_CANT_OPEN);
    }

    if (!fread(&stu, sizeof(stu), 1, fp)) // 判断数据库是否为空库
    {
        perror("信息库为空!");
        fclose(fp);
        Delay_ms(1000); // 延时1秒
        return;
    }
    rewind(fp); // 重置内部位置指示指针到文件开头

    while (1)
    {
        while (1)
        {
            printf("请输入要删除的学生学号(6位)\n");
            if (scanf("%d", &temp_id) == 1)
            {
                if ((temp_id >= 10000) && (temp_id <= 999999)) // 检测用户输入的学号是否为6位
                {
                    while (fread(&stu, sizeof(Student), 1, fp) == 1) // 检查该学号的学生是否存在
                    {
                        if (stu.Id == temp_id)
                        {
                            fseek(fp, 0, SEEK_SET);
                            goto label1; // 跳转前往label1
                        }
                    }
                    printf("未找到该学生，请重试\n"); // 学生未找到，重新回到输入
                    fseek(fp, 0, SEEK_SET);           // 重置文件指针
                    continue;
                }
                else
                {
                    printf("输入错误，请重试\n");
                    continue;
                }
            }
            else
            {
                printf("非数值型输入，请重试\n");
                clearInputBuff(); // 清空缓冲区
                continue;
            }
        }

    label1:
        while (fread(&stu, sizeof(Student), 1, fp) == 1) // 从文件中读取学生数据
        {
            if (stu.Id != temp_id)
            {
                fwrite(&stu, sizeof(Student), 1, fptem); // 将读取到的数据写入新文件
                continue;
            }
            if (stu.Id == temp_id) // 不写入用户要删除的数据
            {
                continue;
            }
        }

        fclose(fp); // 关闭文件
        fclose(fptem);
        // 文件替换
        remove("Database.bin");
        rename("Temp.bin", "Database.bin");

        printf("成功删除\n按E退出或其余键继续\n");
        clearInputBuff();
        char ch = getchar();
        if (ch == 'E' || ch == 'e')
        {
            return; // 结束函数
        }
    }
}

void fixStudentInfo() // 修改学生信息
{
    Student stu;
    int search_id;
    int i;
    char ch;

    FILE *fp = fopen("Database.bin", "rb+"); // 读写方式打开文件
    if (fp == NULL)
    {
        perror("Error openning the file");
        return;
    }

    if (!fread(&stu, sizeof(Student), 1, fp)) // 检查数据库中是否有数据
    {
        perror("信息库为空!");
        fclose(fp);
        Delay_ms(1000); // 延时1秒
        return;
    }
    rewind(fp);

label:
    while (1)
    {
        system("cls"); // 清空界面
        printf("请输入要修改的学生学号(按E退出)\n");
        while (1)
        {
            if (scanf("%d", &search_id) != 1)
            {
                char ch = getchar();
                if (ch == 'E' || (ch == 'e'))
                    return; // 检查用户输入E，并作出响应
                printf("非数值型输入，请重试\n");
                clearInputBuff();
                continue;
            }
            if (search_id < 100000 || search_id > 999999) // 若输入的学号非6位
            {
                printf("输入错误，请重试\n");
                clearInputBuff();
                continue;
            }
            break;
        }

        while (fread(&stu, sizeof(Student), 1, fp) == 1) // 检查用户所输入的学号是否有对应的学生
        {
            if (search_id == stu.Id)
            {
                break;
            }
        }
        if (stu.Id != search_id && feof(fp))
        {
            printf("未找到该学生\n");
            Delay_ms(1000);
            goto label;
        }
        rewind(fp); // 重置文件内部位置指示器至开头

        Menu_B();
        i = Do_MenuB();
        switch (i)
        {
        case 1:
            system("cls");
            fixName(search_id);
            break;
        case 2:
            system("cls");
            fixId(search_id);
            break;
        case 3:
            system("cls");
            fixMark(search_id);
            break;
        }
    }
}

void fixName(int search_id) // 修改姓名
{
    Student stu;
    char _name[20];

    FILE *fpn = fopen("Database.bin", "rb+");
    if (fpn == NULL)
    {
        perror("Error openning the file");
        return;
    }

    printf("请输入新姓名\n");
    clearInputBuff();
    stringInput(_name, sizeof(_name)); // 输入功能函数
    while (fread(&stu, sizeof(Student), 1, fpn) == 1)
    {
        if (search_id != stu.Id)
        {
            continue;
        }
        if (search_id == stu.Id)
        {
            strcpy(stu.name, _name);
            fseek(fpn, -sizeof(Student), SEEK_CUR); // 将指针重新指向上一个区块数据，准备复写
            fwrite(&stu, sizeof(Student), 1, fpn);  // 复写数据
            printf("修改成功\n");
            Delay_ms(1000);
            fclose(fpn);
            return;
        }
    }
}

void fixId(int search_id) // 修改学号
{
    Student stu;
    int _id;

    FILE *fpn = fopen("Database.bin", "rb+");
    if (fpn == NULL)
    {
        perror("Error openning the file");
        return;
    }

    printf("请输入新学号\n");

label2:
    while (1)
    {
        if (scanf("%d", &_id) != 1)
        {
            printf("非数值型输入，请重试\n");
            clearInputBuff();
            continue;
        }
        else
        {
            if (_id < 100000 || _id > 999999) // 判断用户输入的新学号是否为6位
            {
                printf("输入错误，请重试\n");
                continue;
            }
            while (fread(&stu, sizeof(Student), 1, fpn) == 1) // 检查数据库中是否有与之重复的学号，若有则要用户重新输入。
            {
                if (_id == stu.Id)
                {
                    printf("该学号已存在，请重试\n");
                    rewind(fpn); // 重置文件内部位置指示器
                    goto label2;
                }
                if (_id != stu.Id && feof(fpn)) // 若无重名学号，跳出循环继续往下执行
                {
                    break;
                }
            }
        }
        break;
    }

    rewind(fpn);
    while (fread(&stu, sizeof(Student), 1, fpn) == 1)
    {
        if (search_id != stu.Id)
        {
            continue;
        }
        if (search_id == stu.Id)
        {
            stu.Id = _id;
            fseek(fpn, -sizeof(Student), SEEK_CUR); // 将指针重新指向上一个区块数据，准备复写
            fwrite(&stu, sizeof(Student), 1, fpn);  // 复写数据
            printf("修改成功\n");
            Delay_ms(1000);
            fclose(fpn);
            return;
        }
    }
}

void fixMark(int search_id) //修改三科成绩
{
    Student stu;
    int eng, chs, math;

    FILE *fpn = fopen("Database.bin", "rb+");
    if (fpn == NULL)
    {
        perror("Error openning the file");
        return;
    }

    printf("请依次输入英语，语文，数学成绩\n");
    while (1)
    {
        if (scanf("%d %d %d", &eng, &chs, &math) != 3)
        {
            printf("非数值型输入，请重试\n");
            clearInputBuff();
            continue;
        }
        break;
    }

    while (fread(&stu, sizeof(Student), 1, fpn) == 1)
    {
        if (search_id != stu.Id)
        {
            continue;
        }
        if (search_id == stu.Id)
        {
            stu.Marks.chinese_mark = chs;
            stu.Marks.english_mark = eng;
            stu.Marks.math_mark = math;

            fseek(fpn, -sizeof(Student), SEEK_CUR); // 将指针重新指向上一个区块数据，准备复写
            fwrite(&stu, sizeof(Student), 1, fpn);  // 复写数据
            printf("修改成功\n");
            Delay_ms(1000);
            fclose(fpn);
            return;
        }
    }
}

void searchStudentInfo() // 查询学生信息
{
    Student stu;
    int _id;

    system("cls");
    while (1)
    {
        printf("请输入要查询学生的学号(按E退出)\n");
        while (1)
        {
            if (scanf("%d", &_id) != 1)
            {
                char ch = getchar();
                if (ch == 'E' || ch == 'e')
                    return;
                printf("非数值型输入，请重试\n");
                Delay_ms(1000);
                system("cls");
                clearInputBuff();
                continue;
            }
            else
            {
                if (_id < 100000 || _id > 999999)
                {
                    printf("输入错误，请重试\n");
                    Delay_ms(1000);
                    system("cls");
                    continue;
                }
            }
            break;
        }

        FILE *fpn = fopen("Database.bin", "rb");
        while (fread(&stu, sizeof(Student), 1, fpn) == 1)
        {
            if (_id == stu.Id)
            {
                printf("找到该学生\n");
                printf("Name:%s\n", stu.name);
                printf("ID:%d\n", stu.Id);
                printf("Math:%d    English:%d    Chinese:%d\n\n",
                       stu.Marks.math_mark, stu.Marks.english_mark, stu.Marks.chinese_mark);
                fclose(fpn);
                break;
            }
        }
        if (_id != stu.Id && feof(fpn))
        {
            printf("未找到该学生\n");
            fclose(fpn);
            Delay_ms(1000);
            system("cls");
            continue;
        }
    }
}