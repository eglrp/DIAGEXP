#include "DataModel.h"



DataModel::DataModel()
{
	doc = new TiXmlDocument();
	RootElm = nullptr;
}


DataModel::~DataModel()
{
	delete this->RootElm;
	delete this->doc;
}


// 根据确切的文件路径载入模型数据文件
int DataModel::InitModel(char* procFilePath)
{
	this->doc->LoadFile(procFilePath);
	this->RootElm = this->doc->RootElement();
	return 0;
}


// 定位一个模块节点
int DataModel::LocateModule(char* m_id, TiXmlElement** moduleElmRef)
{
	TiXmlElement* moduleC = this->RootElm->FirstChildElement("modulecollect");
	TiXmlElement* moduleOne = moduleC->FirstChildElement();

	while (strcmp(moduleOne->Attribute("m_id"), m_id)) {
		moduleOne = moduleOne->NextSiblingElement();
	}

	*moduleElmRef = moduleOne;

	return 0;
}


// 定位一个模块的branch节点
int DataModel::LocateBranch(TiXmlElement* moduleElm, char* b_id, TiXmlElement** branchElmRef)
{
	return 0;
}


// 定位属于模块的变量节点
int DataModel::LocateVariable(TiXmlElement* moduleElm, char* v_id, TiXmlElement** varElmRef)
{
	return 0;
}


// 精确获取一个relate节点，relate节点是一个次级节点，因此利用R_id可以唯一确定
int DataModel::GetRelate(char* r_id)
{
	return 0;
}


// 根据指定的分支id，获取属于该分支的下一个节点，有状态方法
int DataModel::GetNextOneOfRelates(char* module_branch_id)
{
	return 0;
}
