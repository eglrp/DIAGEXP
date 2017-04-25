#include "ModelProcessor.h"

using namespace std;

#define OPERATE_WORDS 0
#define CONDITION 1
#define SUPPLEMENT 2


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

 
/*“增加”操作统一处理
COMMANDLINE ADD
	MODULE_ADD :		(NONE;)				module_id = sdf; module_type = sfsfdf;
	BRANCH_ADD:			(module_id = sdf;)	branch_id = adfd;
	VARIABLE_ADD:		(module_id = sdf;)	variable_id = asdf; type = asdkfj; accessablily = sdfsf;
	RELATE_ADD:			(NONE;)				relate_id = asdf; branch = sdfddf; from = adkjfl; to = alflskd;
RESULT:
	SUCCESS:S3 key and value
	ERROR : what and why
*/
int ModelProcessor::_add(std::string cmdline)
{
	string operate_words = " ";
	this->_parse_cmd_line(cmdline, OPERATE_WORDS, "", &operate_words);

	if (operate_words.find("MODULE") != string::npos) {
		string module_id,module_type;
		this->_parse_cmd_line(cmdline, SUPPLEMENT, "module_id", &module_id);
		this->_parse_cmd_line(cmdline, SUPPLEMENT, "module_type", &module_type);

		TiXmlElement* elm=nullptr;
		do {
			this->modelptr->LocateModule(module_id.c_str(), &elm);//elm为null，表明没有满足要求的节点
			if (elm != NULL) {//已存在该节点，换一个id重新搜索
				// 特殊处理
				stringstream buf;
				buf << rand();
				module_id = module_id + buf.str();
			}
		}while (elm != NULL);

		// 添加节点



	}
	else if (operate_words.find("BRANCH") != string::npos) {

	}
	else if (operate_words.find("VARIABLE") != string::npos) {

	}
	else if (operate_words.find("RELATE") != string::npos) {

	}

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


// 将数据模型另存为数据文件，如果输入参数为空，表示保存到原文件
int ModelProcessor::_save_as(std::string filePath)
{
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
		else if (operate_words.find("SAVE_AS") != string::npos) {
			this->_save_as(cmdline);
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


// 根据输入选择性的提取值，如果输入命令没有值，返回nullptr
int ModelProcessor::_parse_cmd_line(std::string cmdline, int kind, std::string key, std::string* value)
{
	switch (kind)
	{
	case OPERATE_WORDS:
		*value = cmdline.substr(0, cmdline.find(":"));
		break;

	case CONDITION: {
			string condition_array = cmdline.substr(cmdline.find("(") + 1, cmdline.find(")")- cmdline.find("(")-1);
			
			if (condition_array == "NONE;") {
				*value = nullptr;
				return 0;
			}

			if (condition_array.find(key) == string::npos) {
				*value = nullptr;
				return -1;
			}

			string contain_val = condition_array.substr(condition_array.find(key));
			string val = contain_val.substr(contain_val.find("=")+1, contain_val.find(";")- contain_val.find("=")-1);

			*value = val;
		}
		break;

	case SUPPLEMENT: {
			string supplement = cmdline.substr(cmdline.find(")") + 1);

			if (supplement == "NONE;") {
				*value = nullptr;
				return 0;
			}

			if (supplement.find(key) == string::npos) {
				*value = nullptr;
				return -1;
			}

			string contain_val = supplement.substr(supplement.find(key));
			string val = contain_val.substr(contain_val.find("=")+1, contain_val.find(";")- contain_val.find("=") - 1);

			*value = val;
		}
		break;
	}

	return 0;
}
