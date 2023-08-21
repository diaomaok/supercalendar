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
	//���캯��
	ControllerFestival();
	
	//չʾ�˵�
	void showMenu();

	//�˳�ϵͳ
	void ExitSystem();
	
	// ��¼��������
	int m_FestNum;

	//��������ָ��
	Festival** m_FestArray;

	//��ӽ���
	void AddFest();

	//��ʾ����
	void Show_Fest();
	
	//�����ļ�
	void SaveFestival();

	//�ж��ļ��Ƿ�Ϊ�� ��־
	bool m_FileIsEmpty;

	//ͳ���ļ��н�������
	int getFestNum();

	//��ʼ������
	void initFest();

	//ɾ������
	void Del_Fest();

	//�ж�ְ���Ƿ���ڣ�������ڷ���ְ�����������е�λ�ã������ڷ���-1
	int IsExist(string name);

	//�޸Ľ���
	void Mod_Fest();

	//�ж��Ƿ�Ϊ����
	int IsLeapYear(int yeardays);

	//��ѯ�������
	void Find_Fest();

	//����������
	void FestivalToNow();

	//��ѯʱ�������ڽ�������
	void Sort_Fest();

	//�����ͽ�����ʾ
	void ShowCalender();

	//�ж�һ���µ�һ�����ڼ�
	int firstdayofmonth(int year,int month);

	//��������
	~ControllerFestival();
};




#endif // !ControllerFestival_hpp


