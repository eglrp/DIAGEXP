#include "OperateAccept.h"



OperateAccept::OperateAccept()
{
}


OperateAccept::~OperateAccept()
{
}



// �ӱ�׼�����ȡһ����������
int OperateAccept::GetOneLine(std::string* cmdline)
{
	std::cin >> *cmdline;
	return 0;
}
