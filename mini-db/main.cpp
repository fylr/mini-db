#include"lexical_analysis.h"
#include"files_processing.h"
#include"core_processing.h"

int main()
{
	string cmd;
	CoreProcessing cp;
	//cmd = "USEDATABASE database;"; cp.Analysis(cmd);
	while (getline(cin, cmd)){
		cp.Analysis(cmd);
	}
	return 0;
}
