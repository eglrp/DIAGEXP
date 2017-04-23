#include "OperateAccept.h"



OperateAccept::OperateAccept()
{
}


OperateAccept::~OperateAccept()
{
}



// 从标准输入获取一条调用命令
int OperateAccept::GetOneLine(std::string* cmdline)
{
	std::cin >> *cmdline;
	return 0;
}
