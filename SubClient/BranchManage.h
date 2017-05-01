#include "DataModel.h"
#include "OperateAccept.h"
#include "BasicSupport.h"
#include "BranchSymbo.h"

class BranchManage
{
public:
	BranchManage();
	virtual ~BranchManage();
	// 初始化模型branchManage
	virtual int Init(DataModel* model);
	virtual int PrintOutBranchContent(const char * branch_map, std::string* stringBuf);
private:
	// 内部函数整理分支内容
	virtual int TrimBranchContent();
	// 打印分支内容
	virtual int PrintBranch(std::string* stringBuf);
	// 分支节点容器 branch_contentnode_collection
	std::map<std::string, BranchSymbo*>* branch_CN_C_ptr;
	DataModel* model_ptr;
	// 加载分支内容节点函数
	virtual int LoadBranchContentNode(const char* branch_map);
};

