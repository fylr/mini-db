//表类的定义
#pragma once
#include<iostream>
#include<string>
#include"files_processing.h"

using namespace std;

class Table
{
public:
	Table();

	~Table();

	void CreateTable(vector<string>& parameter);

	void UseTable(string name);

	void Insert(vector<string>& parameter);

	void Update(vector<string>& parameter);

	void Delete(vector<string>& parameter);

	void Select(vector<string>& parameter);

	void Add(vector<string>& parameter);

	void Save();

protected:	FilesProcessing mFP_util;

private:
	int mKeyWordNum;
	int mRecordNum;
	vector<vector<string> > mTable;
	vector<string> mDataType;
	vector<int> mPosList;
};