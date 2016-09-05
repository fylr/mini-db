#include"core_processing.h"

CoreProcessing::CoreProcessing()
{
	time_t t = time(NULL);
	char a[64];
	strftime(a, sizeof(a), "%Y_%m_%d", localtime(&t));
	strcat(a, ".txt");
	mStartTime = a;
	mFP_util.ChangePath("logs");
	mLog.open(mStartTime, ios::app);
	if (!mLog.is_open())
		cout << "日志文件创建失败" << endl;
	mFP_util.ChangePath();
	mFP_util.ChangePath("workplace");
	cout << "工作空间下";
	mFP_util.ShowAllFiles();
}

CoreProcessing::~CoreProcessing()
{
	mLog.close();
}

void CoreProcessing::Analysis(string& cmd)
{
	mLog << cmd << endl;
	mLA_util.setStr(cmd);
	mLA_util.Analysis();
	if (mLA_util.Correct())
	{
		string tmp = mLA_util.getKeyWord();
		if ("USEDATABASE" == tmp)				UseDataBase(mLA_util.getParameter()[0]);
		else if ("USETABLE" == tmp)				UseTable(mLA_util.getParameter()[0]);
		else if ("BACK" == tmp)					Back();
		else if ("CREATEDATABASE" == tmp)		CreateDataBase(mLA_util.getParameter()[0]);
		else if ("CREATETABLE" == tmp)			CreateTable(mLA_util.getParameter());
		else if ("INSERT" == tmp)				Insert(mLA_util.getParameter());
		else if ("UPDATE" == tmp)				Update(mLA_util.getParameter());
		else if ("DELETE" == tmp)				Delete(mLA_util.getParameter());
		else if ("SELECT" == tmp)				Select(mLA_util.getParameter());
		else if ("ADD" == tmp)					Add(mLA_util.getParameter());
		else if ("SAVE" == tmp)					Save();
	}
}

void CoreProcessing::UseDataBase(string name)
{
	mFP_util.ChangePath(name);
	cout << "数据库"<<name;
	mFP_util.ShowAllFiles();
}

void CoreProcessing::Back()
{
	mFP_util.ChangePath();
	mFP_util.ShowAllFiles();
}

void CoreProcessing::CreateDataBase(string name)
{
	mFP_util.CreateFolder(name);
	mFP_util.ShowAllFiles();
}

void CoreProcessing::ReadLog(string name)
{

}