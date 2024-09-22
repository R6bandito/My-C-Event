#include "Staff.h"
#include "unlock.h"

Basic_Staff::Basic_Staff() : Name("Null"), bonus(0.0), Numer(0) {}

/*软件开发*/
auto Job::Software_Developemnt()
{
    Job_1 = "Software_Dev";
    return Job_1;
}

/*销售*/
auto Job::Sale()
{
    Job_2 = "Sale";
    return Job_2;
}

/*硬件开发*/
auto Job::HardWare_Development()
{
    Job_3 = "HardWare_Dev";
    return Job_3;
}

/*测试*/
auto Job::Debugging()
{
    Job_4 = "Debugging_Eng";
    return Job_4;
}

/*DepNum构造*/
DepNum::DepNum()
{
    Initial();
}
/*Staff构造*/
Staff::Staff() : Basic_Staff(), staff_DepNum(DepNum()), staff_Job() {}

/*添加职工信息*/
void get_basicInfo(Staff &stf)
{
    using namespace std;
    cout << "请输入姓名: ";
    if (getline(cin, stf.Name)) {} // 输入成功什么都不做
    else
    { // 错误处理
        cout << "Something wrong Happened" << endl;
        delay_sec(2);
        return;
    }

    cout<<"请输入编号: ";
    if(!(cin>>stf.Numer)){
        Cin_Error_Handle();
        delay_sec(1);
    }

    cout<<"请输入该职工底薪: ";
    if(!(cin>>stf.bonus)){
        Cin_Error_Handle();
        delay_sec(1);
    }
}

void get_detailInfo(Staff &stf){
    using namespace std;
    cout<<R"delimiter(请选择职工部门
    部门:
    NA10|0    NA11|1   NA12|2   NC26|3   NC28|4  NC31|5)delimiter";
}
void Staff::AddStaffInfo()
{
    using namespace std;
    std::thread th2;
    while (true)
    {
        std::thread th1(get_basicInfo, this);
        std::thread th2(get_detailInfo,this);
    }
}
