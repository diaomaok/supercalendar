#ifndef DateFestival_hpp
#define DateFestival_hpp

#include<iostream>
#include"Festival.hpp"
using namespace std;

class DateFestival :public Festival
{
public:
	//���캯��
	DateFestival(int format, string name, int month,int ordnum, int day);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ȡ��������
	virtual string getFestivalName();

	//��������
	~DateFestival();

};

#endif // !DateFestival_hpp
