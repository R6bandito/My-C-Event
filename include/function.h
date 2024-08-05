
#ifndef FUNCTION_H
#define FUNCTION_H

typedef struct Student{ //定义学生信息结构体
    char Name[20];
    char Sex[5];
    int Number;
}stu;

typedef struct Node{    //定义结点
    stu data;
    struct Node* next;
}Node,*Link;

void Distinguish(short i);  //传递函数
Link NewList(); //新建链表函数
void CheckList(Link head); //遍历链表函数
void SearchStudents(Link head); //学生信息查询函数
char CountList(Link head);  //统计链表项数函数
void ClearInputBuff();  //清空键盘输入缓冲区
void AddElement(Link head); //添加学生信息函数
void DeleteStudentInfo(Link head);  //删除学生信息函数
void StringInput(char *p); //字符串输入函数

#endif