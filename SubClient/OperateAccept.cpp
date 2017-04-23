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


// 写出回令结果
int OperateAccept::WriteOut(std::string result)
{
	std::cout << result << std::endl;
	return 0;
}
