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
	TiXmlElement* moduleC = this->RootElm->FirstChildElement("modulecollect");
	TiXmlElement* moduleOne = moduleC->FirstChildElement();

	while (strcmp(moduleOne->Attribute("m_id"), m_id)) {
		moduleOne = moduleOne->NextSiblingElement();
	}

	*moduleElmRef = moduleOne;

	return 0;
}


// ��λһ��ģ���branch�ڵ�
int DataModel::LocateBranch(TiXmlElement* moduleElm, char* b_id, TiXmlElement** branchElmRef)
{
	return 0;
}


// ��λ����ģ��ı����ڵ�
int DataModel::LocateVariable(TiXmlElement* moduleElm, char* v_id, TiXmlElement** varElmRef)
{
	return 0;
}


// ��ȷ��ȡһ��relate�ڵ㣬relate�ڵ���һ���μ��ڵ㣬�������R_id����Ψһȷ��
int DataModel::GetRelate(char* r_id)
{
	return 0;
}


// ����ָ���ķ�֧id����ȡ���ڸ÷�֧����һ���ڵ㣬��״̬����
int DataModel::GetNextOneOfRelates(char* module_branch_id)
{
	return 0;
}
