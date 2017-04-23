#ifndef OPERATEACCEPT_MACRO
#define OPERATEACCEPT_MACRO

#include "BasicSupport.h"


class OperateAccept
{
public:
	OperateAccept();
	virtual ~OperateAccept();

	// 从标准输入获取一条调用命令
	virtual int GetOneLine(std::string* cmdline);
	// 写出回令结果
	virtual int WriteOut(std::string result);
};

#endif