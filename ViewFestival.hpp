#pragma once
#ifndef ViewFestival_hpp
#define ViewFestival_hpp
#include<iostream>
#include<string>
using namespace std;

class ViewFestival
{
	friend class ControllerFestival;
public:
	ViewFestival();
	~ViewFestival();
	void ShowMenu();
	//void PrintDate(int y, int m, int md, int ow, int mt);
	//年 月 日 当前这个月的星期 总的天数	
private:
};
#endif