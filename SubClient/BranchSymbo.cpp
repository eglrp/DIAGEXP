#include "BranchSymbo.h"

#define NODE_RANK_AT_HEAD 0
#define UPSTREAM_ERROR 1
#define DOWNSTREAM_ERROR -1


using namespace std;

BranchSymbo::BranchSymbo(std::string& node_id)
	: rank(0)
	, node_id("")
	, upstreamNodeC(nullptr)
	, downstreamNodeC(nullptr)
{
	this->upstreamNodeC = new map<string, BranchSymbo*>();
	this->downstreamNodeC = new map<string, BranchSymbo*>();
	this->node_id = node_id;
}


BranchSymbo::~BranchSymbo()
{
	delete this->upstreamNodeC;
	delete this->downstreamNodeC;
}


int BranchSymbo::BindPreviousNode(BranchSymbo* previousNode, std::string* relate_id)
{
	this->upstreamNodeC->insert(pair<string, BranchSymbo*>(*relate_id, previousNode));
	return 0;
}


int BranchSymbo::BindNextNode(BranchSymbo* nextNode, std::string* relate_id)
{
	this->downstreamNodeC->insert(pair<string, BranchSymbo*>(*relate_id, nextNode));
	return 0;
}


int BranchSymbo::ResetToContentHead()
{
	this->rank = NODE_RANK_AT_HEAD;
	return 0;
}

// 上一节点调用本函数，用于确定本节点处在的位置，向下递归整理，rank越来越大
// 返回值：DOWNSTREAM_ERROR，在下面发现了回环支路
int BranchSymbo::DownstreamArrayRankClear(int previousRank, std::vector<std::string>* avoidList)
{
	if (!avoidList) {
		avoidList = new vector<string>();
	}

	// 查询是否重复经过本节点，如果是，返回错误代码，不继续执行
	if (find(avoidList->begin(), avoidList->end(), this->node_id) != avoidList->end()) {
		return DOWNSTREAM_ERROR;
	}
	
	// 并没有形成节点回环，那么就开始计算节点等级
	// 第一次或多次经过本节点，从节点排布上来算，本节点rank值必须大于调用方上级节点提供值
	// 如果发现本节点值小于外部调用，则升值。
	if (previousRank >= this->rank) {
		this->rank = previousRank + 1;
	}

	avoidList->push_back(this->node_id);

	map<string, BranchSymbo*>::iterator itptr;
	for (itptr = this->downstreamNodeC->begin(); itptr != this->downstreamNodeC->end();++itptr) {
		itptr->second->DownstreamArrayRankClear(this->rank,avoidList);
	}
	avoidList->pop_back();
	
	return 0;
}


// 上溯，重排队列等级,rank越来越小
// 返回值：UPSTREAM_ERROR，在上面发现了回环支路
int BranchSymbo::UpstreamArrayRankClear(int nextRank, std::vector<std::string>* avoidList)
{
	if (!avoidList) {
		avoidList = new vector<string>();
	}


	if (find(avoidList->begin(), avoidList->end(), this->node_id) != avoidList->end()) {
		return UPSTREAM_ERROR;
	}
	
	// 开始计算节点等级，正常情况下，本函数是由下级节点调用，本节点rank值需要小于提供的nextrank
	// 如果发现，本节点的提供的值大于调用方提供的值，则说明多分支经过本节点，且另一分支节点数少
	// 需要降值,thisRank 需要变更为更小的值.
	if (nextRank <= this->rank) {
		this->rank = nextRank -1;
	}

	avoidList->push_back(this->node_id);

	map<string, BranchSymbo*>::iterator itptr;
	for (itptr = this->upstreamNodeC->begin(); itptr != this->upstreamNodeC->end(); ++itptr) {
		itptr->second->UpstreamArrayRankClear(this->rank,avoidList);
	}
	avoidList->pop_back();

	return 0;
}


// 获取排名序列
int BranchSymbo::GetRank()
{
	return this->rank;
}


// 获取唯一标识符
int BranchSymbo::GetBranchNode_id(std::string* branchNode_id)
{
	*branchNode_id = this->node_id;
	return 0;
}


// 打印branch内容到缓冲，一般rank_head节点调用函数，能够将整个分支打印出来
// 方向自顶向下
int BranchSymbo::PrintItSelfContent(std::string* stringBuf)
{
	// 最后一个end节点掠过
	if (this->downstreamNodeC->size() == 0)
		return 0;


	map<string, BranchSymbo*>::iterator it_ptr;

	// 一个小分支一个小分支的打印方式
	for (it_ptr = this->downstreamNodeC->begin();
		it_ptr != this->downstreamNodeC->end(); ++it_ptr) {

		string branch_id("");
		it_ptr->second->GetBranchNode_id(&branch_id);
		// 打印node节点id
		*stringBuf += string(BRANCH_NODE_SYMBO) + "=" + branch_id + ";";
		// 紧跟着打印到节点的关系
		*stringBuf += string(BRANCH_RELATE_SYMBO) + "=" + it_ptr->first + ";\n";

		// 以上确定了一个节点之后，继续以下一个节点为基准执行打印自身
		int child_rank = it_ptr->second->GetRank();
		// 斩断节点回环
		if (this->rank < child_rank) {
			it_ptr->second->PrintItSelfContent(stringBuf);
		}
	}
	return 0;
}
