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


// д��������
int OperateAccept::WriteOut(std::string result)
{
	std::cout << result << std::endl;
	return 0;
}
