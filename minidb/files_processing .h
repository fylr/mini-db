#pragma once
//文件处理类的定义
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<direct.h>

using namespace std;

class FilesProcessing
{
public:
	static void ChangePath(string path_name = "");

	static void CreateFolder(string dir_name);

	static void DeleteFolder(string dir_name);

	static void Rename(string pre_name, string new_name);

	static void WriteTxt(string name, vector<string> &record);

	static void ReadTxt(string name, vector<string> &record);

};
