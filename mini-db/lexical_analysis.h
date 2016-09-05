//�ʷ�������Ķ���
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

	void Analysis();		//�ж��Ƿ�Ϸ�������������

	void CommandHelp(int n);		//��ʾ����Ƿ����ṩ�����ʽ����

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
	string mStr;			//Ҫ������ַ���
	string mKeyWord;		//�ؼ���
	vector<string> mParameter;	//������
	bool mCorrect;			//�����Ƿ�Ϸ�
};
