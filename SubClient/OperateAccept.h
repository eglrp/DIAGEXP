#pragma once
#include <iostream>


class OperateAccept
{
public:
	OperateAccept();
	virtual ~OperateAccept();

	virtual int GetAGroupMsg(char* msgGroupsSpliter);
};

