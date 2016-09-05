#include"lexical_analysis.h"

LexicalAnalysis::LexicalAnalysis()
{
	mCorrect = true;
}

LexicalAnalysis::LexicalAnalysis(string &str)
{
	mStr = str;
	mCorrect = true;
}

LexicalAnalysis::~LexicalAnalysis()
{

}

void LexicalAnalysis::Analysis()
{
	regex pattern("\\s*([A-Z]+)\\s*.*");       //ȡ�ؼ���
	smatch tmp;
	if (!regex_match(mStr, tmp, pattern)){
		mCorrect = false;
		cout << "������������" << endl;
		CommandHelp(0);
	}
	else{
		mKeyWord = tmp[1];
		if ("USEDATABASE" == mKeyWord)			UseDataBase();
		else if ("USETABLE" == mKeyWord)		UseTable();
		else if ("BACK" == mKeyWord)			Back();
		else if ("CREATEDATABASE" == mKeyWord)	CreateDataBase();
		else if ("CREATETABLE" == mKeyWord)		CreateTable();
		else if ("INSERT" == mKeyWord)			Insert();
		else if ("UPDATE" == mKeyWord)			Update();
		else if ("DELETE" == mKeyWord)          Delete();
		else if ("SELECT" == mKeyWord)          Select();
		else if ("ADD" == mKeyWord)				Add();
		else if ("SAVE" == mKeyWord)			Save();
		else{
			mCorrect = false;
			cout << "������������" << endl;
			CommandHelp(0); 
		}
	}
}

void LexicalAnalysis::CommandHelp(int n)
{
	switch (n)
	{
	case 0:cout << "���������¹ؼ���:USEDATABASE USETABLE BACK CREATEDATABASE CREATETABLE INSTER UPDATE DELETE SELECT ADD SAVE" << endl; break;
	case 1:cout << "��ȷ��ʽ����:USEDATABASE <����>;" << endl; break;
	case 2:cout << "��ȷ��ʽ����:USETABLE <����>;" << endl; break;
	case 3:cout << "��ȷ��ʽ����:BACK;" << endl; break;
	case 4:cout << "��ȷ��ʽ����:CREATEDATABASE <����>;" << endl; break;
	case 5:cout << "��ȷ��ʽ����:CREATETABLE  <����>��<�ֶ���1>  <��������1> , <�ֶ���2>  <��������2> ,��, <�ֶ���10>  <��������10>;" << endl; break;
	case 6:cout << "��ȷ��ʽ����:INSERT [(<�ֶ���1>  [,<�ֶ���2>��])] VALUES (<����1>[, <����2>��]);" << endl; break;
	case 7:cout << "��ȷ��ʽ����:UPDATE SET  <�ֶ���1>=<���ʽ1>  [, <�ֶ���2>=<���ʽ2>]��[WHERE  <����>];" << endl; break;
	case 8:cout << "��ȷ��ʽ����:DELETE  [WHERE  <����> ];" << endl; break;
	case 9:cout << "��ȷ��ʽ����:SELECT  *; " << endl << "SELECT <�ֶ���1> <�ֶ���2>...; " << endl << "SELECT <�ֶ���1> <�ֶ���2>... WHERE <����>;" << endl; break;
	case 10:cout << "��ȷ��ʽ����:ADD <�ֶ���>;" << endl; break;
	case 11:cout << "��ȷ��ʽ����:SAVE;" << endl; break;
	default:cout << "������ĸ�ʽ������" << endl; break;
	}
}

void LexicalAnalysis::UseDataBase()
{
	regex pattern("\\s*USEDATABASE\\s+([^\\s;,:\*\?\<\>\|/\(\)]+)\\s*[;��]\\s*");				//ȡUsedatabase����ĵ�ַ
	smatch tmp;
	if (!regex_match(mStr, tmp, pattern))
	{
		mCorrect = false;
		cout << "�����ʽ����" << endl;
		CommandHelp(1);
	}
	else
	{
		mParameter.push_back(tmp[1]);
	}
}

void LexicalAnalysis::UseTable()
{
	regex pattern("\\s*USETABLE\\s+([^\\s;,:\*\?\<\>\|/\(\)]+)\\s*[;��]\\s*");				//ȡUsetable����ĵ�ַ
	smatch tmp;
	if (!regex_match(mStr, tmp, pattern))
	{
		mCorrect = false;
		cout << "�����ʽ����" << endl;
		CommandHelp(2);
	}
	else
	{
		mParameter.push_back(tmp[1]);
	}
}

void LexicalAnalysis::Back()
{
	regex pattern("\\s*BACK\\s*;\\s*");				
	if (!regex_match(mStr, pattern))
	{
		mCorrect = false;
		cout << "�����ʽ����" << endl;
		CommandHelp(3);
	}
}

void LexicalAnalysis::CreateDataBase()
{
	regex  pattern("\\s*CREATEDATABASE\\s+([^\\s;,:\*\?\<\>\|/\(\)]+)\\s*[;��]\\s*");       //ȡ����
	smatch tmp;
	if (!regex_match(mStr, tmp, pattern)){
		mCorrect = false;
		cout << "�����ʽ����" << endl;
		CommandHelp(4);
	}
	mParameter.push_back(tmp[1]);
}


void LexicalAnalysis::CreateTable()
{
	regex  pattern("\\s*CREATETABLE\\s+([^\\s;,:\*\?\<\>\|/\(\)]+)\\s+\\((\\s*\\S+\\s+[A-Z]+\\s*[,\\)])+\\s*[;��]\\s*"); //ȡ����
	smatch tmp;
	if (!regex_match(mStr, tmp, pattern)){
		mCorrect = false;
		cout << "�����ʽ����" << endl;
		CommandHelp(5);
	}
	else
	{
		mParameter.push_back(tmp[1]);
		regex pattern1("\\s*\\(?(\\S+)\\s+([A-Z]+)\\s*[,\)]");
		string tmpstr = mStr;
		while (regex_search(tmpstr, tmp, pattern1))
		{
			mParameter.push_back(tmp[1]);
			mParameter.push_back(tmp[2]);
			tmpstr = tmp.suffix().str();
		}
	}
	int len = mParameter.size();
	if (len - 1>20){
		mCorrect = false;
		cout << "����ֶ�������10��" << endl;
		CommandHelp(5);
	}
	for (int i = 2; i < len; i += 2)
		if (mParameter[i] != "STRING"&&mParameter[i] != "DATE"&&mParameter[i] != "BOOL"&&mParameter[i] != "NUMBER"){
			mCorrect = false;
			cout << "���ڲ�֧�ֵ���������:" << mParameter[i] << endl;
			cout << "ֻ֧��һ���������ͣ�STRING �ַ��� ;NUMBER ��ֵ��; DATE ������; BOOL ����." << endl;
		}
}

void LexicalAnalysis::Insert()
{
	smatch tmp;
	regex pattern1("\\s*INSERT\\s+VALUES\\s*\\((\\s*'\\s*\\S+\\s*'\\s*[,\\)])+\\s*[;��]\\s*");
	regex pattern2("\\s*INSERT\\s+\\((\\s*\\S+\\s*[,\\)])+\\s+VALUES\\s*\\((\\s*'\\s*\\S+\\s*'\\s*[,\\)])+\\s*[;��]\\s*");
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
		if (rdn > 10){
			mCorrect = false;
			cout << "����ֶ�������10��" << endl;
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
		if (kwn != rdn){
			mCorrect = false;
			cout << "ǰ����������ƥ��" << endl;
		}
		if (rdn > 10){
			mCorrect = false;
			cout << "����ֶ�������10��" << endl;
		}
	}
	else{
		mCorrect = false;
		cout << "�����ʽ����" << endl;
		CommandHelp(6);
	}
}


void LexicalAnalysis::Update()
{


}


void LexicalAnalysis::Delete()
{
	smatch tmp;
	regex pattern1("\\s*DELETE\\s*[;��]\\s*");
	regex pattern2("\\s*DELETE\\s+WHERE\\s+(\\S+)\\s*=\\s*'\\s*(\\S+)\\s*'\\s*;\\s*");
	if (regex_match(mStr, pattern1))
	{
		mParameter.push_back("ALL");
	}
	else if (regex_match(mStr, tmp, pattern2))
	{
		mParameter.push_back("PART");
		mParameter.push_back(tmp[1]);
		mParameter.push_back(tmp[2]);
	}
	else{
		mCorrect = false;
		cout << "�����ʽ����" << endl;
		CommandHelp(8);
	}
}

void LexicalAnalysis::Select()
{

}

void LexicalAnalysis::Add()
{


}

void LexicalAnalysis::Save()
{
	regex pattern("\\s*SAVE\\s*[;��]\\s*");				//ȡUse����ĵ�ַ
	if (!regex_match(mStr, pattern))
	{
		mCorrect = false;
		cout << "�����ʽ����" << endl;
		CommandHelp(11);
	}
}

void LexicalAnalysis::setStr(string& str)
{
	mStr = str;
}

string& LexicalAnalysis::getKeyWord()
{
	return mKeyWord;
}

vector<string>& LexicalAnalysis::getParameter()
{
	return mParameter;
}

bool LexicalAnalysis::Correct()
{
	return mCorrect;
}