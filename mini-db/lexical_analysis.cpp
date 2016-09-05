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
	regex pattern("\\s*([A-Z]+)\\s*.*");       //取关键字
	smatch tmp;
	if (!regex_match(mStr, tmp, pattern)){
		mCorrect = false;
		cout << "该命令不在命令集中" << endl;
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
			cout << "该命令不在命令集中" << endl;
			CommandHelp(0); 
		}
	}
}

void LexicalAnalysis::CommandHelp(int n)
{
	switch (n)
	{
	case 0:cout << "请输入以下关键字:USEDATABASE USETABLE BACK CREATEDATABASE CREATETABLE INSTER UPDATE DELETE SELECT ADD SAVE" << endl; break;
	case 1:cout << "正确格式如下:USEDATABASE <库名>;" << endl; break;
	case 2:cout << "正确格式如下:USETABLE <表名>;" << endl; break;
	case 3:cout << "正确格式如下:BACK;" << endl; break;
	case 4:cout << "正确格式如下:CREATEDATABASE <库名>;" << endl; break;
	case 5:cout << "正确格式如下:CREATETABLE  <表名>（<字段名1>  <数据类型1> , <字段名2>  <数据类型2> ,…, <字段名10>  <数据类型10>;" << endl; break;
	case 6:cout << "正确格式如下:INSERT [(<字段名1>  [,<字段名2>…])] VALUES (<常量1>[, <常量2>…]);" << endl; break;
	case 7:cout << "正确格式如下:UPDATE SET  <字段名1>=<表达式1>  [, <字段名2>=<表达式2>]…[WHERE  <条件>];" << endl; break;
	case 8:cout << "正确格式如下:DELETE  [WHERE  <条件> ];" << endl; break;
	case 9:cout << "正确格式如下:SELECT  *; " << endl << "SELECT <字段名1> <字段名2>...; " << endl << "SELECT <字段名1> <字段名2>... WHERE <条件>;" << endl; break;
	case 10:cout << "正确格式如下:ADD <字段名>;" << endl; break;
	case 11:cout << "正确格式如下:SAVE;" << endl; break;
	default:cout << "您输入的格式有问题" << endl; break;
	}
}

void LexicalAnalysis::UseDataBase()
{
	regex pattern("\\s*USEDATABASE\\s+([^\\s;,:\*\?\<\>\|/\(\)]+)\\s*[;；]\\s*");				//取Usedatabase后面的地址
	smatch tmp;
	if (!regex_match(mStr, tmp, pattern))
	{
		mCorrect = false;
		cout << "命令格式出错" << endl;
		CommandHelp(1);
	}
	else
	{
		mParameter.push_back(tmp[1]);
	}
}

void LexicalAnalysis::UseTable()
{
	regex pattern("\\s*USETABLE\\s+([^\\s;,:\*\?\<\>\|/\(\)]+)\\s*[;；]\\s*");				//取Usetable后面的地址
	smatch tmp;
	if (!regex_match(mStr, tmp, pattern))
	{
		mCorrect = false;
		cout << "命令格式出错" << endl;
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
		cout << "命令格式出错" << endl;
		CommandHelp(3);
	}
}

void LexicalAnalysis::CreateDataBase()
{
	regex  pattern("\\s*CREATEDATABASE\\s+([^\\s;,:\*\?\<\>\|/\(\)]+)\\s*[;；]\\s*");       //取库名
	smatch tmp;
	if (!regex_match(mStr, tmp, pattern)){
		mCorrect = false;
		cout << "命令格式出错" << endl;
		CommandHelp(4);
	}
	mParameter.push_back(tmp[1]);
}


void LexicalAnalysis::CreateTable()
{
	regex  pattern("\\s*CREATETABLE\\s+([^\\s;,:\*\?\<\>\|/\(\)]+)\\s+\\((\\s*\\S+\\s+[A-Z]+\\s*[,\\)])+\\s*[;；]\\s*"); //取表名
	smatch tmp;
	if (!regex_match(mStr, tmp, pattern)){
		mCorrect = false;
		cout << "命令格式出错" << endl;
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
		cout << "表的字段数超过10个" << endl;
		CommandHelp(5);
	}
	for (int i = 2; i < len; i += 2)
		if (mParameter[i] != "STRING"&&mParameter[i] != "DATE"&&mParameter[i] != "BOOL"&&mParameter[i] != "NUMBER"){
			mCorrect = false;
			cout << "存在不支持的数据类型:" << mParameter[i] << endl;
			cout << "只支持一下四种类型：STRING 字符串 ;NUMBER 数值型; DATE 日期型; BOOL 布尔." << endl;
		}
}

void LexicalAnalysis::Insert()
{
	smatch tmp;
	regex pattern1("\\s*INSERT\\s+VALUES\\s*\\((\\s*'\\s*\\S+\\s*'\\s*[,\\)])+\\s*[;；]\\s*");
	regex pattern2("\\s*INSERT\\s+\\((\\s*\\S+\\s*[,\\)])+\\s+VALUES\\s*\\((\\s*'\\s*\\S+\\s*'\\s*[,\\)])+\\s*[;；]\\s*");
	if (regex_match(mStr, pattern1))
	{
		string tmpstr = mStr;
		mParameter.push_back("ALL");		//表示添加全部信息
		regex pattern("'\\s*(\\S+)\\s*'\\s*[,\\)]");
		while (regex_search(tmpstr, tmp, pattern))
		{
			mParameter.push_back(tmp[1]);
			tmpstr = tmp.suffix().str();
		}
		int rdn = mParameter.size() - 1;
		if (rdn > 10){
			mCorrect = false;
			cout << "表的字段数超过10个" << endl;
		}
	}
	else if (regex_match(mStr, pattern2))
	{
		string tmpstr = mStr;
		mParameter.push_back("PART");		//表示添加部分信息
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
			cout << "前后项数量不匹配" << endl;
		}
		if (rdn > 10){
			mCorrect = false;
			cout << "表的字段数超过10个" << endl;
		}
	}
	else{
		mCorrect = false;
		cout << "命令格式出错" << endl;
		CommandHelp(6);
	}
}


void LexicalAnalysis::Update()
{


}


void LexicalAnalysis::Delete()
{
	smatch tmp;
	regex pattern1("\\s*DELETE\\s*[;；]\\s*");
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
		cout << "命令格式出错" << endl;
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
	regex pattern("\\s*SAVE\\s*[;；]\\s*");				//取Use后面的地址
	if (!regex_match(mStr, pattern))
	{
		mCorrect = false;
		cout << "命令格式出错" << endl;
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