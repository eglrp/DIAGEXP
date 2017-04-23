#ifndef BASICSUPPORT_MACRO
#define BASICSUPPORT_MACRO

//引入标准库模块
#include<iostream>
#include<fstream>
#include<string>


//引入第三方模块：tinyxml
#include "../ThirdPackage/tinystr.h"
#include "../ThirdPackage/tinyxml.h"



//自定义宏参数
#define PROCESSRULE_VERSION "1.0.0"

//自定义数据文件标签名
#define DOC_ROOT_ELM_TAG "document"
#define PROCESSRULE_VERSION_TAG "fvision"
#define MAINMODULE_TAG "mainmodule"

#define MODULE_COLLECTION_TAG "modulecollect"
#define ELM_SURFACE_NAME "name"
#define MODULE_ELM_TAG "module"
#define MODULE_ID_TAG	"m_id"
#define BRANCH_COLLECTION_TAG "innermap"
#define BRANCH_ID_TAG	"b_id"
#define VAR_COLLECTION_TAG "varcollect"
#define VAR_ID_TAG "v_id"


#define RELATE_COLLECTION_TAG "relatecollect"
#define RELATE_ELM_TAG "relate"
#define RELATE_ID_TAG "relate_id"
#define RELATE_BRANCH_MAP_TAG "branch_map"

#endif