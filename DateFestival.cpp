#include"DateFestival.hpp"

DateFestival::DateFestival(int format,string name, int month,int ordnum, int day)
{
	this->m_format = format;
	this->m_name = name;
	this->m_month = month;
	this->m_day = day;
	this->m_ordnum = ordnum;
}

void DateFestival::showInfo()
{
	cout << "节日名称：" << this->m_name
		<< "\t节日月份" << this->m_month
		<< "\t节日日期" << this->m_day << endl;
}

string DateFestival::getFestivalName()
{
	return m_name;
}
//析构函数
DateFestival::~DateFestival(){};