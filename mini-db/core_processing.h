//核心处理类的定义
#pragma once
#include<iostream>
#include"table.h"
#include<ctime>
#include"lexical_analysis.h"

using namespace std;

class CoreProcessing:public Table
{
public:
	CoreProcessing();

	~CoreProcessing();

	void Analysis(string& cmd);

	void UseDataBase(string name);

	void Back();

	void CreateDataBase(string name);

	void ReadLog(string name);
private:
	LexicalAnalysis mLA_util;
	string mStartTime;
	ofstream mLog;
};