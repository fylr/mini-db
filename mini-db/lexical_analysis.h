//词法分析类的定义
#pragma once
#include<iostream>
#include<string>
#include<regex>

using namespace std;

class LexicalAnalysis
{
public:
	LexicalAnalysis();

	LexicalAnalysis(string &str);

	~LexicalAnalysis();

	void Analysis();		//判断是否合法，并归类命令

	void CommandHelp(int n);		//显示输入非法并提供命令格式帮助

	void UseDataBase();

	void UseTable();

	void Back();

	void CreateDataBase();

	void CreateTable();

	void Insert();

	void Update();

	void Delete();

	void Select();

	void Add();

	void Save();

	void setStr(string &str);

	string& getKeyWord();

	vector<string>& getParameter();

	bool Correct();
private:
	string mStr;			//要处理的字符串
	string mKeyWord;		//关键字
	vector<string> mParameter;	//参数表
	bool mCorrect;			//输入是否合法
};
