#ifndef FILEOPERATE_MACRO
#define FILEOPERATE_MACRO

#include "BasicSupport.h"

class FileOperate
{
public:
	FileOperate();
	virtual ~FileOperate();
	// ȷ��procrule�ļ����ڣ���������·�������½�һ��Ĭ�ϸ�ʽ���ļ�������ֵ����ԭλ���ļ��Ƿ����
	// ����ֵ���壺0��	�ļ�����
	//				-1���ļ������ڣ��½��հ��ļ�
	virtual int EnsureProcFileExist(char* procFilePath);
};

#endif 