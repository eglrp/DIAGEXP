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
	virtual int LocateBranch(TiXmlElement* moduleElm, const char * b_id, TiXmlElement** branchElmRef);
	// 定位属于模块的变量节点
	// variable节点是一个三级节点，需要由module_id与variable_id共同确定
	virtual int LocateVariable(TiXmlElement* moduleElm, const char * v_id, TiXmlElement** varElmRef);
private:
	TiXmlElement* RootElm;
public:
	// 精确获取一个relate节点，relate节点是一个次级节点，因此利用R_id可以唯一确定
	virtual int LocateRelate(const char* r_id, TiXmlElement** relateRef);
	// 根据指定的分支id，获取属于该分支的下一个节点，有状态方法
	// 如果第一次调用该方法或者id与上次调用不同，模型从头遍历节点树，
	// 如果两次调用相同，模型紧跟着上次结果取下一个节点。
	virtual int LocateNextOneOfRelates(char* module_branch_map, TiXmlElement** relateRef);
private:
	TiXmlElement* previousRelate;
public:
	// 添加module
	virtual int AddModule(const char * m_id, const char * type);
	// 添加relate节点
	virtual int AddRelate(const char * relate_id, const char * branch_map, const char * from, const char * to);
	// 修改模型属性
	virtual int ModifyMainModule(char* value);
	// 添加branch节点，同其他节点要求一致，需要人工确保该节点的唯一性
	virtual int AddBranch(TiXmlElement* mountable, const char * branch_id);
	// 添加一个variable节点，人工确保唯一性
	virtual int AddVariable(TiXmlElement* mountable, const char * varibale_id, const char * type, const char * accessible);
	// 打印模型自身，是一个测试方法，并非常用方法
	virtual int _print_itself();
};

#endif