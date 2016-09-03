#pragma once
//�ʷ�������Ķ���
#include<iostream>
#include<string>
#include<regex>

using namespace std;

class LexicalAnalysis
{
public:
	LexicalAnalysis(string str);

	~LexicalAnalysis();

	void Analysis();		//�ж��Ƿ�Ϸ�������������

	void CommandHelp(int n);		//��ʾ����Ƿ����ṩ�����ʽ����

	void Use();

	void Back();

	void CreateDataBase();

	void CreateTable();

	void Inster();

	void Update();

	void Delete();

	void Select();

	void Add();

	void Save();

private:
	string mStr;			//Ҫ������ַ���
	string mKeyWord;		//�ؼ���
	vector<string>  mParameter;	//������
	bool mCorrect;			//�����Ƿ�Ϸ�
};