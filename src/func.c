#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

// 以下代码为初始化初链表数据
char name[5][20] = {"TOM", "Bob", "Mike", "Alice", "Jenny"};
char sex[5][20] = {"male", "male", "male", "female", "female"};
int number[5] = {1, 2, 3, 4, 5};
extern Link phead;

void ClearInputBuff()
{ // 清空键盘输入缓存
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

char CountList(Link head)
{ // 统计链表中目前项数
    char count = 0;
    Link p = head;
    while (p->next != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}

void StringInput(char *p)
{ // 输入功能函数。读取用户键盘输入并且剔除换行符
    if (fgets(p, 20, stdin) != NULL)
    {
        p[strcspn(p, "\n")] = '\0'; // 查找到换行符位置并将其更换为结束符
    }
    else
    {
        printf("Wrong!\n");
    }
}

void Distinguish(short i)
{ // 传递函数。将输入传入对应的功能函数进行相对应的功能实现
    if (i == 1)
    {
        SearchStudents(phead);
    }
    if (i == 2)
    {
        AddElement(phead);
    }
    if (i == 3)
    {
        DeleteStudentInfo(phead);
    }
    if (i == 4)
    {
        CheckList(phead);
    }
}

Link NewList()
{ // 新建链表
    Link rear;
    Link head;

    // 下面语句为申请一个头结点，并且对头结点进行初始化
    head = (Link)malloc(sizeof(Node));
    strcpy(head->data.Name, "NULL");
    strcpy(head->data.Sex, "NULL");
    head->data.Number = 0;
    head->next = NULL;

    rear = head;
    for (short i = 0; i < 5; i++)
    {                                           // 尾插法
        Link node = (Link)malloc(sizeof(Node)); // 新建一个结点
        strcpy(node->data.Name, name[i]);       // 逐一为链表中每一个结点分配对应的数据
        strcpy(node->data.Sex, sex[i]);
        node->data.Number = number[i];

        rear->next = node;
        rear = node;
    }
    rear->next = NULL;
    return head;
}

void CheckList(Link head)
{ // 遍历链表，实现全部输出学生信息
    Link p = head;
    short i;
    while (p->next != NULL)
    {
        printf("姓名:%s\n", p->next->data.Name);
        printf("性别:%s\n", p->next->data.Sex);
        printf("学号:%d\n", p->next->data.Number);
        printf("\n\n");
        p = p->next;
    }
    while (1)
    {
        printf("按-1返回\n");
        if (scanf("%hd", &i) != 1)
        { // 检测输入是否为非数值型
            printf("非数值型输入，请重试\n");
            ClearInputBuff(); // 清空输入缓冲区。防止因非数值型输入而导致无限循环bug
        }
        if (i == -1)
            return; // 结束程序
        else
            printf("输入错误,请重试\n");
    }
}

void SearchStudents(Link head)
{ // 通过学号查找学生信息
    short n;
    Link p = head;
back1:
    printf("请输入要查询的学生学号(按-1返回)\n");
    if (scanf("%hd", &n) != 1)
    { // 检测输入是否为非数值型
        printf("非数值型输入，请重试\n");
        ClearInputBuff(); // 清空输入缓冲区。防止因非数值型输入而导致无限循环bug
        goto back1;
    }

    if (n <= 0 && n != -1)
    { // 检测输入的学号是否合理
        printf("错误输入，请重试\n");
        goto back1;
    }
    if (n == -1)
    {
        return; // 结束程序
    }

    char count = CountList(head); // 获取目前链表项数
    while (p->next != NULL && n <= count)
    {
        if (p->next->data.Number == n)
        { // 遍历整个表，对学号进行比较。若符合则输出相对应的数据
            printf("姓名:%s\t", p->next->data.Name);
            printf("性别:%s\t", p->next->data.Sex);
            printf("学号:%d\n", p->next->data.Number);
            break;
        }
        p = p->next;
    }
    if (p->next == NULL || n > count)
    {
        printf("该学号不存在，请重新输入\n");
        goto back1;
    }

    p = head; // 重置工作指针
    goto back1;
}

void AddElement(Link head)
{
    Link p = head;
    short i = CountList(head); // 链表元素个数
    while (p->next != NULL)
    { // 移动工作指针至目前链表最后一个结点
        p = p->next;
    }
    while (1)
    {
        ClearInputBuff();                 // 清空输入缓冲区
        Link node = malloc(sizeof(Node)); // 创建新结点

        // 创建临时变量，存储学生信息
        char _Name[20];
        char _Sex[20];

        // 输入要添加的学生信息，并将其存储在临时变量中
        printf("输入学生姓名(按-1返回)\n");
        StringInput(_Name);
        if (_Name[1] == 49 && _Name[0] == 45)
        { // 检测输入是否为-1
            return;
        }
        printf("请输入学生性别\n");
        StringInput(_Sex);

        // 将输入的学生信息分配到新结点中
        strcpy(node->data.Name, _Name);
        strcpy(node->data.Sex, _Sex);
        node->data.Number = ++i; // 由于是逐项添加学生，因此学号可借由递增自行计算

        // 对结点进行链接
        p->next = node;
        node->next = NULL;
        p = node;

        // 用户自行选择接下来的操作
        printf("(输入任意键继续或按-1返回)\n");
        short temp;
        scanf("%hd", &temp);
        if (temp == -1)
            return; // 退出函数
    }
}

void DeleteStudentInfo(Link head)
{                  // 定义删除学生信息函数
    Link p = head; // 初始化工作指针
    short n;
    short cnt = CountList(head); // 调用统计函数，计算目前链表的结点数

    while (1)
    {
        // 对输入的数据进行检查
        while (1)
        {
            printf("请输入您要删除学生的学号(按-1返回)\n");
            ClearInputBuff(); // 清空输入缓冲区，为接下来的输入做准备
            if (scanf("%hd", &n) != 1)
            {
                printf("非数值型输入，请重试\n");
                continue;
            }
            if (n == -1)
            {
                return;
            }
            if (n > cnt || ((n <= 0) && (n != -1)))
            {
                printf("该学生不存在，请重新输入\n");
                continue;
            }
            break;
        }

        // 移动工作指针到要删除结点的前驱结点
        for (short i = 1; i < n; i++)
        {
            p = p->next;
        }

        // 删除结点，释放空间
        Link node = p->next;
        p->next = node->next;
        free(node);
        printf("成功删除\t");
        cnt--; // 更新整个链表结点数

        while (p->next != NULL)
        { // 对删除项之后的所有项学生学号进行更新
            p->next->data.Number -= 1;
            p = p->next;
        }
        p = head; // 重置指针

        // 流程控制
        printf("按任意键继续(或按-1退出)\n");
        short temp;
        scanf("%hd", &temp);
        if (temp == -1)
        {
            return;
        }
    }
}