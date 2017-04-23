#include "DataModel.h"



DataModel::DataModel()
{
	doc = new TiXmlDocument();
	RootElm = nullptr;
	previousRelate = nullptr;
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
	TiXmlElement* moduleC = this->RootElm->FirstChildElement(MODULE_COLLECTION_TAG);
	TiXmlElement* moduleOne = moduleC->FirstChildElement();

	while (strcmp(moduleOne->Attribute(MODULE_ID_TAG), m_id)) {
		moduleOne = moduleOne->NextSiblingElement();
	}

	*moduleElmRef = moduleOne;

	return 0;
}


// 定位一个模块的branch节点
int DataModel::LocateBranch(TiXmlElement* moduleElm, char* b_id, TiXmlElement** branchElmRef)
{
	TiXmlElement* branchC = moduleElm->FirstChildElement(BRANCH_COLLECTION_TAG);
	TiXmlElement* branchOne = branchC->FirstChildElement();
	
	while (strcmp(branchOne->Attribute(BRANCH_ID_TAG), b_id)) {
		branchOne = branchOne->NextSiblingElement();
	}

	*branchElmRef = branchOne;

	return 0;
}


// 定位属于模块的变量节点
int DataModel::LocateVariable(TiXmlElement* moduleElm, char* v_id, TiXmlElement** varElmRef)
{
	TiXmlElement* variableC = moduleElm->FirstChildElement(VAR_COLLECTION_TAG);
	TiXmlElement* varOne = variableC->FirstChildElement();

	while (strcmp(varOne->Attribute(VAR_ID_TAG), v_id)) {
		varOne = varOne->NextSiblingElement();
	}
	
	*varElmRef = varOne;

	return 0;
}


// 精确获取一个relate节点，relate节点是一个次级节点，因此利用R_id可以唯一确定
int DataModel::GetRelate(char* r_id, TiXmlElement** relateRef)
{
	TiXmlElement* relateC = this->RootElm->FirstChildElement(RELATE_COLLECTION_TAG);
	TiXmlElement* relateOne = relateC->FirstChildElement();

	while (strcmp(relateOne->Attribute(RELATE_ID_TAG), r_id)){
		relateOne = relateOne->NextSiblingElement();
	}
	
	*relateRef = relateOne;

	return 0;
}


// 根据指定的分支id，获取属于该分支的下一个节点，有状态方法
int DataModel::GetNextOneOfRelates(char* module_branch_id, TiXmlElement** relateRef)
{
	TiXmlElement* relateOne = nullptr;

	if (this->previousRelate != nullptr &&
		!strcmp(this->previousRelate->Attribute(RELATE_BRANCH_MAP_TAG), module_branch_id)) {
		relateOne = this->previousRelate->NextSiblingElement();
	}
	else {
		TiXmlElement* relateC = this->RootElm->FirstChildElement(RELATE_COLLECTION_TAG);
		relateOne = relateC->FirstChildElement();
	}



	while (strcmp(relateOne->Attribute(RELATE_BRANCH_MAP_TAG), module_branch_id)) {
		relateOne = relateOne->NextSiblingElement();
	}

	*relateRef = relateOne;
	this->previousRelate = relateOne;

	return 0;
}
