#include"BasicSupport.h"

class BranchSymbo
{
public:
	BranchSymbo(std::string& node_id);
	virtual ~BranchSymbo();
	// 绑定上级节点
	virtual int BindPreviousNode(BranchSymbo* previousNode, std::string* relate_id);
	// 绑定下级节点
	virtual int BindNextNode(BranchSymbo* nextNode, std::string* relate_id);
	// 确定一定要重设本节点为branch的内容构造中第一节点
	virtual int ResetToContentHead();
	// 上一节点调用本函数，用于确定本节点处在的位置，向下递归整理，rank越来越大
	// 返回值：DOWNSTREAM_ERROR，在下面发现了回环支路
	virtual int DownstreamArrayRankClear(int previousRank, std::vector<std::string>* avoidList);
	// 上溯，重排队列等级,rank越来越小
	// 返回值：UPSTREAM_ERROR，在上面发现了回环支路
	virtual int UpstreamArrayRankClear(int thisRank, std::vector<std::string>* avoidList);
	// 获取排名序列
	virtual int GetRank();
private:
	int rank;
	// 本节点的id编号
	std::string node_id;
	// 上一级节点
	std::map<std::string, BranchSymbo*>* upstreamNodeC;
	// 下一级节点
	std::map<std::string, BranchSymbo*>* downstreamNodeC;
public:
	// 获取唯一标识符
	virtual int GetBranchNode_id(std::string* branchNode_id);
	// 打印branch内容到缓冲
	virtual int PrintItSelfContent(std::string* stringBuf);
};

