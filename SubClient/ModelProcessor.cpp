#include "ModelProcessor.h"



ModelProcessor::ModelProcessor()
{
	modelptr = nullptr;
}


ModelProcessor::~ModelProcessor()
{
}


int ModelProcessor::InitProcessor(DataModel* model)
{
	this->modelptr = model;
	return 0;
}


// �����ӡ�����ͳһ����
int ModelProcessor::_add(char* cmdline)
{
	return 0;
}


// ɾ�� ������ͳһ����
int ModelProcessor::_remove(char* cmdline)
{
	return 0;
}


int ModelProcessor::_query(char* cmdline)
{
	return 0;
}


int ModelProcessor::_update(char* cmdline)
{
	return 0;
}
