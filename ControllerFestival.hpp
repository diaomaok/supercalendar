#ifndef ControllerFestival_hpp
#define ControllerFestival_hpp
#include<iostream>
#include<fstream>
#include<string>
#include"Festival.hpp"
#include"DateFestival.hpp"
#include"ViewFestival.hpp"
#define FILENAME "FestivalFile.txt"
using namespace std;

class ControllerFestival
{
public:
	ViewFestival vf;
	//构造函数
	ControllerFestival();
	
	//展示菜单
	void showMenu();

	//退出系统
	void ExitSystem();
	
	// 记录节日数量
	int m_FestNum;

	//节日数组指针
	Festival** m_FestArray;

	//添加节日
	void AddFest();

	//显示节日
	void Show_Fest();
	
	//保存文件
	void SaveFestival();

	//判断文件是否为空 标志
	bool m_FileIsEmpty;

	//统计文件中节日数量
	int getFestNum();

	//初始化节日
	void initFest();

	//删除节日
	void Del_Fest();

	//判断职工是否存在，如果存在返回职工所在数组中的位置，不存在返回-1
	int IsExist(string name);

	//修改节日
	void Mod_Fest();

	//判断是否为闰年
	int IsLeapYear(int yeardays);

	//查询具体节日
	void Find_Fest();

	//计算距今天数
	void FestivalToNow();

	//查询时间区间内节日排序
	void Sort_Fest();

	//日历和节日显示
	void ShowCalender();

	//判断一个月第一天星期几
	int firstdayofmonth(int year,int month);

	//析构函数
	~ControllerFestival();
};




#endif // !ControllerFestival_hpp


