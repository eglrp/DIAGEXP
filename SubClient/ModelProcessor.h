/*���ڽ�����ǰ�˴�����ָ����Ϣ
**�����γ�����ģ�ͣ���Ӧָ���ģ�͵ġ���ɾ��ġ�
**ָ���ʽ ִ�����Ŀ�����_ִ�в��������޶��������ϣ������������Ŀ��
**================ָ���嵥����Ӧ=====================
COMMANDLINE ADD
	MODULE_ADD:			NONE;:			module_id=sdf;module_type=sfsfdf;
	BRANCH_ADD:			module_id=sdf;:	branch_id=adfd;
	VARIABLE_ADD:		module_id=sdf;:	var_id=asdf;type=asdkfj;accessablily=sdfsf;
	RELATE_ADD:			NONE;:			relate_id=asdf;branch=sdfddf;from=adkjfl;to=alflskd;
RESULT:
	SUCCESS:
	FAIL:


COMMANDLINE REMOVE:
	MODULE_REMOVE:		module_id=sdf;:		NONE
	BRANCH_REMOVE:		branch_id=asdf;:	NONE
	VARIABLE_REMOVE:	variable=sdfsf;:	NONE
	RELATE_REMOVE:		relate_id=sdfasdf;:	NONE

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


class ModelProcessor
{
public:
	ModelProcessor();
	virtual ~ModelProcessor();
};

#endif