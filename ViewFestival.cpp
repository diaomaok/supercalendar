#include <stdexcept>
#include<vector>
#include"ViewFestival.hpp"
using namespace std;
ViewFestival::ViewFestival() {}
ViewFestival::~ViewFestival() {}
void ViewFestival::ShowMenu() {

	cout << "******欢迎使用节日管理系统 *******" << endl;
	cout << "**********0.退出管理程序**********" << endl;
	cout << "**********1.增加指定节日**********" << endl;
	cout << "**********2.删除指定节日**********" << endl;
	cout << "**********3.修改指定节日**********" << endl;
	cout << "**********4.显示节日月历**********" << endl;
	cout << "**********5.显示节日日期**********" << endl;
	cout << "**********6.查询距今天数**********" << endl;
	cout << "**********7.查询具体节日**********" << endl;
	cout << "**********8.查询节日排序**********" << endl;
	cout << "**********************************" << endl;

}

