#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function_IO.h"
#include "function.h"

#define FILE_CANT_OPEN 3

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
                printf("请输入学生学号\n");
                if (scanf("%d", &_id) != 1)
                {
                    printf("非数值型输入，请重试\n");
                    clearInputBuff(); // 清空输入缓冲区，防止死循环
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
                            fseek(fp,0,SEEK_SET);
                            goto label1; // 跳转前往label1
                        }
                    }
                    printf("未找到该学生，请重试\n");   //学生未找到，重新回到输入
                    fseek(fp,0,SEEK_SET);   //重置文件指针
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
        if(ch == 'E'|| ch == 'e')
        {
            return; //结束函数
        }
    }
}