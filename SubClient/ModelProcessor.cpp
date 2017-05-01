#include "ModelProcessor.h"

using namespace std;

#define OPERATE_WORDS 0
#define CONDITION 1
#define SUPPLEMENT 2


ModelProcessor::ModelProcessor()
	: ioPort(nullptr)
{
	modelptr = nullptr;
}


ModelProcessor::~ModelProcessor()
{
}


int ModelProcessor::InitProcessor(DataModel* model, OperateAccept* port)
{
	this->modelptr = model;
	this->ioPort = port;
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

	if (operate_words.find(OPERATE_OBJECT_MODULE) != string::npos) {
		Add_Module(cmdline);
	}
	else if (operate_words.find(OPERATE_OBJECT_BRANCH) != string::npos) {
		int retval = Add_Branch(cmdline);
		if (retval) return retval;
	}
	else if (operate_words.find(OPERATE_OBJECT_VARIABLE) != string::npos) {
		bool retflag;
		int retval = Add_Variable(cmdline, retflag);
		if (retflag) return retval;
	}
	else if (operate_words.find(OPERATE_OBJECT_RELATE) != string::npos) {
		Add_Relate(cmdline);
	}

	return 0;
}

void ModelProcessor::Add_Relate(std::string &cmdline)
{
	string relate_id, branch_map, from, to;
	this->_parse_cmd_line(cmdline, SUPPLEMENT, OPERATE_FACTOR_RELATE_ID, &relate_id);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, OPERATE_FACTOR_RELATE_BRANCH_MAP, &branch_map);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, OPERATE_FACTOR_RELATE_FROM, &from);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, OPERATE_FACTOR_RELATE_TO, &to);

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
	this->ioPort->WriteOut("SUCCESS: <" + string(OPERATE_FACTOR_RELATE_ID) + "=" + relate_id + ";>");
}

int ModelProcessor::Add_Variable(std::string &cmdline, bool &retflag)
{
	retflag = true;
	string module_id, variable_id, type, accessablily;
	this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_MODULE_ID, &module_id);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, OPERATE_FACTOR_VARIABLE_ID, &variable_id);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, OPERATE_FACTOR_VARIABLE_TYPE, &type);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, OPERATE_FACTOR_VARIABLE_ACCESSABLE, &accessablily);

	TiXmlElement* elm = nullptr;
	this->modelptr->LocateModule(module_id.c_str(), &elm);
	if (elm == NULL) {
		this->ioPort->WriteOut("ERROR: <" + string(OPERATE_FACTOR_MODULE_ID) + "=" + module_id + ";> not exist!");
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
	this->ioPort->WriteOut("SUCCESS: <" + string(OPERATE_FACTOR_MODULE_ID) + "="
		+ module_id + ";"+string(OPERATE_FACTOR_VARIABLE_ID)+"=" + variable_id + ";>");
	retflag = false;
	return {};
}

int ModelProcessor::Add_Branch(std::string &cmdline)
{
	string module_id, branch_id;
	this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_MODULE_ID, &module_id);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, OPERATE_FACTOR_BRANCH_ID, &branch_id);

	TiXmlElement* elm = nullptr;
	this->modelptr->LocateModule(module_id.c_str(), &elm);
	if (elm == NULL) {
		this->ioPort->WriteOut("ERROR: <" + string(OPERATE_FACTOR_MODULE_ID) + "=" + module_id + ";> not exist!");
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

	this->ioPort->WriteOut("SUCCESS: <" + string(OPERATE_FACTOR_MODULE_ID) + "=" + module_id + ";"
		+string(OPERATE_FACTOR_BRANCH_ID)+"=" + branch_id + ";>");
	return 0;
}

void ModelProcessor::Add_Module(std::string &cmdline)
{
	string module_id, module_type;
	this->_parse_cmd_line(cmdline, SUPPLEMENT, OPERATE_FACTOR_MODULE_ID, &module_id);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, OPERATE_FACTOR_MODULE_TYPE, &module_type);

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

	this->ioPort->WriteOut(string("SUCCESS: <"+string(OPERATE_FACTOR_MODULE_ID)+"=") + module_id + ">");
}

/*
COMMANDLINE REMOVE:
	MODULE_REMOVE:		(module_id=sdf;)					NONE;
	BRANCH_REMOVE:		(module_id=asdfsf;branch_id=asdf;)	NONE;
	VARIABLE_REMOVE:	(module_id=asdj;variable_id=sdfd;)	NONE;
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

	if (operate_words.find(OPERATE_OBJECT_MODULE) != string::npos) {
		bool retflag;
		int retval = Remove_Module(cmdline, retflag);
		if (retflag) return retval;
	}
	else if (operate_words.find(OPERATE_OBJECT_BRANCH) != string::npos) {
		bool retflag;
		int retval = Remove_Branch(cmdline, retflag);
		if (retflag) return retval;
	}
	else if (operate_words.find(OPERATE_OBJECT_VARIABLE) != string::npos) {
		bool retflag;
		int retval = Remove_Variable(cmdline, retflag);
		if (retflag) return retval;
	}
	else if (operate_words.find(OPERATE_OBJECT_RELATE) != string::npos) {
		bool retflag;
		int retval = Remove_Relate(cmdline, retflag);
		if (retflag) return retval;
	}
	return 0;
}

int ModelProcessor::Remove_Relate(std::string &cmdline, bool &retflag)
{
	retflag = true;
	string relate_id("");
	this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_VARIABLE_ID, &relate_id);

	TiXmlElement* relate_node(nullptr);
	this->modelptr->LocateRelate(relate_id.c_str(), &relate_node);

	if (relate_node == NULL) {
		this->ioPort->WriteOut("ERROR:<" + string(OPERATE_FACTOR_RELATE_ID) + "=" + relate_id + ";> Relate isn't exist!");
		return -1;
	}

	relate_node->Parent()->RemoveChild(relate_node);

	this->ioPort->WriteOut("SUCCESS: <" + string(OPERATE_FACTOR_RELATE_ID) + "=" + relate_id + ";> Relate already removed!");
	retflag = false;
	return {};
}

int ModelProcessor::Remove_Variable(std::string &cmdline, bool &retflag)
{
	retflag = true;
	string module_id(""), variable_id("");
	this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_MODULE_ID, &module_id);
	this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_VARIABLE_ID, &variable_id);

	TiXmlElement* module_node(nullptr);
	this->modelptr->LocateModule(module_id.c_str(), &module_node);

	if (module_node == NULL) {
		this->ioPort->WriteOut("ERROR:<"+string(OPERATE_FACTOR_MODULE_ID)+"=" + module_id + ";> Module isn't exist!");
		return -1;
	}

	TiXmlElement* variable_node(nullptr);
	this->modelptr->LocateVariable(module_node, variable_id.c_str(), &variable_node);

	if (variable_node == NULL) {
		this->ioPort->WriteOut("ERROR:<" + string(OPERATE_FACTOR_MODULE_ID) + "=" + module_id +";"+
			OPERATE_FACTOR_VARIABLE_ID+"=" + variable_id + ";> Variable isn't exist!");
		return -1;
	}

	variable_node->Parent()->RemoveChild(variable_node);

	this->ioPort->WriteOut("SUCCESS:<" + string(OPERATE_FACTOR_MODULE_ID) + "=" + module_id + ";"
		+ string(OPERATE_FACTOR_VARIABLE_ID) + "=" + variable_id + ";> Variable already removed.");
	retflag = false;
	return {};
}

int ModelProcessor::Remove_Branch(std::string &cmdline, bool &retflag)
{
	retflag = true;
	string module_id(""), branch_id("");
	this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_MODULE_ID, &module_id);
	this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_BRANCH_ID, &branch_id);

	TiXmlElement* module_node(nullptr);
	this->modelptr->LocateModule(module_id.c_str(), &module_node);

	if (module_node == NULL) {
		this->ioPort->WriteOut("ERROR:<"+string(OPERATE_FACTOR_MODULE_ID)+"=" + module_id + ";> Module isn't exist!");
		return -1;
	}

	TiXmlElement* branch_node(nullptr);
	this->modelptr->LocateBranch(module_node, branch_id.c_str(), &branch_node);

	if (branch_node == NULL) {
		this->ioPort->WriteOut("ERROR:<"+string(OPERATE_FACTOR_MODULE_ID)+"=" + module_id + ";"+
			string(OPERATE_FACTOR_BRANCH_ID) + "=" + branch_id + ";> Branch isn't exist!");
		return -1;
	}

	branch_node->Parent()->RemoveChild(branch_node);

	this->ioPort->WriteOut("SUCCESS:<" + string(OPERATE_FACTOR_MODULE_ID) + "=" + module_id + ";" +
		string(OPERATE_FACTOR_BRANCH_ID)+"=" + branch_id + ";> Branch already removed.");
	retflag = false;
	return {};
}

int ModelProcessor::Remove_Module(std::string &cmdline, bool &retflag)
{
	retflag = true;
	string module_id("");
	this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_MODULE_ID, &module_id);

	TiXmlElement* module_node(nullptr);
	this->modelptr->LocateModule(module_id.c_str(), &module_node);

	if (module_node == NULL) {
		this->ioPort->WriteOut("ERROR:<" + string(OPERATE_FACTOR_MODULE_ID) + "=" + module_id + ";> Module isn't exist!");
		return -1;
	}

	module_node->Parent()->RemoveChild(module_node);

	this->ioPort->WriteOut("SUCCESS: <" + string(OPERATE_FACTOR_MODULE_ID) + "=" + module_id + ";> Module already removed!");
	retflag = false;
	return {};
}

/*
COMMANDLINE QUERY:
	MODEL_QUERY:		(NONE;)								NONE;
															query=mainbranch;
RESULT:
	SUCCESS:<query=mainbranch> query success.
	branch_id=adfasf;
	ERROR:<query=mainbranch> mainbranch not exist.
	----------------------------------------------------------------------------------------
COMMANDLINE QUERY:
	MODULE_QUERY:		(module_id=asdfaf;)					query=description;
RESULT:
	SUCCESS:<module_id=asdfaf;> query success.
	{name=sdfd;
	 branch_list=[sdf,sdfs,dfas,asffd,sdfa];
	 variable_list=[asdf,asdf,sdf,sdfa,sfsdf,asdfa];}
	ERROR:<module_id=asdf;> module not exist.
	 ---------------------------------------------------------------------------------------
COMMANDLINE QUERY:
	BRANCH_QUERY:		(module_id=ada;branch_id=adf;)		query=interface;
															query=content;
REUSLT:
	SUCCESS:<module_id=ada;branch_id=adf;> query success.
	{kind=interface;
	name=adfadfsdf;
	description=asdfaf;
	input=[skjf,asdlkjf,asldkjf,asldfm,asdf,lslkj];
	output=[asdjfk,asldjf,asdf,ad,adfa,dfa,dfadsf];}

	{kind=content;
	 name=aldkjfadf;
	 description=adfasdfasdf;
	 link_node_branch=fasdfsd.asdkjj;link_relate=adfaf;
	 link_node_branch=asdfaff.adffdf;link_relate=adfas;
	 link_node_branch=asdfadf.adfadf;link_relate=asdff;
	 ……
	 link_node_branch=link_end;		link_relate=asdfa;}

	ERROR:<module_id=ada;branch_id=adf;> branch not exist.
	-----------------------------------------------------------------------------------------
COMMANDLINE QUERY:
	VARIABLE_QUERY:		(module_id=asd;variable_id=adf;)	NONE;
RESULT:
	SUCCESS:<module_id=asd;variable_id=ad;> query success.
	{name=sdfad;
	 description=sdfasdfa;
	 type=asdfasdf;
	 accessable=adfasdf;}

	ERROR:<module_id=asd;variable_id=ad;> variable not exist.
	-----------------------------------------------------------------------------------------
COMMANDLINE QUERY:
	RELATE_QUERY:		(relate_id=sff;)					NONE;
RESULT:
	SUCCESS:<relate_id=asdfad;> query success.
	{from=asdfasdf.asdkjalkj;
	 to=asdfasf;
	 branch_map=asdfadf.asdfad;
	 elm:to.var_id=from.var_id;
	 elm:to.varasd=from.vadfaf;}
	ERROR:<relate_id=adfadf;> relate not exist.
*/
int ModelProcessor::_query(std::string cmdline)
{
	string operate_words = " ";
	this->_parse_cmd_line(cmdline, OPERATE_WORDS, "", &operate_words);

	//MODEL_QUERY:(NONE;)NONE;
	//MODEL_QUERY:(NONE;)query=mainbranch
	if (operate_words.find(OPERATE_OBJECT_MODEL) != string::npos) {
		string search_value;
		this->_parse_cmd_line(cmdline, SUPPLEMENT, OPERATE_FACTOR_QUERYKEY, &search_value);
		if (search_value == "") {
			this->ioPort->WriteOut("SUCCESS:<" + string(OPERATE_FACTOR_QUERYKEY) + "=model_description;> query success. \n");
			this->modelptr->_print_itself();
		}
		else if(search_value == "mainbranch"){
			this->modelptr->QueryMainModule(&search_value);
			this->ioPort->WriteOut("SUCCESS:<" + string(OPERATE_FACTOR_QUERYKEY) + "=" + search_value + ";> query success.\nbranch_id=" + search_value);
		}
	}
	/*
	COMMANDLINE QUERY:
		MODULE_QUERY:		(module_id=asdfaf;)					query=description;
	RESULT:
		SUCCESS:<module_id=asdfaf;> query success.
		{name=sdfd;
		 branch_list=[sdf,sdfs,dfas,asffd,sdfa,];
		 variable_list=[asdf,asdf,sdf,sdfa,sfsdf,asdfa];}
		ERROR:<module_id=asdf;> module not exist.*/
	else if (operate_words.find(OPERATE_OBJECT_MODULE) != string::npos) {
		bool retflag;
		int retval = Query_Module(cmdline, retflag);
		if (retflag) return retval;
	}
	/*COMMANDLINE QUERY:
		BRANCH_QUERY:		(module_id=ada;branch_id=adf;)		query=interface;
																query=content;
	REUSLT:
		SUCCESS:<module_id=ada;branch_id=adf;> query success.
		{kind=interface;
		 name=adfadfsdf;
		 description=asdfaf;
		 input=[skjf,asdlkjf,asldkjf,asldfm,asdf,lslkj];
		 output=[asdjfk,asldjf,asdf,ad,adfa,dfa,dfadsf];}

		{kind=content;
		 name=aldkjfadf;
		 description=adfasdfasdf;
		 link_node_branch=fasdfsd.asdkjj;link_relate=adfaf;
		 link_node_branch=asdfaff.adffdf;link_relate=adfas;
		 link_node_branch=asdfadf.adfadf;link_relate=asdff;
		 ……
		 link_node_branch=link_end;		link_relate=asdfa;}

		ERROR:<module_id=ada;branch_id=adf;> branch not exist.
	*/
	else if (operate_words.find(OPERATE_OBJECT_BRANCH) != string::npos) {
		bool retflag;
		int retval = Query_Branch(cmdline, retflag);
		if (retflag) return retval;
	}
	/*COMMANDLINE QUERY :
		VARIABLE_QUERY:		(module_id = asd; variable_id = adf;)	NONE;
	RESULT:
		SUCCESS:<module_id = asd; variable_id = ad; > query success.
		{name = sdfad;
		description = sdfasdfa;
		type = asdfasdf;
		accessable = adfasdf; }

	ERROR:<module_id = asd; variable_id = ad; > variable not exist.*/
	else if (operate_words.find(OPERATE_OBJECT_VARIABLE) != string::npos) {
		bool retflag;
		int retval = Query_Variable(cmdline, retflag);
		if (retflag) return retval;
	}
	/*COMMANDLINE QUERY:
		RELATE_QUERY:		(relate_id=sff;)					NONE;
	RESULT:
		SUCCESS:<relate_id=asdfad;> query success.
		{from=asdfasdf.asdkjalkj;
		 to=asdfasf;
		 branch_map=asdfadf.asdfad;
		 elm:to.var_id=from.var_id;
		 elm:to.varasd=from.vadfaf;}
		ERROR:<relate_id=adfadf;> relate not exist.*/
	else if (operate_words.find(OPERATE_OBJECT_RELATE) != string::npos) {
		string relate_id("");
		this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_RELATE_ID, &relate_id);

		TiXmlElement* relate_ptr = nullptr;
		this->modelptr->LocateRelate(relate_id.c_str(), &relate_ptr);
		if (relate_ptr == NULL) {
			this->ioPort->WriteOut("ERROR:<" OPERATE_FACTOR_RELATE_ID "="
				+ relate_id + ";> relate not exist.");
		}
		string anwser("");
		anwser += string("SUCCESS:<") + OPERATE_FACTOR_RELATE_ID + "=" + relate_id + ";> query success.\n";
		anwser += string("{") + OPERATE_FACTOR_RELATE_FROM + "=" + relate_ptr->Attribute(RELATE_BEGIN) + ";\n";
		anwser += string(OPERATE_FACTOR_RELATE_TO) + "=" + relate_ptr->Attribute(RELATE_END) + ";\n";
		anwser += string(OPERATE_FACTOR_RELATE_BRANCH_MAP) + "=" + relate_ptr->Attribute(RELATE_BRANCH_MAP_TAG) + ";\n";
		// elmpair输出






	}
	return 0;
}

int ModelProcessor::Query_Variable(std::string &cmdline, bool &retflag)
{
	retflag = true;
	string module_id(""), variable_id("");
	this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_MODULE_ID, &module_id);
	this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_VARIABLE_ID, &variable_id);

	TiXmlElement* module_ptr = nullptr;
	this->modelptr->LocateModule(module_id.c_str(), &module_ptr);
	if (module_ptr == NULL) {
		this->ioPort->WriteOut("ERROR:<" + string(OPERATE_FACTOR_MODULE_ID) + "="
			+ module_id + ";> module not exist.");
		return -1;
	}

	TiXmlElement* variable_ptr = nullptr;
	this->modelptr->LocateVariable(module_ptr, variable_id.c_str(), &variable_ptr);
	if (variable_ptr == NULL) {
		this->ioPort->WriteOut("ERROR:<" + string(OPERATE_FACTOR_MODULE_ID) + "=" + module_id + ";"
			+ OPERATE_FACTOR_VARIABLE_ID + "=" + variable_id + ";> variable not exist.");
		return -1;
	}

	string anwser("");
	anwser += "SUCCESS:<" + string(OPERATE_FACTOR_MODULE_ID) + "=" + module_id + ";"
		+ OPERATE_FACTOR_VARIABLE_ID + "=" + variable_id + ";> query success.\n";
	anwser += "{name=" + string(variable_ptr->FirstChildElement(ELM_NAME_TAG)
		->FirstChildElement()->Value()) + ";\n";
	anwser += string(OPERATE_FACTOR_VARIABLE_TYPE) + "=" + string(variable_ptr->Attribute(VAR_TYPE_TAG)) + ";\n";
	anwser += string(OPERATE_FACTOR_VARIABLE_ACCESSABLE) + "="
		+ string(variable_ptr->Attribute(VAR_ACCESSABLE)) + ";}\n";

	this->ioPort->WriteOut(anwser);
	retflag = false;
	return {};
}

int ModelProcessor::Query_Branch(std::string &cmdline, bool &retflag)
{
	retflag = true;
	string module_id(""), branch_id(""), query("");
	this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_MODULE_ID, &module_id);
	this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_BRANCH_ID, &branch_id);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, OPERATE_FACTOR_QUERYKEY, &query);

	TiXmlElement* module_ptr = nullptr;
	this->modelptr->LocateModule(module_id.c_str(), &module_ptr);
	if (module_ptr == NULL) {
		this->ioPort->WriteOut("ERROR:<" + string(OPERATE_FACTOR_MODULE_ID) + "="
			+ module_id + ";> module not exist.");
		return -1;
	}

	TiXmlElement* branch_ptr = nullptr;
	this->modelptr->LocateBranch(module_ptr, branch_id.c_str(), &branch_ptr);
	if (branch_ptr == NULL) {
		this->ioPort->WriteOut("ERROR:<" + string(OPERATE_FACTOR_MODULE_ID) + "="
			+ module_id + ";" + OPERATE_FACTOR_BRANCH_ID + "=" + branch_id + ";> branch not exist.");
		return -1;
	}

	string anwser("");
	anwser += string("SUCCESS:<") + OPERATE_FACTOR_MODULE_ID + "=" + module_id + ";"
		+ OPERATE_FACTOR_BRANCH_ID + "=" + branch_id + ";> query success.\n";
	anwser += "{kind=" + query + ";\n";
	anwser += "name=" + string(branch_ptr->FirstChildElement(ELM_NAME_TAG)->FirstChildElement()->Value()) + ";\n";


	if (query == OPERATE_FACTOR_INTERFACE) {
		TiXmlElement* inputElm = branch_ptr->FirstChildElement(BRANCH_INPUT_VAR_COLLECTION_TAG)
			->FirstChildElement();// elm 开头的分支节点
		TiXmlElement* outputElm = branch_ptr->FirstChildElement(BRANCH_OUTPUT_VAR_COLLECTION_TAG)
			->FirstChildElement();

		anwser += string(BRANCH_INPUT_VAR_COLLECTION_TAG) + "=[";
		while (inputElm != NULL) {
			anwser += inputElm->FirstChildElement()->Value() + string(",");
		}
		anwser += "];\n";

		anwser += string(BRANCH_OUTPUT_VAR_COLLECTION_TAG) += "=[";
		while (outputElm != NULL) {
			anwser += outputElm->FirstChildElement()->Value() + string(",");
		}
		anwser += "];}";

	}
	else if (query == OPERATE_FACTOR_CONTENT) {
		BranchManage* optr = new BranchManage();
		optr->Init(this->modelptr);
		optr->PrintOutBranchContent((module_id + MODULE_AND_BRANCH_OR_VAR_SPLIT
			+ branch_id).c_str(), &anwser);
		anwser += "}";
	}

	this->ioPort->WriteOut(anwser);
	retflag = false;
	return {};
}

int ModelProcessor::Query_Module(std::string &cmdline, bool &retflag)
{
	retflag = true;
	string module_id(""), description("");
	this->_parse_cmd_line(cmdline, CONDITION, OPERATE_FACTOR_MODULE_ID, &module_id);
	this->_parse_cmd_line(cmdline, SUPPLEMENT, OPERATE_FACTOR_QUERYKEY, &description);

	TiXmlElement* module_x = nullptr;
	this->modelptr->LocateModule(module_id.c_str(), &module_x);
	if (module_x == NULL) {
		this->ioPort->WriteOut("ERROR:<module_id=" + module_id + "> module not exist.");
		return -1;
	}
	this->ioPort->WriteOut("SUCCESS:<module_id=" + module_id + "> query success.");
	TiXmlElement* name_node = module_x->FirstChildElement(ELM_NAME_TAG);
	this->ioPort->WriteOut("{name=" + string(name_node->FirstChildElement()->Value()) + ";");

	string branch_list("branch_list=[");
	TiXmlElement* branch_node = module_x->FirstChildElement(BRANCH_COLLECTION_TAG)
		->FirstChildElement(BRANCH_ELM_TAG);
	while (branch_node != NULL) {
		branch_list += branch_node->Attribute(BRANCH_ID_TAG);
		branch_list += ",";
		branch_node = branch_node->NextSiblingElement();
	}
	branch_list += "];";
	this->ioPort->WriteOut(branch_list);

	string variable_list("variable_list=[");
	TiXmlElement* variable_node = module_x->FirstChildElement(VAR_COLLECTION_TAG)
		->FirstChildElement(VAR_ELM_TAG);
	while (variable_node != NULL) {
		variable_list += variable_node->Attribute(VAR_ID_TAG);
		variable_list += ",";
		variable_node = variable_node->NextSiblingElement();
	}
	variable_list += "];}";
	this->ioPort->WriteOut(variable_list);
	retflag = false;
	return {};
}

/*
COMMANDLINE UPDATE:
	MODEL_UPDATE:		(NONE;)								mainmodule=asdfj;
	MODULE_UPDATE:		(module_id=afaf;)					name=adfsf;
	BRANCH_UPDATE:		(module_id=adff;branch_id=adfad;)	input(output)=[sdfjkd;skflsj;skdjfls;];
	VARIABLE_UPDATE:	(module_id=adff;var_id=adfa;)		name=slkjf;
						(module_id=asdf;var_id=sdfad;)		accessablily=branch/module/global;
	RELATE_UPDATE:		(relate_id=adfad;)					elmap=[to.var1:somemodule.var2;];
*/
int ModelProcessor::_update(std::string cmdline)
{
	string operate_words = " ";
	this->_parse_cmd_line(cmdline, OPERATE_WORDS, "", &operate_words);

	if (operate_words.find(OPERATE_OBJECT_MODEL) != string::npos) {

	}
	else if (operate_words.find(OPERATE_OBJECT_MODULE) != string::npos) {

	}
	else if (operate_words.find(OPERATE_OBJECT_BRANCH) != string::npos) {

	}
	else if (operate_words.find(OPERATE_OBJECT_VARIABLE) != string::npos) {

	}
	else if (operate_words.find(OPERATE_OBJECT_RELATE) != string::npos) {

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
		this->ioPort->WriteOut("SUCCESS: <filepath=default> File already saved.");
	}
	else {
		this->modelptr->SaveFile(filepath.c_str());
		this->ioPort->WriteOut("SUCCESS: <filepath=" + filepath + "> File already saved.");
	}

	return 0;
}


// 进入循环消息处理过程
int ModelProcessor::Loop()
{
	string cmdline = PROCESS_START_MSG;

	while (cmdline != PROCESS_EXIT_MSG)
	{
		if (cmdline == PROCESS_START_MSG) {
			this->ioPort->GetOneLine(&cmdline);
			continue;
		}
		if (cmdline.find(":") == string::npos || cmdline.find("(") == string::npos || cmdline.find(")") == string::npos)
		{
			this->ioPort->WriteOut("ERROR: <" + cmdline + "> Format Error !");
			this->ioPort->GetOneLine(&cmdline);
			continue;
		}
		// process msg and writeout the result
		string operate_words = cmdline.substr(0, cmdline.find(":"));

		if (operate_words.find(OPERATE_BEHAVE_ADD)!=string::npos)
		{
			this->_add(cmdline);
		}else if (operate_words.find(OPERATE_BEHAVE_REMOVE)!=string::npos)
		{
			this->_remove(cmdline);
		}else if (operate_words.find(OPERATE_BEHAVE_QUERY)!=string::npos)
		{
			this->_query(cmdline);
		}else if (operate_words.find(OPERATE_BEHAVE_UPDATE)!=string::npos)
		{
			this->_update(cmdline);
		}
		else if (operate_words.find(OPERATE_BEHAVE_SAVE) != string::npos) {
			this->_save_as(cmdline);
		}
		else {
			this->ioPort->WriteOut("ERROR: <" + cmdline + "> Illegal Operate Error !");
		}

		// turn to the next msg
		this->ioPort->GetOneLine(&cmdline);
	}

	this->ioPort->WriteOut(PROCESS_EXIT_MSG);

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
			
			if (condition_array == OPERATE_FACTOR_NONE) {
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

			if (supplement == OPERATE_FACTOR_NONE) {
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
