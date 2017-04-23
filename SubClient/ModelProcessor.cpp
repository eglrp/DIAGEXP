#include "ModelProcessor.h"

using namespace std;


ModelProcessor::ModelProcessor()
	: IOport(nullptr)
{
	modelptr = nullptr;
}


ModelProcessor::~ModelProcessor()
{
}


int ModelProcessor::InitProcessor(DataModel* model, OperateAccept* port)
{
	this->modelptr = model;
	this->IOport = port;
	return 0;
}


// “增加”操作统一处理
int ModelProcessor::_add(std::string cmdline)
{
	this->IOport->WriteOut("add_"+cmdline);
	return 0;
}


// 删除 操作，统一处理
int ModelProcessor::_remove(std::string cmdline)
{
	this->IOport->WriteOut("remove_" + cmdline);
	return 0;
}


int ModelProcessor::_query(std::string cmdline)
{
	this->IOport->WriteOut("query_" + cmdline);
	return 0;
}


int ModelProcessor::_update(std::string cmdline)
{
	this->IOport->WriteOut("update_" + cmdline);
	return 0;
}


// 进入循环消息处理过程
int ModelProcessor::Loop()
{
	string cmdline = "$$Process_Start";

	while (cmdline != PROCESS_EXIT_MSG)
	{
		if (cmdline == "$$Process_Start") {
			this->IOport->GetOneLine(&cmdline);
			continue;
		}
		if (cmdline.find(":") == string::npos || cmdline.find("(") == string::npos || cmdline.find(")") == string::npos)
		{
			this->IOport->WriteOut("ERROR: <" + cmdline + "> Format Error !");
			this->IOport->GetOneLine(&cmdline);
			continue;
		}
		// process msg and writeout the result
		string operate_words = cmdline.substr(0, cmdline.find(":"));

		if (operate_words.find("ADD")!=string::npos)
		{
			this->_add(cmdline);
		}else if (operate_words.find("REMOVE")!=string::npos)
		{
			this->_remove(cmdline);
		}else if (operate_words.find("QUERY")!=string::npos)
		{
			this->_query(cmdline);
		}else if (operate_words.find("UPDATE")!=string::npos)
		{
			this->_update(cmdline);
		}
		else {
			this->IOport->WriteOut("ERROR: <" + cmdline + "> Illegal Operate Error !");
		}

		// turn to the next msg
		this->IOport->GetOneLine(&cmdline);
	}

	this->IOport->WriteOut("$$Process_Exit");

	return 0;
}
