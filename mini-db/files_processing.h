//文件处理类的定义
#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<io.h>
#include<direct.h>

using namespace std;

class FilesProcessing
{
public:
	static void ChangePath(string path_name="");

	static void CreateFolder(string dir_name);

	static void DeleteFolder(string dir_name);

	static void Rename(string pre_name, string new_name);
	
	static void ShowAllFiles();

//	static void WriteTxt(string name, vector<string> &record,bool isapp=false);

//	static void ReadTxt(string name, vector<string> &record);

	static void WriteTableHeader(int keywordnum, int recordnum, vector<vector<string> >& table, vector<string>& datatype);
		  
	static void WriteTableRecord(int keywordnum, vector<vector<string> >& table, vector<int>& poslist);

	static void WriteTableIndexes();

	static void ReadTableHeader(int &keywordnum, int &recordnum, vector<vector<string> >& table, vector<string>& datatype);

	static void ReadTableRecord(int keywordnum, int recordnum, vector<vector<string> >& table, vector<int>& poslist);

	static void ReadTableIndexes();
};
 