//基本数据结构的定义
#include<iostream>
#include<vector>
using namespace std;

class Table
{
public:
	int mKeyWordNum;
	int mRecordNum;
	vector<vector<string> > mTable;
	vector<string> mDataType;
	vector<bool> mPosList;
};

