/*用于解析从前端传来的指令信息
**本地形成数据模型，响应指令对模型的“增删查改”
**指令格式 执行命令[目标类别_执行操作]：(限定条件集合；)添加属性条目；
**================指令清单与响应=====================
COMMANDLINE ADD==================================================
	MODULE_ADD :		(NONE;)				module_id = sdf; module_type = sfsfdf;
	BRANCH_ADD:			(module_id = sdf;)	branch_id = adfd;
	VARIABLE_ADD:		(module_id = sdf;)	variable_id = asdf; type = asdkfj; accessablily = sdfsf;
	RELATE_ADD:			(NONE;)				relate_id = asdf; branch_map = sdfddf; from = adkjfl; to = alflskd;
RESULT:
	SUCCESS:S3 key and value
	ERROR : what and why


COMMANDLINE REMOVE:===============================================
	MODULE_REMOVE:		(module_id=sdf;)					NONE;
	BRANCH_REMOVE:		(module_id=asdfsf;branch_id=asdf;)	NONE;
	VARIABLE_REMOVE:	(module_id=asdj;variable_id=sdfd;)	NONE;
	RELATE_REMOVE:		(relate_id=sdfasdf;)				NONE;
RESULT:
	SUCCESS:<key=value> Already removed;
	ERROR:<key=value> error why;



COMMANDLINE QUERY:=================================================
	MODEL_QUERY:		(NONE;)								NONE;
															query=mainbranch;
RESULT:
	SUCCESS:<query=mainbranch> query success.
	branch_id=adfasf;
	
	ERROR:<query=mainbranch> mainbranch not exist.

	--------------------------------------------------------------------------------------------
	MODULE_QUERY:		(module_id=asdfaf;)					query=description;
RESULT:
	SUCCESS:<module_id=asdfaf;> query success.
	{name=sdfd;
	branch_list=[sdf,sdfs,dfas,asffd,sdfa];
	variable_list=[asdf,asdf,sdf,sdfa,sfsdf,asdfa];}
	
	ERROR:<module_id=asdf;> module not exist.

	----------------------------------------------------------------------------------------------
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

	------------------------------------------------------------------------------------------------
	VARIABLE_QUERY:		(module_id=asd;variable_id=adf;)	NONE;
RESULT:
	SUCCESS:<module_id=asd;variable_id=ad;> query success.
	{name=sdfad;
	description=sdfasdfa;
	type=asdfasdf;
	accessable=adfasdf;}

	ERROR:<module_id=asd;variable_id=ad;> variable not exist.

	--------------------------------------------------------------------------------------------------
	RELATE_QUERY:		(relate_id=sff;)					NONE;
RESULT:
	SUCCESS:<relate_id=asdfad;> query success.
	{from=asdfasdf.asdkjalkj;
	to=asdfasf;
	branch_map=asdfadf.asdfad;
	elm:to.var_id=from.var_id;
	elm:to.varasd=from.vadfaf;}

	ERROR:<relate_id=adfadf;> relate not exist.

COMMANDLINE UPDATE:========================================================================
	MODEL_UPDATE:		(NONE;)								mainmodule=asdfj;
	MODULE_UPDATE:		(module_id=afaf;)					name=adfsf;
	BRANCH_UPDATE:		(module_id=adff;branch_id=adfad;)	input(output)=[sdfjkd;skflsj;skdjfls;];
	VARIABLE_UPDATE:	(module_id=adff;var_id=adfa;)		name=slkjf;
						(module_id=asdf;var_id=sdfad;)		accessablily=branch/module/global;
	RELATE_UPDATE:		(relate_id=adfad;)					elmap=[to.var1:somemodule.var2;];


COMMANDLINE SAVE_AS:=======================================================================
	SAVE_AS:			(NONE;)								NONE;
	SAVE_AS:			(NONE;)								filepath=C:\Program File\slkdjf;
RESULT:
	SUCCESS:<filepath=default;>Already saved.
	ERROR: <filepath=aldkjfaldf;> Can not be saved.
**/

#ifndef MODELPROCESSOR_MACRO
#define MODELPROCESSOR_MACRO

#include "BasicSupport.h"
#include "DataModel.h"
#include "OperateAccept.h"
#include "BranchManage.h"


class ModelProcessor
{
public:
	ModelProcessor();
	virtual ~ModelProcessor();
	virtual int InitProcessor(DataModel* model, OperateAccept* IOport);
private:
	DataModel* modelptr;
public:
	// “增加”操作统一处理
	virtual int _add(std::string cmdline);
	void Add_Relate(std::string &cmdline);
	int Add_Variable(std::string &cmdline, bool &retflag);
	int Add_Branch(std::string &cmdline);
	void Add_Module(std::string &cmdline);
	// 删除 操作，统一处理
	virtual int _remove(std::string cmdline);
	int Remove_Relate(std::string &cmdline, bool &retflag);
	int Remove_Variable(std::string &cmdline, bool &retflag);
	int Remove_Branch(std::string &cmdline, bool &retflag);
	int Remove_Module(std::string &cmdline, bool &retflag);
	virtual int _query(std::string cmdline);
	int Query_Branch(std::string &cmdline, bool &retflag);
	int Query_Module(std::string &cmdline, bool &retflag);
	virtual int _update(std::string cmdline);
private:
	OperateAccept* IOport;
public:
	// 进入循环消息处理过程
	virtual int Loop();
	// 将数据模型另存为数据文件，如果输入参数为空，表示保存到原文件
	// example   SAVE_AS:(NONE;)NONE;
	virtual int _save_as(std::string cmdline);
	// 根据输入选择性的提取值，如果输入命令没有值，返回nullptr
	virtual int _parse_cmd_line(std::string cmdline, int kind, std::string key, std::string* value);
};

#endif