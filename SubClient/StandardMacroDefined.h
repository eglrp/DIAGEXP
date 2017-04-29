#ifndef STANDARDMACRODEFINED_MACRO
#define STANDARDMACRODEFINED_MACRO

//解析规则版本信息号
#define PROCESSRULE_VERSION "1.0.0"

//自定义数据文件标签名
#define DOC_ROOT_ELM_TAG "document"
#define PROCESSRULE_VERSION_TAG "fvision"
#define MAINBRANCH_TAG "mainbranch_map"

#define MODULE_COLLECTION_TAG "modulecollect"
#define ELM_NAME_TAG "name"
#define ELM_NAME_UNNAMED "unnamed"
#define MODULE_ELM_TAG "module"
#define MODULE_ID_TAG	"m_id"
#define MODULE_TYPE_TAG "type"
#define BRANCH_COLLECTION_TAG "innermap"
#define BRANCH_ID_TAG	"b_id"
#define BRANCH_ELM_TAG "branch"
#define BRANCH_INPUT_VAR_COLLECTION_TAG "input"
#define BRANCH_OUTPUT_VAR_COLLECTION_TAG "output"
#define VAR_COLLECTION_TAG "varcollect"
#define VAR_ELM_TAG "var"
#define VAR_ID_TAG "v_id"
#define VAR_TYPE_TAG "type"
#define VAR_ACCESSABLE "accessable"


#define RELATE_COLLECTION_TAG "relatecollect"
#define RELATE_ELM_TAG "relate"
#define RELATE_ID_TAG "relate_id"
#define RELATE_BRANCH_MAP_TAG "branch_map"
#define RELATE_BEGIN "from"
#define RELATE_END "to"


//操作与命令标准宏
#define PROCESS_EXIT_MSG "$$Process_Exit"
#define PROCESS_START_MSG "$$Process_Start"

#define OPERATE_FACTOR_MODULE_ID "module_id"
#define OPERATE_FACTOR_MODULE_TYPE "module_type"
#define OPERATE_FACTOR_BRANCH_ID "branch_id"
#define OPERATE_FACTOR_VARIABLE_ID "variable_id"
#define OPERATE_FACTOR_VARIABLE_TYPE "type"
#define OPERATE_FACTOR_VARIABLE_ACCESSABLE "accessablily"
#define OPERATE_FACTOR_RELATE_ID "relate_id"
#define OPERATE_FACTOR_RELATE_BRANCH_MAP "branch_map"
#define OPERATE_FACTOR_RELATE_FROM "from"
#define OPERATE_FACTOR_RELATE_TO "to"
#define OPERATE_FACTOR_NONE "NONE;"
#define OPERATE_FACTOR_QUERYKEY "query"

#define OPERATE_OBJECT_MODEL "MODEL"
#define OPERATE_OBJECT_MODULE "MODULE"
#define OPERATE_OBJECT_BRANCH "BRANCH"
#define OPERATE_OBJECT_VARIABLE "VARIABLE"
#define OPERATE_OBJECT_RELATE "RELATE"

#define OPERATE_BEHAVE_ADD "ADD"
#define OPERATE_BEHAVE_REMOVE "REMOVE"
#define OPERATE_BEHAVE_QUERY "QUERY"
#define OPERATE_BEHAVE_UPDATE "UPDATE"
#define OPERATE_BEHAVE_SAVE "SAVE_AS"

#endif