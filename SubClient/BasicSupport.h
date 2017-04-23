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
#define MODULE_COLLECTION_TAG "modulecollect"
#define RELATE_COLLECTION_TAG "relatecollect"
#define MODULE_ID_TAG	"m_id"
#define BRANCH_COLLECTION_TAG "innermap"
#define MAINMODULE_TAG "mainmodule"
#define PROCESSRULE_VERSION_TAG "fvision"

#endif