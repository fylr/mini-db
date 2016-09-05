#include"table.h"

Table::Table()
{
	mKeyWordNum = 0;
	mRecordNum = 0;
}

Table::~Table()
{

}

void Table::CreateTable(vector<string>& parameter)
{
	mFP_util.CreateFolder(parameter[0]);
	mKeyWordNum = (parameter.size() - 1) / 2;
	mTable.resize(mKeyWordNum);
	for (int i = 0; i < mKeyWordNum; i++)
	{
		mTable[i].push_back(parameter[2 * i + 1]);
		mDataType.push_back(parameter[2 * i + 2]);
	}
	mPosList.push_back(0);
	mFP_util.ShowAllFiles();
}

void Table::UseTable(string name)
{
	mFP_util.ChangePath(name);

	Save();

	mFP_util.ReadTableHeader(mKeyWordNum, mRecordNum, mTable, mDataType);
				
	mFP_util.ReadTableRecord(mKeyWordNum, mRecordNum, mTable, mPosList);
				
	mFP_util.ReadTableIndexes();

}

void Table::Insert(vector<string>& parameter)
{
	if (parameter[0] == "ALL")
	{
		mRecordNum++;
		mPosList.push_back(mRecordNum);
		for (int i = 0; i < mKeyWordNum; i++)
			mTable[i].push_back(parameter[i + 1]);
	}
	if (parameter[0] == "PART")
	{
		int len = (parameter.size() - 1) / 2;
		vector<int> tmp;
		for (int i = 0; i < len; i++)
		{
			int pos;
			for (pos = 0; pos < mKeyWordNum && parameter[i + 1] != mTable[pos][0]; pos++);
			if (pos == mKeyWordNum)
				cout << "表头中不存在字段'" << parameter[i + 1] << "'" << endl;
			else  tmp.push_back(pos);
		}
		mRecordNum++;
		mPosList.push_back(mRecordNum);
		for (int i = 0; i < tmp.size(); i++)
			mTable[tmp[i]].push_back(parameter[len + i + 1]);
		for (int i = 0; i < mKeyWordNum; i++)
			if (mTable[i].size() < mPosList.size())
				mTable[i].push_back("*");
	}
}

void Table::Update(vector<string>& parameter)
{

}

void Table::Delete(vector<string>& parameter)
{
	if (parameter[0] == "ALL")
	{
		mRecordNum = 0;
		for (int i = 1; i < mPosList.size(); i++)
			mPosList[i] = 0;
	}
	if (parameter[0] == "PART")
	{
		int pos;
		for (pos = 0; pos < mKeyWordNum && parameter[1] != mTable[pos][0]; pos++);
		if (pos == mKeyWordNum)
			cout << "表头中不存在字段'" << parameter[1] << "'" << endl;
		else
		{
			int cnt = 0;
			for (int i = 0; i < mPosList.size(); i++)
			{
				if (mPosList[i] && mTable[pos][i] == parameter[2])
					mPosList[i] = 0, cnt++;
			}
			if (!cnt)
				cout << "表中不存在满足该条件的记录" << endl;
			else  mRecordNum -= cnt;
		}
	}
}

void Table::Select(vector<string>& parameter)
{

}

void Table::Add(vector<string>& parameter)
{

}

void Table::Save()
{
	//写表头
	mFP_util.WriteTableHeader(mKeyWordNum, mRecordNum, mTable, mDataType);
	//写数据记录
	mFP_util.WriteTableRecord(mKeyWordNum, mTable, mPosList);
	//写索引
	mFP_util.WriteTableIndexes();
}