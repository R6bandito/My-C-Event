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
        printf("Oops!Cant open the file\n");
        exit(FILE_CANT_OPEN);
    }

    while (1)
    {
        while (1)
        {
            clearInputBuff();
            printf("请输入学生姓名(按E退出)\n");
            stringInput(_name, sizeof(_name)); // 输入学生姓名
            if(_name[0] == 'E' || _name[0] == 'e')  //判断用户输入是否为E
            {
                fclose(fp);
                return;     //结束函数
            }
            while (1)
            {
                printf("请输入学生学号\n");
                if (scanf("%d", &_id) != 1)
                {
                    printf("非数值型输入，请重试\n");
                    clearInputBuff();   //清空输入缓冲区，防止死循环
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
            strcpy(st.name,_name);
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