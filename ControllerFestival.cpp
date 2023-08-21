#include<iostream>
#include<ctime>
#include"ControllerFestival.hpp"
#include"ViewFestival.hpp"
using namespace std;


ControllerFestival::ControllerFestival()
{
	//1.文件不存在
	ifstream ifs;
		//读文件
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		//初始化属性
		//初始化记录节日数量
		this->m_FestNum = 0;
		//初始化数组指针
		this->m_FestArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2.文件存在，但是没有数据
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		//cout << "文件为空" << endl;
		//初始化属性
		//初始化记录节日数量
		this->m_FestNum = 0;
		//初始化数组指针
		this->m_FestArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在，并且记录数据
	int num = this->getFestNum();
	cout << "已有节日个数为：" << num << endl;
	this->m_FestNum = num;
	//开辟空间
	this->m_FestArray = new Festival * [this->m_FestNum];
	//将文件中的数据存到数组中
	this->initFest();

	//初始化属性
	//this->m_FestNum = 0;
	//this->m_FestArray = NULL;
}


void ControllerFestival::SaveFestival()
{
	ofstream ofs;
	//用输出的方式打开文件——写文件
	ofs.open(FILENAME, ios::out);
	
	//将每个节日的信息写入到文件中
	for (int i = 0; i < this->m_FestNum; i++)
	{
		ofs << this->m_FestArray[i]->m_name << " "
			<< this->m_FestArray[i]->m_month << " "
			<< this->m_FestArray[i]->m_day << endl;
	}

	//关闭文件
	ofs.close();

}

//统计文件中节日数量
int ControllerFestival::getFestNum()
{
	ifstream ifs;
	//打开文件 读取
	ifs.open(FILENAME, ios::in);
	string name;
	int month;
	int day;

	int num = 0;
	while (ifs >> name && ifs >> month && ifs >> day)
	{
		//统计人数变量
		num++;
	}
	return num;
}

//初始化节日
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
	//关闭文件
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
//添加节日
void ControllerFestival::AddFest()
{
	cout << "请输入添加节日数量:" << endl;
	int addNum = 0;//保存用户输入数量
	cin >> addNum;
	if (addNum > 0)
	{
		//添加
		//计算添加新空间大小
		int newSize = this->m_FestNum + addNum;
		//开辟新空间
		Festival** newSpace = new Festival * [newSize];
		//将原来空间下数据，拷贝到新空间下
		if (this->m_FestArray != NULL) {
			for (int i = 0; i < this->m_FestNum; i++) {
				newSpace[i] = this->m_FestArray[i];
			}
		}
		//添加新数据
		for (int i = 0; i < addNum; i++) {
			int fFormat;
			string fName;
			int fMonth;
			int fOrdNum = -1;//!!fesitval需要添加!!
			int fDay;

			cout << "请输入第" << i + 1 << "个新节日的形式（0：月日型；1：正数星期型 2：倒数星期型）" << endl;
			cin >> fFormat;

			Festival* festival = NULL;
			bool judgename=true;
			switch (fFormat) {
			case 0: {
				cout << "请输入第" << i + 1 << "个新节日的节日名" << endl;
				cin >> fName;

				//判断节日是否重复
				while (judgename == true)
				{
					for (int i = 0; i < this->m_FestNum; i++)
					{
						if (this->m_FestArray[i]->m_name == fName)
						{
							judgename = false;
							cout << "节日已经存在，请重新输入节日名称" << endl;
							cin >> fName;
						}
					}
				}
				

				cout << "请输入第" << i + 1 << "个新节日的月份" << endl;
				cin >> fMonth;
				cout << "请输入第" << i + 1 << "个新节日的日期" << endl;
				cin >> fDay;

				festival = new DateFestival(fFormat, fName, fMonth, fOrdNum, fDay);
				break;
			}
			default:
			{cout << "您输入的节日形式有误，请重新输入" << endl;
			system("pause");
			system("cls");

			break; }
			}
			//将创建并保存在数组中
			newSpace[this->m_FestNum + i] = festival;


		}
		//释放原有的空间
		delete[]this->m_FestArray;
		//更改新空间的指向
		this->m_FestArray = newSpace;
		//更新新的节日数
		this->m_FestNum = newSize;

		//成功添加后 保存到文件中
		SaveFestival();

		//更新节日不为空标志
		this->m_FestNum = newSize;
		//提示成功添加
		cout << "成功添加" << addNum << "个新节日!" << endl;
		m_FileIsEmpty = false;
	}
	else { cout << "输入数量有误" << endl; }
	//按任意键清屏，回到上级目录
	system("pause");
	system("cls");
}
void ControllerFestival::ExitSystem()
{
	cout << "欢迎下次使用!" << endl;
	system("pause");
	exit(0);
}

//显示节日
void ControllerFestival::Show_Fest() {
	//判断文件是否为空
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		for (int i = 0; i < m_FestNum; i++) {
			//利用多态调用程序接口
			this->m_FestArray[i]->showInfo();
		}

	}
	//按任意键后清屏
	system("pause");
	system("cls");
}

//删除节日
void ControllerFestival::Del_Fest() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或为空！" << endl;
	}
	else {
		//按照节日名删除
		cout << "请输入想要删除的节日名" << endl;
		string dname = "";
		cin >> dname;
		int index = this->IsExist(dname);
		if (index != -1)//说明节日存在
		{
			//数据前移
			for (int i = index; i < this->m_FestNum - 1; i++) {
				this->m_FestArray[i] = this->m_FestArray[i + 1];

			}
			this->m_FestNum--;//更新数组中记录的节日个数
			//数据同步更新到文件中
			this->SaveFestival();
			cout << "删除成功!" << endl;
		}
		else
		{
			cout << "删除失败，未找到该节日" << endl;
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}
//判断节日是否存在，如果存在返回节日所在数组中的位置，不存在返回-1
int ControllerFestival::IsExist(string name) {
	int index = -1;
	for (int i = 0; i < this->m_FestNum; i++) {
		if (this->m_FestArray[i]->m_name == name) {
			//找到节日
			index = i;
			break;
		}
	}
	return index;
}



//修改节日
void ControllerFestival::Mod_Fest()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入修改节日的名称：" << endl;
		string name;
		cin >> name;
		int ret = this->IsExist(name);
		if (ret != -1)
		{
			//查找到该节日
			delete this->m_FestArray[ret];
			int format = 0;
			int newMonth = 0;
			int newordnum = 0;
			int newDay = 0;
			Festival* festival = NULL;
			cout << "查到" << name << "，请输入节日新形式，月份和日期：" << endl;
			cout << "形式：（0,表示月日；1，每月正数几周的周几；2，每月倒数几周的周几）" << endl;
			cin >> format;
			if (format == 0)
			{
			cout << "月份" << endl;
			cin >> newMonth;
			cout << "日期" << endl;
			cin >> newDay;
			festival = new DateFestival(0, name, newMonth, -1, newDay);
			}
			else if(format == 1)
			{
				cout << "月份" << endl;
				cin >> newMonth;
				cout << "正数第几周" << endl;
				cin >> newordnum;
				cout << "周几" << endl;
				cin >> newDay;
			}
			else if (format == 2)
			{
				cout << "月份" << endl;
				cin >> newMonth;
				cout << "倒数第几周" << endl;
				cin >> newordnum;
				cout << "周几" << endl;
				cin >> newDay;
			}
			else
			{
				cout << "错误形式" << endl;
				system("cls");
			}
			//更新数据到数组中
			this->m_FestArray[ret] = festival;
			cout << "修改成功" << endl;
			//保存到文件中
			this->SaveFestival();
		}
		else
		{
			cout << "修改失败，无此节日" << endl;

		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//查询时间区间内节日排序
void ControllerFestival::Sort_Fest()
{
	//int startyear = 0;
	int startmonth = 0;
	int startday = 0;
	//int endyear = 0;
	int endmonth = 0;
	int endday = 0;
	int form;
	cout << "请输入时间区间" << endl;
	//cout << "起始年：" << endl;
	//cin >> startyear;
	cout << "起始月：" << endl;
	cin >> startmonth;
	cout << "起始日：" << endl;
	cin >> startday;
	//cout << "终止年：" << endl;
	//cin >> endyear;
	cout << "终止月：" << endl;
	cin >> endmonth;
	cout << "终止日：" << endl;
	cin >> endday;

	//判断输入的日期是否合理


	cout << "请输入排序方式：（1：按日期升序；2：按名称升序）" << endl;
	cin >> form;

	//日期升序
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
				cout << "节日名称：" << this->m_FestArray[i]->m_name
					<< "\t节日月份" << this->m_FestArray[i]->m_month
					<< "\t节日日期" << this->m_FestArray[i]->m_day << endl;
			}
		}
	}
	//名称升序
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
				cout << "节日名称：" << this->m_FestArray[i]->m_name
					<< "\t节日月份" << this->m_FestArray[i]->m_month
					<< "\t节日日期" << this->m_FestArray[i]->m_day << endl;

			}
		}
	}
	else
	{
		cout << "输入有误，请重新输入" << endl;
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
//计算距今天数
void ControllerFestival::FestivalToNow() {
	//计算1970.1.1距今秒数
	time_t SecondstoNow;
	SecondstoNow = time(NULL);
	//得到今天时间结构体
	struct tm now_time;
	time_t time_seconds = time(0);
	localtime_s(&now_time, &time_seconds);
	int DaysToFestival;
	//设置基准日为1月1日
	struct tm basis_time;
	int SecondstoBasis;
	basis_time.tm_year = now_time.tm_year;
	basis_time.tm_mon = 0;
	basis_time.tm_mday = 1;
	basis_time.tm_hour = 0;
	basis_time.tm_min = 0;
	basis_time.tm_sec = 1;
	basis_time.tm_isdst = -1;
	//得到基准日秒数
	SecondstoBasis = mktime(&basis_time);
	//得到节日结构体
	string name;
	cout << "请输入查询的节日名称:" << endl;
	cin >> name;
	//查找节日
	int ret = this->IsExist(name);
	if (ret != -1) {
		//找到节日
		cout << "查找成功" << endl;
		//将节日数据存进结构体tm
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
			cout << "节日距今的天数为" << DaysToFestival + 1 << "天!" << endl;
		}
		else if ((now_time.tm_mon) == (this->m_FestArray[ret]->m_month)) {
			if ((now_time.tm_mday) == (this->m_FestArray[ret]->m_day))
			{
				cout << "节日距今的天数为0天，节日在今天！" << endl;
			}
			else if ((now_time.tm_mday) > (this->m_FestArray[ret]->m_day))
			{
				DaysToFestival = (this->IsLeapYear(now_time.tm_year) - (SecondstoNow - SecondstoBasis) / 3600 / 24) + (SecondstoFestival - SecondstoBasis) / 3600 / 24;
				cout << "节日距今的天数为" << DaysToFestival + 1 << "天!" << endl;
			}
			else if ((now_time.tm_mday) < (this->m_FestArray[ret]->m_day))
			{
				DaysToFestival = ((SecondstoFestival - SecondstoNow) / 3600) / 24;
				cout << "节日距今的天数为" << DaysToFestival + 1 << "天!" << endl;
			}
		}
		else {
			DaysToFestival = ((SecondstoFestival - SecondstoNow) / 3600) / 24;
			cout << "节日距今的天数为" << DaysToFestival + 1 << "天!" << endl;
		}
	}
	else {
		cout << "查找失败，无此节日记录" << endl;
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}

//查找具体节日
void ControllerFestival::Find_Fest() {
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		string name;
		int ret = this->IsExist(name);
		if (ret != -1) {
			//找到节日
			cout << "查找成功" << endl;
			this->m_FestArray[ret]->showInfo();
		}
		else {
			cout << "查找失败，无此节日记录" << endl;
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}


//日历和节日显示
void ControllerFestival::ShowCalender() {
	int DaysofMonth[2][13] = {
		31,28,31,30,31,30,31,31,30,31,30,31,
		31,29,31,30,31,30,31,31,30,31,30,31
	};
	int DaysofWeek = 7;
	int year;
	int month;
	cout << "请输入年份" << endl;
	cin >> year;
	cout << "请输入月份" << endl;
	cin >> month;

	int num = firstdayofmonth(year, month);
	if (num == 0)
	{
		num = 7;
	}

	cout << "星期一" << "\t星期二" << "\t星期三" << "\t星期四" << "\t星期五" << "\t星期六" << "\t星期日" << endl;
	//计算日历有几行
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

	//打印这个月的节日（没有排序）
	for (int i = 0; i < this->m_FestNum; i++)
	{
		if ((this->m_FestArray[i]->m_month == month)  && (this->m_FestArray[i]->m_day <= DaysofMonth[IsLeapYear(year) - 365][month])&&(this->m_FestArray[i]->m_day>=1))
		{
			cout << "节日名称：" << this->m_FestArray[i]->m_name
				<< "\t节日月份" << this->m_FestArray[i]->m_month
				<< "\t节日日期" << this->m_FestArray[i]->m_day << endl;
		}
	}


	system("pause");
	system("cls");
}

//判断一个月第一天星期几
int ControllerFestival::firstdayofmonth(int year,int month)
{
	struct tm timeinfo;
	//int year, month ,day ;
	const char* weekday[] = { "周日", "周一","周二", "周三","周四", "周五", "周六" };
	
	/* 获取当前时间信息，并修改用户输入的输入信息 */
	time_t time_seconds = time(0);
	localtime_s(&timeinfo,&time_seconds);
	timeinfo.tm_year = year - 1900;
	timeinfo.tm_mon = month - 1;
	timeinfo.tm_mday = 1;

	/* 调用 mktime: timeinfo->tm_wday  */
	mktime(&timeinfo);
	return timeinfo.tm_wday;
	//printf("那一天是：%s\n", weekday[timeinfo->tm_wday]);


}