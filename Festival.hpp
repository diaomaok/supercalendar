#ifndef Festival_hpp
#define Festival_hpp
#include<iostream>
#include<string>
using namespace std;

//节日抽象类
class Festival
{
public:
	//显示节日信息
	virtual void showInfo() = 0;

	//获得节日名称
	virtual string getFestivalName() = 0;
	
	//节日类型
	int m_format;

	//节日名称
	string m_name;
	//节日月份
	int m_month;
	//节日周数
	int m_ordnum;
	//节日日期
	int m_day;
};
#endif // !Festival_hpp

