#pragma once
class DataModel
{
public:
	DataModel();
	virtual ~DataModel();
	// ����ȷ�е��ļ�·������ģ�������ļ�
	virtual int InitModel(char* procFilePath);
};

