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


// ����ȷ�е��ļ�·������ģ�������ļ�
int DataModel::InitModel(char* procFilePath)
{
	this->doc->LoadFile(procFilePath);
	this->RootElm = this->doc->RootElement();
	return 0;
}


// ��λһ��ģ��ڵ�
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


// ��λһ��ģ���branch�ڵ�
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


// ��λ����ģ��ı����ڵ�
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


// ��ȷ��ȡһ��relate�ڵ㣬relate�ڵ���һ���μ��ڵ㣬�������R_id����Ψһȷ��
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


// ����ָ���ķ�֧id����ȡ���ڸ÷�֧����һ���ڵ㣬��״̬����
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
