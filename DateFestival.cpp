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
	cout << "�������ƣ�" << this->m_name
		<< "\t�����·�" << this->m_month
		<< "\t��������" << this->m_day << endl;
}

string DateFestival::getFestivalName()
{
	return m_name;
}
//��������
DateFestival::~DateFestival(){};