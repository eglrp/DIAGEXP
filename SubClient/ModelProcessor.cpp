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
	RELATE_ADD:			(NONE;)				relate_id = asdf; branch_map = sdfddf; from = adkjfl; to = alflskd;
RESULT:
	SUCCESS:S3 key and value
	ERROR : what and why
*/
int ModelProcessor::_add(std::string cmdline)
{
	string operate_words = " ";
	this->_parse_cmd_line(cmdline, OPERATE_WORDS, "", &operate_words);

	if (operate_words.find("MODULE") != string::npos) {
		Add_Module(cmdline);
	}
	else if (operate_words.find("BRANCH") != string::npos) {
		int retval = Add_Branch(cmdline);
		if (retval) return retval;
	}
	else if (operate_words.find("VARIABLE") != string::npos) {
		bool retflag;
		int retval = Add_Variable(cmdline, retflag);
		if (retflag) return retval;
	}
	else if (operate_words.find("RELATE") != string::npos) {
		Add_Relate(cmdline);
	}

	return 0;
}

void ModelProcessor::Add_Relate(std::string &cmdline)
{
	string relate_id, branch_map, from, to;
	this->_parse_cmd_line(cmdline, SUPPLEMENT, "relate_id", &relate_id);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, "branch_map", &branch_map);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, "from", &from);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, "to", &to);

	TiXmlElement* relate = nullptr;
	do {
		this->modelptr->LocateRelate(relate_id.c_str(), &relate);
		if (relate != NULL) {
			stringstream buf;
			buf << rand();
			relate_id += buf.str();
		}
	} while (relate != NULL);

	this->modelptr->AddRelate(relate_id.c_str(), branch_map.c_str(), from.c_str(), to.c_str());
	this->IOport->WriteOut("SUCCESS: <relate_id=" + relate_id + ">");
}

int ModelProcessor::Add_Variable(std::string &cmdline, bool &retflag)
{
	retflag = true;
	string module_id, variable_id, type, accessablily;
	this->_parse_cmd_line(cmdline, CONDITION, "module_id", &module_id);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, "variable_id", &variable_id);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, "type", &type);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, "accessablily", &accessablily);

	TiXmlElement* elm = nullptr;
	this->modelptr->LocateModule(module_id.c_str(), &elm);
	if (elm == NULL) {
		this->IOport->WriteOut("ERROR: <module_id=" + module_id + "> not exist!");
		return -1;
	}

	TiXmlElement* v_elm = nullptr;
	do {
		this->modelptr->LocateVariable(elm, variable_id.c_str(), &v_elm);
		if (v_elm != NULL) {
			stringstream buf;
			buf << rand();
			variable_id += buf.str();
		}
	} while (v_elm != NULL);

	this->modelptr->AddVariable(elm, variable_id.c_str(), type.c_str(), accessablily.c_str());
	this->IOport->WriteOut("SUCCESS: <module_id=" + module_id + ";variable_id=" + variable_id + ">");
	retflag = false;
	return {};
}

int ModelProcessor::Add_Branch(std::string &cmdline)
{
	string module_id, branch_id;
	this->_parse_cmd_line(cmdline, CONDITION, "module_id", &module_id);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, "branch_id", &branch_id);

	TiXmlElement* elm = nullptr;
	this->modelptr->LocateModule(module_id.c_str(), &elm);
	if (elm == NULL) {
		this->IOport->WriteOut("ERROR: <module_id=" + module_id + "> not exist!");
		return -1;
	}
	TiXmlElement* b_elm = nullptr;
	do {
		this->modelptr->LocateBranch(elm, branch_id.c_str(), &b_elm);
		if (b_elm != NULL) {
			stringstream buf;
			buf << rand();
			branch_id = branch_id + buf.str();
		}
	} while (b_elm != NULL);

	this->modelptr->AddBranch(elm, branch_id.c_str());

	this->IOport->WriteOut("SUCCESS: <module_id=" + module_id + ";branch_id=" + branch_id + ">");
	return 0;
}

void ModelProcessor::Add_Module(std::string &cmdline)
{
	string module_id, module_type;
	this->_parse_cmd_line(cmdline, SUPPLEMENT, "module_id", &module_id);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, "module_type", &module_type);

	TiXmlElement* elm = nullptr;
	do {
		this->modelptr->LocateModule(module_id.c_str(), &elm);//elm为null，表明没有满足要求的节点
		if (elm != NULL) {//已存在该节点，换一个id重新搜索
						  // 特殊处理
			stringstream buf;
			buf << rand();
			module_id = module_id + buf.str();
		}
	} while (elm != NULL);

	// 添加节点
	this->modelptr->AddModule(module_id.c_str(), module_type.c_str());

	this->IOport->WriteOut(string("SUCCESS: <module_id=") + module_id + ">");
}

/*
COMMANDLINE REMOVE:
	MODULE_REMOVE:		(module_id=sdf;)					NONE;
	BRANCH_REMOVE:		(module_id=asdfsf;branch_id=asdf;)	NONE;
	VARIABLE_REMOVE:	(module_id=asdjdf;var_id=sdfsf;)	NONE;
	RELATE_REMOVE:		(relate_id=sdfasdf;)				NONE;
RESULT:
	SUCCESS:<key=value> Already removed;
	ERROR:<key=value> error why;
*/
// 删除 操作，统一处理
int ModelProcessor::_remove(std::string cmdline)
{
	string operate_words = " ";
	this->_parse_cmd_line(cmdline, OPERATE_WORDS, "", &operate_words);

	if (operate_words.find("MODULE") != string::npos) {
		bool retflag;
		int retval = Remove_Module(cmdline, retflag);
		if (retflag) return retval;
	}
	else if (operate_words.find("BRANCH") != string::npos) {
		bool retflag;
		int retval = Remove_Branch(cmdline, retflag);
		if (retflag) return retval;
	}
	else if (operate_words.find("VARIABLE") != string::npos) {
		bool retflag;
		int retval = Remove_Variable(cmdline, retflag);
		if (retflag) return retval;
	}
	else if (operate_words.find("RELATE") != string::npos) {

	}
	return 0;
}

int ModelProcessor::Remove_Variable(std::string &cmdline, bool &retflag)
{
	retflag = true;
	string module_id(""), variable_id("");
	this->_parse_cmd_line(cmdline, CONDITION, "module_id", &module_id);
	this->_parse_cmd_line(cmdline, CONDITION, "variable_id", &variable_id);

	TiXmlElement* module_node(nullptr);
	this->modelptr->LocateModule(module_id.c_str(), &module_node);

	if (module_node == NULL) {
		this->IOport->WriteOut("ERROR:<module_id=" + module_id + ";> Module isn't exist!");
		return -1;
	}

	TiXmlElement* variable_node(nullptr);
	this->modelptr->LocateVariable(module_node, variable_id.c_str(), &variable_node);

	if (variable_node == NULL) {
		this->IOport->WriteOut("ERROR:<module_id=" + module_id +
			";variable_id=" + variable_id + ";> Variable isn't exist!");
		return -1;
	}

	variable_node->Parent()->RemoveChild(variable_node);

	this->IOport->WriteOut("SUCCESS:<module_id=" + module_id +
		";variable_id=" + variable_id + ";> Variable already removed.");
	retflag = false;
	return {};
}

int ModelProcessor::Remove_Branch(std::string &cmdline, bool &retflag)
{
	retflag = true;
	string module_id(""), branch_id("");
	this->_parse_cmd_line(cmdline, CONDITION, "module_id", &module_id);
	this->_parse_cmd_line(cmdline, CONDITION, "branch_id", &branch_id);

	TiXmlElement* module_node(nullptr);
	this->modelptr->LocateModule(module_id.c_str(), &module_node);

	if (module_node == NULL) {
		this->IOport->WriteOut("ERROR:<module_id=" + module_id + ";> Module isn't exist!");
		return -1;
	}

	TiXmlElement* branch_node(nullptr);
	this->modelptr->LocateBranch(module_node, branch_id.c_str(), &branch_node);

	if (branch_node == NULL) {
		this->IOport->WriteOut("ERROR:<module_id=" + module_id +
			";branch_id=" + branch_id + ";> Branch isn't exist!");
		return -1;
	}

	branch_node->Parent()->RemoveChild(branch_node);

	this->IOport->WriteOut("SUCCESS:<module_id=" + module_id +
		";branch_id=" + branch_id + ";> Branch already removed.");
	retflag = false;
	return {};
}

int ModelProcessor::Remove_Module(std::string &cmdline, bool &retflag)
{
	retflag = true;
	string module_id("");
	this->_parse_cmd_line(cmdline, CONDITION, "module_id", &module_id);

	TiXmlElement* module_node(nullptr);
	this->modelptr->LocateModule(module_id.c_str(), &module_node);

	if (module_node == NULL) {
		this->IOport->WriteOut("ERROR:<module_id=" + module_id + "> Module isn't exist!");
		return -1;
	}

	module_node->Parent()->RemoveChild(module_node);

	this->IOport->WriteOut("SUCCESS: <module_id=" + module_id + "> Module already removed!");
	retflag = false;
	return {};
}


int ModelProcessor::_query(std::string cmdline)
{
	string operate_words = " ";
	this->_parse_cmd_line(cmdline, OPERATE_WORDS, "", &operate_words);

	if (operate_words.find("MODEL") != string::npos) {
		this->modelptr->_print_itself();
	}
	else if (operate_words.find("MODULE") != string::npos) {

	}
	else if (operate_words.find("BRANCH") != string::npos) {
		
	}
	else if (operate_words.find("VARIABLE") != string::npos) {
		
	}
	else if (operate_words.find("RELATE") != string::npos) {
		
	}
	return 0;
}


int ModelProcessor::_update(std::string cmdline)
{
	string operate_words = " ";
	this->_parse_cmd_line(cmdline, OPERATE_WORDS, "", &operate_words);

	if (operate_words.find("MODEL") != string::npos) {

	}
	else if (operate_words.find("MODULE") != string::npos) {

	}
	else if (operate_words.find("BRANCH") != string::npos) {

	}
	else if (operate_words.find("VARIABLE") != string::npos) {

	}
	else if (operate_words.find("RELATE") != string::npos) {

	}
	return 0;
}


/*
COMMANDLINE SAVE_AS:
	SAVE_AS:			(NONE;)								NONE;
	SAVE_AS:			(NONE;)								filepath=C:\Program File\slkdjf;
RESULT:
	SUCCESS:<filepath=default;>Already saved.
	ERROR: <filepath=aldkjfaldf;> Can not be saved.
*/
// 将数据模型另存为数据文件，如果输入参数为空，表示保存到原文件
int ModelProcessor::_save_as(std::string cmdline)
{
	string filepath;
	this->_parse_cmd_line(cmdline, SUPPLEMENT, "filepath", &filepath);

	if (filepath == "") {
		this->modelptr->SaveFile("default");
		this->IOport->WriteOut("SUCCESS: <filepath=default> File already saved.");
	}
	else {
		this->modelptr->SaveFile(filepath.c_str());
		this->IOport->WriteOut("SUCCESS: <filepath=" + filepath + "> File already saved.");
	}

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
				*value = "";
				return 0;
			}

			if (condition_array.find(key) == string::npos) {
				*value = "";
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
				*value = "";
				return 0;
			}

			if (supplement.find(key) == string::npos) {
				*value = "";
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
