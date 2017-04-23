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


// “增加”操作统一处理
int ModelProcessor::_add(char* cmdline)
{
	return 0;
}


// 删除 操作，统一处理
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
