#ifndef DateFestival_hpp
#define DateFestival_hpp

#include<iostream>
#include"Festival.hpp"
using namespace std;

class DateFestival :public Festival
{
public:
	//构造函数
	DateFestival(int format, string name, int month,int ordnum, int day);

	//显示节日信息
	virtual void showInfo();

	//获取节日名称
	virtual string getFestivalName();

	//析构函数
	~DateFestival();

};

#endif // !DateFestival_hpp
