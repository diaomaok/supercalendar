#include<iostream>
#include<ctime>
#include"ControllerFestival.hpp"
#include"ViewFestival.hpp"
using namespace std;


ControllerFestival::ControllerFestival()
{
	//1.�ļ�������
	ifstream ifs;
		//���ļ�
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		//��ʼ������
		//��ʼ����¼��������
		this->m_FestNum = 0;
		//��ʼ������ָ��
		this->m_FestArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2.�ļ����ڣ�����û������
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		//cout << "�ļ�Ϊ��" << endl;
		//��ʼ������
		//��ʼ����¼��������
		this->m_FestNum = 0;
		//��ʼ������ָ��
		this->m_FestArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����ڣ����Ҽ�¼����
	int num = this->getFestNum();
	cout << "���н��ո���Ϊ��" << num << endl;
	this->m_FestNum = num;
	//���ٿռ�
	this->m_FestArray = new Festival * [this->m_FestNum];
	//���ļ��е����ݴ浽������
	this->initFest();

	//��ʼ������
	//this->m_FestNum = 0;
	//this->m_FestArray = NULL;
}


void ControllerFestival::SaveFestival()
{
	ofstream ofs;
	//������ķ�ʽ���ļ�����д�ļ�
	ofs.open(FILENAME, ios::out);
	
	//��ÿ�����յ���Ϣд�뵽�ļ���
	for (int i = 0; i < this->m_FestNum; i++)
	{
		ofs << this->m_FestArray[i]->m_name << " "
			<< this->m_FestArray[i]->m_month << " "
			<< this->m_FestArray[i]->m_day << endl;
	}

	//�ر��ļ�
	ofs.close();

}

//ͳ���ļ��н�������
int ControllerFestival::getFestNum()
{
	ifstream ifs;
	//���ļ� ��ȡ
	ifs.open(FILENAME, ios::in);
	string name;
	int month;
	int day;

	int num = 0;
	while (ifs >> name && ifs >> month && ifs >> day)
	{
		//ͳ����������
		num++;
	}
	return num;
}

//��ʼ������
void  ControllerFestival::initFest()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string name;
	int month;
	int day;

	int index = 0;
	while (ifs >> name && ifs >> month && ifs >> day)
	{
		Festival* festival = NULL;
		festival = new DateFestival(0,name, month,-1, day);
		this->m_FestArray[index] = festival;
		index++;
	}
	//�ر��ļ�
	ifs.close();
}
ControllerFestival::~ControllerFestival() {
	if (this->m_FestArray != NULL) {
		delete[]this->m_FestArray;
		this->m_FestArray = NULL;
	}

}
void ControllerFestival::showMenu() {
	vf.ShowMenu();

}
//��ӽ���
void ControllerFestival::AddFest()
{
	cout << "��������ӽ�������:" << endl;
	int addNum = 0;//�����û���������
	cin >> addNum;
	if (addNum > 0)
	{
		//���
		//��������¿ռ��С
		int newSize = this->m_FestNum + addNum;
		//�����¿ռ�
		Festival** newSpace = new Festival * [newSize];
		//��ԭ���ռ������ݣ��������¿ռ���
		if (this->m_FestArray != NULL) {
			for (int i = 0; i < this->m_FestNum; i++) {
				newSpace[i] = this->m_FestArray[i];
			}
		}
		//���������
		for (int i = 0; i < addNum; i++) {
			int fFormat;
			string fName;
			int fMonth;
			int fOrdNum = -1;//!!fesitval��Ҫ���!!
			int fDay;

			cout << "�������" << i + 1 << "���½��յ���ʽ��0�������ͣ�1������������ 2�����������ͣ�" << endl;
			cin >> fFormat;

			Festival* festival = NULL;
			bool judgename=true;
			switch (fFormat) {
			case 0: {
				cout << "�������" << i + 1 << "���½��յĽ�����" << endl;
				cin >> fName;

				//�жϽ����Ƿ��ظ�
				while (judgename == true)
				{
					for (int i = 0; i < this->m_FestNum; i++)
					{
						if (this->m_FestArray[i]->m_name == fName)
						{
							judgename = false;
							cout << "�����Ѿ����ڣ������������������" << endl;
							cin >> fName;
						}
					}
				}
				

				cout << "�������" << i + 1 << "���½��յ��·�" << endl;
				cin >> fMonth;
				cout << "�������" << i + 1 << "���½��յ�����" << endl;
				cin >> fDay;

				festival = new DateFestival(fFormat, fName, fMonth, fOrdNum, fDay);
				break;
			}
			default:
			{cout << "������Ľ�����ʽ��������������" << endl;
			system("pause");
			system("cls");

			break; }
			}
			//��������������������
			newSpace[this->m_FestNum + i] = festival;


		}
		//�ͷ�ԭ�еĿռ�
		delete[]this->m_FestArray;
		//�����¿ռ��ָ��
		this->m_FestArray = newSpace;
		//�����µĽ�����
		this->m_FestNum = newSize;

		//�ɹ���Ӻ� ���浽�ļ���
		SaveFestival();

		//���½��ղ�Ϊ�ձ�־
		this->m_FestNum = newSize;
		//��ʾ�ɹ����
		cout << "�ɹ����" << addNum << "���½���!" << endl;
		m_FileIsEmpty = false;
	}
	else { cout << "������������" << endl; }
	//��������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}
void ControllerFestival::ExitSystem()
{
	cout << "��ӭ�´�ʹ��!" << endl;
	system("pause");
	exit(0);
}

//��ʾ����
void ControllerFestival::Show_Fest() {
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < m_FestNum; i++) {
			//���ö�̬���ó���ӿ�
			this->m_FestArray[i]->showInfo();
		}

	}
	//�������������
	system("pause");
	system("cls");
}

//ɾ������
void ControllerFestival::Del_Fest() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ�Ϊ�գ�" << endl;
	}
	else {
		//���ս�����ɾ��
		cout << "��������Ҫɾ���Ľ�����" << endl;
		string dname = "";
		cin >> dname;
		int index = this->IsExist(dname);
		if (index != -1)//˵�����մ���
		{
			//����ǰ��
			for (int i = index; i < this->m_FestNum - 1; i++) {
				this->m_FestArray[i] = this->m_FestArray[i + 1];

			}
			this->m_FestNum--;//���������м�¼�Ľ��ո���
			//����ͬ�����µ��ļ���
			this->SaveFestival();
			cout << "ɾ���ɹ�!" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ��ý���" << endl;
		}
	}
	//�������������
	system("pause");
	system("cls");
}
//�жϽ����Ƿ���ڣ�������ڷ��ؽ������������е�λ�ã������ڷ���-1
int ControllerFestival::IsExist(string name) {
	int index = -1;
	for (int i = 0; i < this->m_FestNum; i++) {
		if (this->m_FestArray[i]->m_name == name) {
			//�ҵ�����
			index = i;
			break;
		}
	}
	return index;
}



//�޸Ľ���
void ControllerFestival::Mod_Fest()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		cout << "�������޸Ľ��յ����ƣ�" << endl;
		string name;
		cin >> name;
		int ret = this->IsExist(name);
		if (ret != -1)
		{
			//���ҵ��ý���
			delete this->m_FestArray[ret];
			int format = 0;
			int newMonth = 0;
			int newordnum = 0;
			int newDay = 0;
			Festival* festival = NULL;
			cout << "�鵽" << name << "���������������ʽ���·ݺ����ڣ�" << endl;
			cout << "��ʽ����0,��ʾ���գ�1��ÿ���������ܵ��ܼ���2��ÿ�µ������ܵ��ܼ���" << endl;
			cin >> format;
			if (format == 0)
			{
			cout << "�·�" << endl;
			cin >> newMonth;
			cout << "����" << endl;
			cin >> newDay;
			festival = new DateFestival(0, name, newMonth, -1, newDay);
			}
			else if(format == 1)
			{
				cout << "�·�" << endl;
				cin >> newMonth;
				cout << "�����ڼ���" << endl;
				cin >> newordnum;
				cout << "�ܼ�" << endl;
				cin >> newDay;
			}
			else if (format == 2)
			{
				cout << "�·�" << endl;
				cin >> newMonth;
				cout << "�����ڼ���" << endl;
				cin >> newordnum;
				cout << "�ܼ�" << endl;
				cin >> newDay;
			}
			else
			{
				cout << "������ʽ" << endl;
				system("cls");
			}
			//�������ݵ�������
			this->m_FestArray[ret] = festival;
			cout << "�޸ĳɹ�" << endl;
			//���浽�ļ���
			this->SaveFestival();
		}
		else
		{
			cout << "�޸�ʧ�ܣ��޴˽���" << endl;

		}
	}
	//�����������
	system("pause");
	system("cls");
}

//��ѯʱ�������ڽ�������
void ControllerFestival::Sort_Fest()
{
	//int startyear = 0;
	int startmonth = 0;
	int startday = 0;
	//int endyear = 0;
	int endmonth = 0;
	int endday = 0;
	int form;
	cout << "������ʱ������" << endl;
	//cout << "��ʼ�꣺" << endl;
	//cin >> startyear;
	cout << "��ʼ�£�" << endl;
	cin >> startmonth;
	cout << "��ʼ�գ�" << endl;
	cin >> startday;
	//cout << "��ֹ�꣺" << endl;
	//cin >> endyear;
	cout << "��ֹ�£�" << endl;
	cin >> endmonth;
	cout << "��ֹ�գ�" << endl;
	cin >> endday;

	//�ж�����������Ƿ����


	cout << "����������ʽ����1������������2������������" << endl;
	cin >> form;

	//��������
	if (form == 1)
	{
		string tempname;
		int tempmonth;
		int tempday;
		for (int i = 0; i < this->m_FestNum - 1; i++)
		{
			for (int k = 0; k < this->m_FestNum - 1 - i; k++)
			{
				if ((this->m_FestArray[k]->m_month > this->m_FestArray[k + 1]->m_month) || ((this->m_FestArray[k]->m_month == this->m_FestArray[k+1]->m_month)&&(this->m_FestArray[k]->m_day> this->m_FestArray[k+1]->m_day)))
					{
						tempname = this->m_FestArray[k]->m_name;
						this->m_FestArray[k]->m_name = this->m_FestArray[k + 1]->m_name;
						this->m_FestArray[k + 1]->m_name = tempname;
						tempmonth = this->m_FestArray[k]->m_month;
						this->m_FestArray[k]->m_month = this->m_FestArray[k + 1]->m_month;
						this->m_FestArray[k + 1]->m_month = tempmonth;
						tempday = this->m_FestArray[k]->m_day;
						this->m_FestArray[k]->m_day = this->m_FestArray[k + 1]->m_day;
						this->m_FestArray[k + 1]->m_day = tempday;
					}
			}

		}
		for (int i = 0; i < this->m_FestNum; i++)
		{
			if (((this->m_FestArray[i]->m_month > startmonth) || ((this->m_FestArray[i]->m_month == startmonth) && (this->m_FestArray[i]->m_day >= startday)) )&& ((this->m_FestArray[i]->m_month < endmonth) || ((this->m_FestArray[i]->m_month == endmonth) && (this->m_FestArray[i]->m_day <= endday))))
			{
				cout << "�������ƣ�" << this->m_FestArray[i]->m_name
					<< "\t�����·�" << this->m_FestArray[i]->m_month
					<< "\t��������" << this->m_FestArray[i]->m_day << endl;
			}
		}
	}
	//��������
	else if (form == 2)
	{

		string tempname;
		int tempmonth;
		int tempday;
		for (int i = 0; i < this->m_FestNum - 1; i++)
		{
			for (int k = 0; k < this->m_FestNum - 1 - i; k++)
			{
				if (this->m_FestArray[k]->m_name > this->m_FestArray[k + 1]->m_name) 
				{
					tempname = this->m_FestArray[k]->m_name;
					this->m_FestArray[k]->m_name = this->m_FestArray[k + 1]->m_name;
					this->m_FestArray[k + 1]->m_name = tempname;
					tempmonth = this->m_FestArray[k]->m_month;
					this->m_FestArray[k]->m_month = this->m_FestArray[k + 1]->m_month;
					this->m_FestArray[k + 1]->m_month = tempmonth;
					tempday = this->m_FestArray[k]->m_day;
					this->m_FestArray[k]->m_day = this->m_FestArray[k + 1]->m_day;
					this->m_FestArray[k + 1]->m_day = tempday;
				}
			}
		}
		for (int i = 0; i < this->m_FestNum; i++)
		{
			if (((this->m_FestArray[i]->m_month > startmonth) || ((this->m_FestArray[i]->m_month == startmonth) && (this->m_FestArray[i]->m_day >= startday))) &&( (this->m_FestArray[i]->m_month < endmonth) || ((this->m_FestArray[i]->m_month == endmonth) && (this->m_FestArray[i]->m_day <= endday))))
			{
				cout << "�������ƣ�" << this->m_FestArray[i]->m_name
					<< "\t�����·�" << this->m_FestArray[i]->m_month
					<< "\t��������" << this->m_FestArray[i]->m_day << endl;

			}
		}
	}
	else
	{
		cout << "������������������" << endl;
		system("pause");
		system("cls");
	}
	system("pause");
	system("cls");
}

int ControllerFestival::IsLeapYear(int yeardays) {
	if (yeardays % 4 == 0 && yeardays % 100 != 0 || yeardays % 400 == 0) {
		return 366;
	}
	else {
		return 365;
	}
}
//����������
void ControllerFestival::FestivalToNow() {
	//����1970.1.1�������
	time_t SecondstoNow;
	SecondstoNow = time(NULL);
	//�õ�����ʱ��ṹ��
	struct tm now_time;
	time_t time_seconds = time(0);
	localtime_s(&now_time, &time_seconds);
	int DaysToFestival;
	//���û�׼��Ϊ1��1��
	struct tm basis_time;
	int SecondstoBasis;
	basis_time.tm_year = now_time.tm_year;
	basis_time.tm_mon = 0;
	basis_time.tm_mday = 1;
	basis_time.tm_hour = 0;
	basis_time.tm_min = 0;
	basis_time.tm_sec = 1;
	basis_time.tm_isdst = -1;
	//�õ���׼������
	SecondstoBasis = mktime(&basis_time);
	//�õ����սṹ��
	string name;
	cout << "�������ѯ�Ľ�������:" << endl;
	cin >> name;
	//���ҽ���
	int ret = this->IsExist(name);
	if (ret != -1) {
		//�ҵ�����
		cout << "���ҳɹ�" << endl;
		//���������ݴ���ṹ��tm
		int SecondstoFestival;
		struct tm info;
		info.tm_year = now_time.tm_year;
		info.tm_mon = (this->m_FestArray[ret]->m_month) - 1;
		info.tm_mday = (this->m_FestArray[ret]->m_day);
		info.tm_hour = 0;
		info.tm_min = 0;
		info.tm_sec = 1;
		info.tm_isdst = -1;
		SecondstoFestival = mktime(&info);
		if ((now_time.tm_mon) > (this->m_FestArray[ret]->m_month)) {
			DaysToFestival = (this->IsLeapYear(now_time.tm_year) - (SecondstoNow - SecondstoBasis) / 3600 / 24) + (SecondstoFestival - SecondstoBasis) / 3600 / 24;
			cout << "���վ�������Ϊ" << DaysToFestival + 1 << "��!" << endl;
		}
		else if ((now_time.tm_mon) == (this->m_FestArray[ret]->m_month)) {
			if ((now_time.tm_mday) == (this->m_FestArray[ret]->m_day))
			{
				cout << "���վ�������Ϊ0�죬�����ڽ��죡" << endl;
			}
			else if ((now_time.tm_mday) > (this->m_FestArray[ret]->m_day))
			{
				DaysToFestival = (this->IsLeapYear(now_time.tm_year) - (SecondstoNow - SecondstoBasis) / 3600 / 24) + (SecondstoFestival - SecondstoBasis) / 3600 / 24;
				cout << "���վ�������Ϊ" << DaysToFestival + 1 << "��!" << endl;
			}
			else if ((now_time.tm_mday) < (this->m_FestArray[ret]->m_day))
			{
				DaysToFestival = ((SecondstoFestival - SecondstoNow) / 3600) / 24;
				cout << "���վ�������Ϊ" << DaysToFestival + 1 << "��!" << endl;
			}
		}
		else {
			DaysToFestival = ((SecondstoFestival - SecondstoNow) / 3600) / 24;
			cout << "���վ�������Ϊ" << DaysToFestival + 1 << "��!" << endl;
		}
	}
	else {
		cout << "����ʧ�ܣ��޴˽��ռ�¼" << endl;
	}
	//�������������
	system("pause");
	system("cls");
}

//���Ҿ������
void ControllerFestival::Find_Fest() {
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else {
		string name;
		int ret = this->IsExist(name);
		if (ret != -1) {
			//�ҵ�����
			cout << "���ҳɹ�" << endl;
			this->m_FestArray[ret]->showInfo();
		}
		else {
			cout << "����ʧ�ܣ��޴˽��ռ�¼" << endl;
		}
	}
	//�������������
	system("pause");
	system("cls");
}


//�����ͽ�����ʾ
void ControllerFestival::ShowCalender() {
	int DaysofMonth[2][13] = {
		31,28,31,30,31,30,31,31,30,31,30,31,
		31,29,31,30,31,30,31,31,30,31,30,31
	};
	int DaysofWeek = 7;
	int year;
	int month;
	cout << "���������" << endl;
	cin >> year;
	cout << "�������·�" << endl;
	cin >> month;

	int num = firstdayofmonth(year, month);
	if (num == 0)
	{
		num = 7;
	}

	cout << "����һ" << "\t���ڶ�" << "\t������" << "\t������" << "\t������" << "\t������" << "\t������" << endl;
	//���������м���
	int line = (num - 1 + DaysofMonth[IsLeapYear(year) - 365][month])/7+1;
	int one = 0;
	int two = 0;
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < DaysofWeek; j++)
		{
			if (one <= DaysofMonth[IsLeapYear(year) - 365][month])
			{
				if (i >= 1 || (i == 0 && j >= num - 1))
				{
					one++;
					cout << one;
				}
				cout << "\t";
			}
		}
		cout << endl;
		for (int j = 0; j < DaysofWeek; j++)
		{
			if (two <= DaysofMonth[IsLeapYear(year) - 365][month])
			{
				if (i >= 1 || (i == 0 && j >= num - 1))
				{
					two++;
					for (int k = 0; k < this->m_FestNum; k++)
					{
						if ((this->m_FestArray[k]->m_month ==month)&& (this->m_FestArray[k]->m_day == two))
						{
							cout << this->m_FestArray[k]->m_name;
						}
					}
				}
				cout << "\t";
			}
		}
		cout << endl;
	}

	//��ӡ����µĽ��գ�û������
	for (int i = 0; i < this->m_FestNum; i++)
	{
		if ((this->m_FestArray[i]->m_month == month)  && (this->m_FestArray[i]->m_day <= DaysofMonth[IsLeapYear(year) - 365][month])&&(this->m_FestArray[i]->m_day>=1))
		{
			cout << "�������ƣ�" << this->m_FestArray[i]->m_name
				<< "\t�����·�" << this->m_FestArray[i]->m_month
				<< "\t��������" << this->m_FestArray[i]->m_day << endl;
		}
	}


	system("pause");
	system("cls");
}

//�ж�һ���µ�һ�����ڼ�
int ControllerFestival::firstdayofmonth(int year,int month)
{
	struct tm timeinfo;
	//int year, month ,day ;
	const char* weekday[] = { "����", "��һ","�ܶ�", "����","����", "����", "����" };
	
	/* ��ȡ��ǰʱ����Ϣ�����޸��û������������Ϣ */
	time_t time_seconds = time(0);
	localtime_s(&timeinfo,&time_seconds);
	timeinfo.tm_year = year - 1900;
	timeinfo.tm_mon = month - 1;
	timeinfo.tm_mday = 1;

	/* ���� mktime: timeinfo->tm_wday  */
	mktime(&timeinfo);
	return timeinfo.tm_wday;
	//printf("��һ���ǣ�%s\n", weekday[timeinfo->tm_wday]);


}