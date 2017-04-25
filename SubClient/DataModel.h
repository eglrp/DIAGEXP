#ifndef DATAMODEL_MACRO
#define DATAMODEL_MACRO

#include "BasicSupport.h"




class DataModel
{
public:
	DataModel();
	virtual ~DataModel();
	// ����ȷ�е��ļ�·������ģ�������ļ�
	virtual int InitModel(char* procFilePath);
private:
	TiXmlDocument* doc;
public:
	// ��λһ��ģ��ڵ�
	// ģ��ڵ���һ���μ��ڵ㣬������һ��idֱ��ȷ��
	virtual int LocateModule(const char * m_id, TiXmlElement** moduleElmRef);
	// ��λһ��ģ���branch�ڵ�
	// branch�ڵ���һ�������ڵ���Ҫ��module_id��branch_id��ͬȷ��
	virtual int LocateBranch(TiXmlElement* moduleElm, char* b_id, TiXmlElement** branchElmRef);
	// ��λ����ģ��ı����ڵ�
	// variable�ڵ���һ�������ڵ㣬��Ҫ��module_id��variable_id��ͬȷ��
	virtual int LocateVariable(TiXmlElement* moduleElm, char* v_id, TiXmlElement** varElmRef);
private:
	TiXmlElement* RootElm;
public:
	// ��ȷ��ȡһ��relate�ڵ㣬relate�ڵ���һ���μ��ڵ㣬�������R_id����Ψһȷ��
	virtual int GetRelate(char* r_id, TiXmlElement** relateRef);
	// ����ָ���ķ�֧id����ȡ���ڸ÷�֧����һ���ڵ㣬��״̬����
	// �����һ�ε��ø÷�������id���ϴε��ò�ͬ��ģ�ʹ�ͷ�����ڵ�����
	// ������ε�����ͬ��ģ�ͽ������ϴν��ȡ��һ���ڵ㡣
	virtual int GetNextOneOfRelates(char* module_branch_id, TiXmlElement** relateRef);
private:
	TiXmlElement* previousRelate;
public:
	// ���module
	virtual int AddModule(const char * m_id, const char * type);
	// ���relate�ڵ�
	virtual int AddRelate(char* relate_id, char* branch_map, char* from, char* to);
	// �޸�ģ������
	virtual int ModifyMainModule(char* value);
	static int Model_Mainmodule;
	static int Model_ParseVision;
};

#endif