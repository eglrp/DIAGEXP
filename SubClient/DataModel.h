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
};

#endif