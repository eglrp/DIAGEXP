#ifndef DATAMODEL_MACRO
#define DATAMODEL_MACRO

#include "BasicSupport.h"




class DataModel
{
public:
	DataModel();
	virtual ~DataModel();
	// 根据确切的文件路径载入模型数据文件
	virtual int InitModel(char* procFilePath);
private:
	TiXmlDocument* doc;
public:
	// 定位一个模块节点
	// 模块节点是一个次级节点，可以由一个id直接确定
	virtual int LocateModule(const char * m_id, TiXmlElement** moduleElmRef);
	// 定位一个模块的branch节点
	// branch节点是一个三级节点需要由module_id与branch_id共同确定
	virtual int LocateBranch(TiXmlElement* moduleElm, char* b_id, TiXmlElement** branchElmRef);
	// 定位属于模块的变量节点
	// variable节点是一个三级节点，需要由module_id与variable_id共同确定
	virtual int LocateVariable(TiXmlElement* moduleElm, char* v_id, TiXmlElement** varElmRef);
private:
	TiXmlElement* RootElm;
public:
	// 精确获取一个relate节点，relate节点是一个次级节点，因此利用R_id可以唯一确定
	virtual int GetRelate(char* r_id, TiXmlElement** relateRef);
	// 根据指定的分支id，获取属于该分支的下一个节点，有状态方法
	// 如果第一次调用该方法或者id与上次调用不同，模型从头遍历节点树，
	// 如果两次调用相同，模型紧跟着上次结果取下一个节点。
	virtual int GetNextOneOfRelates(char* module_branch_id, TiXmlElement** relateRef);
private:
	TiXmlElement* previousRelate;
public:
	// 添加module
	virtual int AddModule(const char * m_id, const char * type);
	// 添加relate节点
	virtual int AddRelate(char* relate_id, char* branch_map, char* from, char* to);
	// 修改模型属性
	virtual int ModifyMainModule(char* value);
	static int Model_Mainmodule;
	static int Model_ParseVision;
};

#endif