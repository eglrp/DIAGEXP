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
int DataModel::LocateModule(const char * m_id, TiXmlElement** moduleElmRef)
{
	TiXmlElement* moduleC = this->RootElm->FirstChildElement(MODULE_COLLECTION_TAG);
	TiXmlElement* moduleOne = moduleC->FirstChildElement();

	while (moduleOne != nullptr && strcmp(moduleOne->Attribute(MODULE_ID_TAG), m_id)) {
		moduleOne = moduleOne->NextSiblingElement();
	}

	*moduleElmRef = moduleOne;

	return 0;
}


// 定位一个模块的branch节点
int DataModel::LocateBranch(TiXmlElement* moduleElm, const char * b_id, TiXmlElement** branchElmRef)
{
	TiXmlElement* branchC = moduleElm->FirstChildElement(BRANCH_COLLECTION_TAG);
	TiXmlElement* branchOne = branchC->FirstChildElement();
	
	while (branchOne != nullptr && strcmp(branchOne->Attribute(BRANCH_ID_TAG), b_id)) {
		branchOne = branchOne->NextSiblingElement();
	}

	*branchElmRef = branchOne;

	return 0;
}


// 定位属于模块的变量节点
int DataModel::LocateVariable(TiXmlElement* moduleElm, const char * v_id, TiXmlElement** varElmRef)
{
	TiXmlElement* variableC = moduleElm->FirstChildElement(VAR_COLLECTION_TAG);
	TiXmlElement* varOne = variableC->FirstChildElement();

	while (varOne != nullptr && strcmp(varOne->Attribute(VAR_ID_TAG), v_id)) {
		varOne = varOne->NextSiblingElement();
	}
	
	*varElmRef = varOne;

	return 0;
}


// 精确获取一个relate节点，relate节点是一个次级节点，因此利用R_id可以唯一确定
int DataModel::LocateRelate(char* r_id, TiXmlElement** relateRef)
{
	TiXmlElement* relateC = this->RootElm->FirstChildElement(RELATE_COLLECTION_TAG);
	TiXmlElement* relateOne = relateC->FirstChildElement();

	while (relateOne != nullptr && strcmp(relateOne->Attribute(RELATE_ID_TAG), r_id)){
		relateOne = relateOne->NextSiblingElement();
	}
	
	*relateRef = relateOne;

	return 0;
}


// 根据指定的分支id，获取属于该分支的下一个节点，有状态方法
int DataModel::LocateNextOneOfRelates(char* module_branch_map, TiXmlElement** relateRef)
{
	TiXmlElement* relateOne = nullptr;

	if (this->previousRelate != nullptr &&
		!strcmp(this->previousRelate->Attribute(RELATE_BRANCH_MAP_TAG), module_branch_map)) {
		relateOne = this->previousRelate->NextSiblingElement();
	}
	else {
		TiXmlElement* relateC = this->RootElm->FirstChildElement(RELATE_COLLECTION_TAG);
		relateOne = relateC->FirstChildElement();
	}



	while (relateOne != nullptr && strcmp(relateOne->Attribute(RELATE_BRANCH_MAP_TAG), module_branch_map)) {
		relateOne = relateOne->NextSiblingElement();
	}

	*relateRef = relateOne;
	this->previousRelate = relateOne;

	return 0;
}


// 修改模型属性
int DataModel::ModifyMainModule(char* value)
{
	this->RootElm->SetAttribute(MAINMODULE_TAG, value);
			
	return 0;
}

// 添加module
int DataModel::AddModule(const char * m_id, const char * type)
{
	TiXmlElement* moduleC = this->RootElm->FirstChildElement(MODULE_COLLECTION_TAG);
	
	TiXmlElement* moduleOne = new TiXmlElement(MODULE_ELM_TAG);
	moduleOne->SetAttribute(MODULE_ID_TAG, m_id);
	moduleOne->SetAttribute(MODULE_TYPE_TAG, type);
	moduleC->LinkEndChild(moduleOne);

	TiXmlElement* nameNode = new TiXmlElement(ELM_NAME_TAG);
	TiXmlText* value_name = new TiXmlText(ELM_NAME_UNNAMED);
	nameNode->LinkEndChild(value_name);
	moduleOne->LinkEndChild(nameNode);

	TiXmlElement* branchCollect = new TiXmlElement(BRANCH_COLLECTION_TAG);
	moduleOne->LinkEndChild(branchCollect);

	TiXmlElement* varCollect = new TiXmlElement(VAR_COLLECTION_TAG);
	moduleOne->LinkEndChild(varCollect);


	return 0;
}



// 添加branch节点，同其他节点要求一致，需要人工确保该节点的唯一性
int DataModel::AddBranch(TiXmlElement* mountable, const char * branch_id)
{
	TiXmlElement* branchC = mountable->FirstChildElement(BRANCH_COLLECTION_TAG);
	
	TiXmlElement* branchOne = new TiXmlElement(BRANCH_ELM_TAG);
	branchOne->SetAttribute(BRANCH_ID_TAG, branch_id);
	branchC->LinkEndChild(branchOne);

	TiXmlElement* nameNode = new TiXmlElement(ELM_NAME_TAG);
	TiXmlText* name_value = new TiXmlText(ELM_NAME_UNNAMED);
	nameNode->LinkEndChild(name_value);
	branchOne->LinkEndChild(nameNode);

	TiXmlElement* inputC = new TiXmlElement(BRANCH_INPUT_VAR_COLLECTION_TAG);
	branchOne->LinkEndChild(inputC);

	TiXmlElement* outputC = new TiXmlElement(BRANCH_OUTPUT_VAR_COLLECTION_TAG);
	branchOne->LinkEndChild(outputC);

	return 0;
}


// 添加一个variable节点，人工确保唯一性
int DataModel::AddVariable(TiXmlElement* mountable, const char * varibale_id, const char * type, const char * accessible)
{
	TiXmlElement* varC = mountable->FirstChildElement(VAR_COLLECTION_TAG);

	TiXmlElement* varOne = new TiXmlElement(VAR_ELM_TAG);
	varOne->SetAttribute(VAR_ID_TAG, varibale_id);
	varOne->SetAttribute(VAR_TYPE_TAG, type);
	varOne->SetAttribute(VAR_ACCESSABLE, accessible);

	varC->LinkEndChild(varOne);

	TiXmlElement* name = new TiXmlElement(ELM_NAME_TAG);
	TiXmlText* name_v = new TiXmlText(ELM_NAME_UNNAMED);
	name->LinkEndChild(name_v);
	varOne->LinkEndChild(name);

	return 0;
}


// 添加relate节点
int DataModel::AddRelate(char* relate_id, char* branch_map, char* from, char* to)
{
	TiXmlElement* relateC = this->RootElm->FirstChildElement(RELATE_COLLECTION_TAG);

	TiXmlElement* relateOne = new TiXmlElement(RELATE_ELM_TAG);
	relateOne->SetAttribute(RELATE_ID_TAG, relate_id);
	relateOne->SetAttribute(RELATE_BRANCH_MAP_TAG, branch_map);
	relateOne->SetAttribute(RELATE_BEGIN, from);
	relateOne->SetAttribute(RELATE_END, to);

	relateC->LinkEndChild(relateOne);

	return 0;
}
