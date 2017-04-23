/*用于解析从前端传来的指令信息
**本地形成数据模型，响应指令对模型的“增删查改”
**指令格式 执行命令（目标类别_执行操作）：限定条件集合；：添加属性条目；
**================指令清单与响应=====================
COMMANDLINE ADD
	MODULE_ADD:			NONE;:			module_id=sdf;module_type=sfsfdf;
	BRANCH_ADD:			module_id=sdf;:	branch_id=adfd;
	VARIABLE_ADD:		module_id=sdf;:	var_id=asdf;type=asdkfj;accessablily=sdfsf;
	RELATE_ADD:			NONE;:			relate_id=asdf;branch=sdfddf;from=adkjfl;to=alflskd;
RESULT:
	SUCCESS:S3 key and value
	ERROR:  what and why


COMMANDLINE REMOVE:
	MODULE_REMOVE:		module_id=sdf;:						NONE
	BRANCH_REMOVE:		module_id=asdfsf;branch_id=asdf;:	NONE
	VARIABLE_REMOVE:	module_id=asdjdf;var_id=sdfsf;:		NONE
	RELATE_REMOVE:		relate_id=sdfasdf;:					NONE

COMMANDLINE QUERY:
	BRANCH_QUERY:		branch_id=adfadf;:	NONE
	MODULE_QUERY:
	VARIABLE_QUERY:


COMMANDLINE UPDATE:
	MODEL_UPDATE:		NONE;:								mainmodule=asdfj;
	MODULE_UPDATE:		module_id=afaf;:					name=adfsf;
	BRANCH_UPDATE:		module_id=adff;branch_id=adfad;:	input(output)=[sdfjkd;skflsj;skdjfls;];
	VARIABLE_UPDATE:	module_id=adff;var_id=adfa;:		name=slkjf;
						module_id=asdf;var_id=sdfad;:		accessablily=branch/module/global;
	RELATE_UPDATE:		relate_id=adfad;:					elmap=[to.var1:somemodule.var2;];
**
**/

#ifndef MODELPROCESSOR_MACRO
#define MODELPROCESSOR_MACRO

#include "BasicSupport.h"
#include "DataModel.h"


class ModelProcessor
{
public:
	ModelProcessor();
	virtual ~ModelProcessor();
	virtual int InitProcessor(DataModel* model);
private:
	DataModel* modelptr;
public:
	// “增加”操作统一处理
	virtual int _add(char* cmdline);
	// 删除 操作，统一处理
	virtual int _remove(char* cmdline);
	virtual int _query(char* cmdline);
	virtual int _update(char* cmdline);
};

#endif