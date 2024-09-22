#ifndef _STAFF
#define _STAFF

#include <iostream>
#include <string>
#include <mingw.thread.h>

class Job;
class DepNum;

//公司人员基类 用于继承，不允许实例化对象
class Basic_Staff{
    protected:
    std::string Name;   //姓名
    double bonus; //底薪
    unsigned int Numer; //编号

    public:
    Basic_Staff();

    virtual ~Basic_Staff() = 0; //纯虚析构
};

class Staff : public Basic_Staff{
    friend void get_basicInfo(Staff &);
    friend void get_detailInfo(Staff &);
    private:
    DepNum staff_DepNum;  //职工部门编号
    Job staff_Job;  //职工岗位

    /*不允许职工信息的拷贝和赋值*/
    Staff(const Staff&) = delete;
    Staff& operator=(const Staff&) = delete;

    public:
    Staff();    //默认构造

    void AddStaffInfo();    //添加职工信息
    

};

/*职工岗位*/
class Job{
    private:
    std::string Job_1;
    std::string Job_2;
    std::string Job_3;
    std::string Job_4;

    //不允许拷贝构造
    Job(const Job&) = delete;
    //不允许赋值
    Job& operator=(const Job&) = delete;

    public:
    Job(){}
    /*软件开发岗位*/
    auto Software_Developemnt();

    /*销售岗位*/
    auto Sale();

    /*硬件开发*/
    auto HardWare_Development();

    /*测试*/
    auto Debugging();
};

/*职工部门编号*/
class DepNum{
    friend class Staff;
    private:
    std::string Depnumer;
    protected:
    void  Initial(){this->Depnumer = "0000000";}
    void  NA10010(){this->Depnumer = "NA10010";}
    void  NA10011(){this->Depnumer = "NA10011";}
    void  NA10012(){this->Depnumer = "NA10012";}
    void  NC10026(){this->Depnumer = "NC10026";}
    void  NC10028(){this->Depnumer = "NC10028";}
    void  NC10031(){this->Depnumer = "NC10031";}
    public:
    DepNum();
};

#endif  //_STAFF