#ifndef FILEOPERATE_MACRO
#define FILEOPERATE_MACRO

#include "BasicSupport.h"

class FileOperate
{
public:
	FileOperate();
	virtual ~FileOperate();
	// 确保procrule文件存在，如果传入空路径，则新建一个默认格式空文件，返回值表明原位置文件是否存在
	// 返回值定义：0，	文件存在
	//				-1，文件不存在，新建空白文件
	virtual int EnsureProcFileExist(char* procFilePath);
};

#endif 