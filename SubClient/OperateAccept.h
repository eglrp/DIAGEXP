#ifndef OPERATEACCEPT_MACRO
#define OPERATEACCEPT_MACRO

#include "BasicSupport.h"


class OperateAccept
{
public:
	OperateAccept();
	virtual ~OperateAccept();

	virtual int GetAGroupMsg(char* msgGroupsSpliter);
};

#endif