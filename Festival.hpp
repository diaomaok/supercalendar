#ifndef Festival_hpp
#define Festival_hpp
#include<iostream>
#include<string>
using namespace std;

//���ճ�����
class Festival
{
public:
	//��ʾ������Ϣ
	virtual void showInfo() = 0;

	//��ý�������
	virtual string getFestivalName() = 0;
	
	//��������
	int m_format;

	//��������
	string m_name;
	//�����·�
	int m_month;
	//��������
	int m_ordnum;
	//��������
	int m_day;
};
#endif // !Festival_hpp

