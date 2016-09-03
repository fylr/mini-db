#include"lexical_analysis.h"
LexicalAnalysis::LexicalAnalysis(string str)
{
	mStr = str;
	mCorrect = true;
}

LexicalAnalysis::~LexicalAnalysis()
{
}

void LexicalAnalysis::Analysis()
{
	regex pattern("\\s*([A-Z]+)\\s.*");       //ȡ�ؼ���
	smatch tmp;
	if (!regex_match(mStr, tmp, pattern)) {
		cout << "������������" << endl;
		CommandHelp(0);
	}
	else {
		mKeyWord = tmp[1];
		if ("USE" == mKeyWord)					Use();
		else if ("BACK" == mKeyWord)			Back();
		else if ("CREATEDATEBASE" == mKeyWord)	CreateDataBase();
		else if ("CREATETABLE" == mKeyWord)		CreateTable();
		else if ("INSTER" == mKeyWord)			Inster();
		else if ("UPDATE" == mKeyWord)			Update();
		else if ("DELETE" == mKeyWord)          Delete();
		else if ("SELECT" == mKeyWord)          Select();
		else if ("ADD" == mKeyWord)				Add();
		else if ("SAVE" == mKeyWord)			Save();
		else {
			cout << "������������" << endl;
			CommandHelp(0);
		}
	}
}

void LexicalAnalysis::CommandHelp(int n)
{
	switch (n)
	{
	case 0:cout << "���������¹ؼ��֡�USE BACK CREATEDATABASE CREATETABLE INSTER UPDATE DELETE SELECT ADD SAVE��" << endl; break;
	case 1:cout << "��ȷ��ʽ���¡�USE <����>��USE <����>��" << endl; break;
	case 2:cout << "��ȷ��ʽ���¡�USE <����>��USE <����>��" << endl; break;
	case 3:cout << "��ȷ��ʽ���¡�CREATE DATABASE <����>��<�ֶ���1>  <��������1> , <�ֶ���2>  <��������2> ,��, <�ֶ���n>  <��������n>����" << endl; break;
	case 4:cout << "��ȷ��ʽ���¡�CREATE TABLE  <����>��<�ֶ���1>  <��������1> , <�ֶ���2>  <��������2> ,��, <�ֶ���n>  <��������n>;��" << endl; break;
	case 5:cout << "��ȷ��ʽ���¡�INSERT [(<�ֶ���1>  [,<�ֶ���2>��])]" << endl << "VALUES(<����1>[, <����2>]��);��" << endl; break;
	case 6:cout << "��ȷ��ʽ���¡�UPDATE SET  <�ֶ���1>=<���ʽ1>  [, <�ֶ���2>=<���ʽ2>]��[WHERE  <����>];��" << endl; break;
	case 7:cout << "��ȷ��ʽ���¡�DELETE  [WHERE  <����> ];��" << endl; break;
	case 8:cout << "��ȷ��ʽ���¡�SELECT  *;" << endl << "SELECT <�ֶ���1> <�ֶ���2>..." << endl << "SELECT <�ֶ���1> <�ֶ���2>..." << endl << "WHERE <����>��" << endl; break;
	case 9:cout << "��ȷ��ʽ���¡�ADD <�ֶ���>��" << endl; break;
	case 10:cout << "��ȷ��ʽ���¡�SAVE��" << endl; break;
	default:;
	}
}
/*************************/
void LexicalAnalysis::Use()
{

}
void LexicalAnalysis::Back()
{

}

void LexicalAnalysis::CreateDataBase()
{
	regex  pattern("\\s*CREATEDATABASE\\s+(\\S+)\\s*;");       //ȡ����
	smatch tmp;
	if (!regex_match(mStr, tmp, pattern)) {
		cout << "�����ʽ����" << endl;
		CommandHelp(3);
	}
	mParameter.push_back(tmp[1]);
}


void LexicalAnalysis::CreateTable()
{
	regex  pattern("\\s*CREATETABLE\\s+(\\S+)\\s+\\((\\s*\\S+\\s+[A-Z]+\\s*[,\\)])+\\s*;"); //ȡ����
	smatch tmp;
	if (!regex_match(mStr, tmp, pattern)) {
		cout << "�����ʽ����" << endl;
		CommandHelp(4);
	}
	else
	{
		mParameter.push_back(tmp[1]);
		regex pattern1("\\s*\\(?(\\S+)\\s+([A-Z]+)\\s*.");
		string tmpstr = mStr;
		while (regex_search(tmpstr, tmp, pattern1))
		{
			mParameter.push_back(tmp[1]);
			mParameter.push_back(tmp[2]);
			tmpstr = tmp.suffix().str();
		}
	}
	int len = mParameter.size();
	if (len - 1>20) {
		cout << "����ֶ�������10��" << endl;
		CommandHelp(4);
	}
	for (int i = 2; i < len; i += 2)
		if (mParameter[i] != "STRING"&&mParameter[i] != "DATE"&&mParameter[i] != "BOOL"&&mParameter[i] != "NUMBER") {
			cout << "���ڲ�֧�ֵ���������" << endl;
			CommandHelp(4);
		}
}


void LexicalAnalysis::Inster()
{
	smatch tmp;
	regex pattern1("\\s*INSERT\\s+VALUES\\s*\\((\\s*'\\s*\\S+\\s*'\\s*[,\\)])+\\s*;");
	regex pattern2("\\s*INSERT\\s+\\((\\s*\\S+\\s*[,\\)])+\\s+VALUES\\s*\\((\\s*'\\s*\\S+\\s*'\\s*[,\\)])+\\s*;");
	if (regex_match(mStr, pattern1))
	{
		string tmpstr = mStr;
		mParameter.push_back("ALL");		//��ʾ���ȫ����Ϣ
		regex pattern("'\\s*(\\S+)\\s*'\\s*[,\\)]");
		while (regex_search(tmpstr, tmp, pattern))
		{
			mParameter.push_back(tmp[1]);
			tmpstr = tmp.suffix().str();
		}
		int rdn = mParameter.size() - 1;
		if (rdn > 10) {
			cout << "����ֶ�������10��" << endl;
			CommandHelp(5);
		}
	}
	else if (regex_match(mStr, pattern2))
	{
		string tmpstr = mStr;
		mParameter.push_back("PART");		//��ʾ��Ӳ�����Ϣ
		regex pattern0("\\s*([^''\\s\\(]+)\\s*[,\\)]");
		while (regex_search(tmpstr, tmp, pattern0))
		{
			mParameter.push_back(tmp[1]);
			tmpstr = tmp.suffix().str();
		}
		int kwn = mParameter.size() - 1;
		regex pattern("'\\s*(\\S+)\\s*'\\s*[,\\)]");
		while (regex_search(tmpstr, tmp, pattern))
		{
			mParameter.push_back(tmp[1]);
			tmpstr = tmp.suffix().str();
		}
		int rdn = mParameter.size() - kwn - 1;
		if (kwn != rdn) {
			cout << "ǰ����������ƥ��" << endl;
			CommandHelp(5);
		}
		if (rdn > 10) {
			cout << "����ֶ�������10��" << endl;
			CommandHelp(5);
		}
		//////////////		check(){}//����ͷ�Ƿ���ڸ��ֶ�
	}
	else {
		cout << "�����ʽ����" << endl;
		CommandHelp(5);
	}
}


void LexicalAnalysis::Update()
{


}


void LexicalAnalysis::Delete()
{

}

void LexicalAnalysis::Select()
{

}

void LexicalAnalysis::Add()
{


}

void LexicalAnalysis::Save()
{


}