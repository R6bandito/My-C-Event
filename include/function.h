#ifndef FUNC_H
#define FUNC_H

typedef struct Course{  //课程分数结构体
    int math_mark;
    int english_mark;
    int chinese_mark;
}Course;

typedef struct Student{     //学生结构体
    int Id;     //学生学号
    char name[20];  //学生姓名
    Course Marks;   //学生三门课的成绩
}Student;


void addStudentInfo();  //声明新增学生信息函数
void readStudentInfo();     //声明从文件中读取学生信息函数
void deleteStudentInfo();   //声明删除学生信息函数
void fixStudentInfo();  //声明修改学生信息函数
void Delay_ms(unsigned int time);   //声明延时函数
void searchStudentInfo();   //声明查询学生函数

void fixName(int search_id); //声明修改姓名函数
void fixId(int search_id);   //声明修改学号函数
void fixMark(int search_id); //声明修改分数函数

#endif  //FUNC_H