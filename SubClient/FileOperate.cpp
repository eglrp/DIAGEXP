#include "FileOperate.h"

using namespace std;

FileOperate::FileOperate()
{
}


FileOperate::~FileOperate()
{
}


// 确保procrule文件存在，如果传入空路径，则新建一个默认格式空文件，返回值表明原位置文件是否存在
int FileOperate::EnsureProcFileExist(char* procFilePath)
{
	int ret = 0;
	fstream tfile;

	tfile.open(procFilePath);
	if (!tfile.is_open()) {
		ret = -1;

		tfile.open(procFilePath, ios::out);

		tfile
			<< "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
			<< "<" <<DOC_ROOT_ELM_TAG<<" "<<MAINMODULE_TAG<<"=\"unknown\" "<<PROCESSRULE_VERSION_TAG<<"=\""<<PROCESSRULE_VERSION<<"\">"
			<< "<" << MODULE_COLLECTION_TAG << ">"
			<< "</"<< MODULE_COLLECTION_TAG << ">"
			<< "<" << RELATE_COLLECTION_TAG << ">"
			<< "</"<< RELATE_COLLECTION_TAG << ">"
			<< "</"<<DOC_ROOT_ELM_TAG<<">";
	}

	tfile.close();
	return ret;
}
