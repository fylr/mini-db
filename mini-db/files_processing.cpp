#include"files_processing.h"

void FilesProcessing::ChangePath(string path_name)
{
	if (path_name.empty()){
		char path[_MAX_DIR];
		_getcwd(path, _MAX_DIR);
		string path0 = path;
		int tmp = path0.find_last_of("/\\");
		path_name = path0.substr(0, tmp);
	}
	if(_chdir(path_name.c_str()))
		cout << "�����ڸ�Ŀ¼" << endl;
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

void FilesProcessing::ShowAllFiles()
{
	char path[_MAX_DIR];
	_getcwd(path, _MAX_DIR);
	strcat(path, "\\*");
	long handle;                                                //���ڲ��ҵľ��
	vector<string> files;                                   //�����ļ���
	struct _finddata_t fileinfo;                          //�ļ���Ϣ�Ľṹ��
	handle = _findfirst(path, &fileinfo);         //��һ�β���
	if (-1 == handle)
		cout << "�����ڲ��ҵ�Ŀ¼" << endl;
	files.push_back(fileinfo.name);                        //��ӡ���ҵ����ļ����ļ���
	while (!_findnext(handle, &fileinfo))               //ѭ�������������ϵ��ļ���ֱ���Ҳ���������Ϊֹ
	{
		files.push_back(fileinfo.name);
	}
	_findclose(handle);                                      //�����˹رվ��
	if (files.size() <= 2)
		cout << "�������ļ�" << endl;
	else{
		cout << "���������ļ�:" << endl;
		for (int i = 2; i < files.size(); i++)
			cout << files[i] << endl;
	}
}

//void FilesProcessing::WriteTxt(string name, vector<string> &record,bool isapp)
//{
//	ofstream ptxt;
//	if (isapp)	ptxt.open(name, ios::app);
//	else        ptxt.open(name, ios::out);
//	if (!ptxt.is_open())
//		cout << "д���ļ�������" << endl;
//	int len = record.size();
//	for (int i = 0; i < len; i++)
//		ptxt << record[i] << endl;
//	ptxt.close();
//}

//void FilesProcessing::ReadTxt(string name, vector<string> &record)
//{
//	ifstream gtxt(name, ios::in);
//	if (!gtxt.is_open())
//		cout << "��ȡ�ļ�������" << endl;
//	string tmp;
//	while (getline(gtxt, tmp))
//		record.push_back(tmp);
//	gtxt.close();
//}

void FilesProcessing::WriteTableHeader(int keywordnum, int recordnum, vector<vector<string> >& table, vector<string>& datatype)
{
	ofstream header("��ͷ.txt", ios::out);
	if (!header.is_open())
		cout << "��ͷ�ļ�д�������" << endl;
	else{
		header << keywordnum << " " << recordnum << endl;
		for (int i = 0; i < keywordnum; i++)
			header << table[i][0] << " " << datatype[i] << endl;
		header.close();
	}
}

void FilesProcessing::WriteTableRecord(int keywordnum, vector<vector<string> >& table, vector<int>& poslist)
{
	ofstream record("����.txt", ios::out);
	if (!record.is_open())
		cout << "�����ļ�д�������" << endl;
	else{
		int len = poslist.size();
		for (int i = 1; i < len && poslist[i]; i++)
		{
			for (int j = 0; j < keywordnum - 1; j++)
				record << table[j][i] << " ";
			record << table[keywordnum - 1][i] << endl;
		}
		record.close();
	}
}

void FilesProcessing::WriteTableIndexes()
{

}

void FilesProcessing::ReadTableHeader(int &keywordnum, int &recordnum, vector<vector<string> >& table, vector<string>& datatype)
{
	ifstream header("��ͷ.txt", ios::in);
	if (!header.is_open())
		cout << "��ͷ�ļ���ȡ������" << endl;
	else{
		char str[300];
		header >> keywordnum >> recordnum;
		header.getline(str, 300);
		for (int i = 0; i < keywordnum; i++)
		{
			header.getline(str, 300);
			char *tmp;
			tmp = strtok(str, " ");
			table[i].push_back(tmp);
			tmp = strtok(NULL, " ");
			datatype.push_back(tmp);
		}
	}
}

void FilesProcessing::ReadTableRecord(int keywordnum, int recordnum, vector<vector<string> >& table, vector<int>& poslist)
{
	ifstream record("����.txt", ios::in);
	if (!record.is_open())
		cout << "�����ļ���ȡ������" << endl;
	else{
		char str[2560];
		poslist.push_back(0);
		for (int i = 1; i <= recordnum; i++)
		{
			poslist.push_back(i);
			record.getline(str, 2560);
			char* tmp;
			tmp = strtok(str, " ");
			for (int j = 0; j < keywordnum; j++)
			{
				table[j].push_back(tmp);
				tmp = strtok(NULL, " ");
			}
		}
	}
}

void FilesProcessing::ReadTableIndexes()
{

}

