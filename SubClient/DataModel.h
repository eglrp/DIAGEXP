#pragma once
class DataModel
{
public:
	DataModel();
	virtual ~DataModel();
	// 根据确切的文件路径载入模型数据文件
	virtual int InitModel(char* procFilePath);
};

