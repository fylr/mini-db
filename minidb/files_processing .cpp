#include"files_processing .h"

void FilesProcessing::ChangePath(string path_name)
{
	if (path_name.empty()) {
		char path[_MAX_DIR];
		_getcwd(path, _MAX_DIR);
		string path0 = path;
		int tmp = path0.find_last_of("/\\");
		path_name = path0.substr(0, tmp);
	}
	_chdir(path_name.c_str());
}

void FilesProcessing::CreateFolder(string dir_name)
{
	_mkdir(dir_name.c_str());
}

void FilesProcessing::DeleteFolder(string dir_name)
{
	_rmdir(dir_name.c_str());
}

void FilesProcessing::Rename(string pre_name, string new_name)
{
	rename(pre_name.c_str(), new_name.c_str());
}

void FilesProcessing::WriteTxt(string name, vector<string> &record)
{
	ofstream ptxt(name, ios::out);
	if (!ptxt.is_open())
		cout << "写入文件出错！！" << endl;
	int len = record.size();
	for (int i = 0; i < len; i++)
		ptxt << record[i] << endl;
	ptxt.close();
}
void FilesProcessing::ReadTxt(string name, vector<string> &record)
{
	ifstream gtxt(name, ios::in);
	if (!gtxt.is_open())
		cout << "读取文件出错！！" << endl;
	string tmp;
	while (getline(gtxt, tmp))
		record.push_back(tmp);
	gtxt.close();
}