#ifndef OPERATEACCEPT_MACRO
#define OPERATEACCEPT_MACRO

#include "BasicSupport.h"


class OperateAccept
{
public:
	OperateAccept();
	virtual ~OperateAccept();

	// �ӱ�׼�����ȡһ����������
	virtual int GetOneLine(std::string* cmdline);
	// д��������
	virtual int WriteOut(std::string result);
};

#endif