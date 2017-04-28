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
	virtual int LocateBranch(TiXmlElement* moduleElm, const char * b_id, TiXmlElement** branchElmRef);
	// ��λ����ģ��ı����ڵ�
	// variable�ڵ���һ�������ڵ㣬��Ҫ��module_id��variable_id��ͬȷ��
	virtual int LocateVariable(TiXmlElement* moduleElm, const char * v_id, TiXmlElement** varElmRef);
private:
	TiXmlElement* RootElm;
public:
	// ��ȷ��ȡһ��relate�ڵ㣬relate�ڵ���һ���μ��ڵ㣬�������R_id����Ψһȷ��
	virtual int LocateRelate(const char* r_id, TiXmlElement** relateRef);
	// ����ָ���ķ�֧id����ȡ���ڸ÷�֧����һ���ڵ㣬��״̬����
	// �����һ�ε��ø÷�������id���ϴε��ò�ͬ��ģ�ʹ�ͷ�����ڵ�����
	// ������ε�����ͬ��ģ�ͽ������ϴν��ȡ��һ���ڵ㡣
	virtual int LocateNextOneOfRelates(char* module_branch_map, TiXmlElement** relateRef);
private:
	TiXmlElement* previousRelate;
public:
	// ���module
	virtual int AddModule(const char * m_id, const char * type);
	// ���relate�ڵ�
	virtual int AddRelate(const char * relate_id, const char * branch_map, const char * from, const char * to);
	// �޸�ģ������
	virtual int ModifyMainModule(char* value);
	// ���branch�ڵ㣬ͬ�����ڵ�Ҫ��һ�£���Ҫ�˹�ȷ���ýڵ��Ψһ��
	virtual int AddBranch(TiXmlElement* mountable, const char * branch_id);
	// ���һ��variable�ڵ㣬�˹�ȷ��Ψһ��
	virtual int AddVariable(TiXmlElement* mountable, const char * varibale_id, const char * type, const char * accessible);
	// ��ӡģ��������һ�����Է��������ǳ��÷���
	virtual int _print_itself();
};

#endif