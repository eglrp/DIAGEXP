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

// ��һ�ڵ���ñ�����������ȷ�����ڵ㴦�ڵ�λ�ã����µݹ�����rankԽ��Խ��
// ����ֵ��DOWNSTREAM_ERROR�������淢���˻ػ�֧·
int BranchSymbo::DownstreamArrayRankClear(int previousRank, std::vector<std::string>* avoidList)
{
	if (!avoidList) {
		avoidList = new vector<string>();
	}

	// ��ѯ�Ƿ��ظ��������ڵ㣬����ǣ����ش�����룬������ִ��
	if (find(avoidList->begin(), avoidList->end(), this->node_id) != avoidList->end()) {
		return DOWNSTREAM_ERROR;
	}
	
	// ��û���γɽڵ�ػ�����ô�Ϳ�ʼ����ڵ�ȼ�
	// ��һ�λ��ξ������ڵ㣬�ӽڵ��Ų������㣬���ڵ�rankֵ������ڵ��÷��ϼ��ڵ��ṩֵ
	// ������ֱ��ڵ�ֵС���ⲿ���ã�����ֵ��
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


// ���ݣ����Ŷ��еȼ�,rankԽ��ԽС
// ����ֵ��UPSTREAM_ERROR�������淢���˻ػ�֧·
int BranchSymbo::UpstreamArrayRankClear(int nextRank, std::vector<std::string>* avoidList)
{
	if (!avoidList) {
		avoidList = new vector<string>();
	}


	if (find(avoidList->begin(), avoidList->end(), this->node_id) != avoidList->end()) {
		return UPSTREAM_ERROR;
	}
	
	// ��ʼ����ڵ�ȼ�����������£������������¼��ڵ���ã����ڵ�rankֵ��ҪС���ṩ��nextrank
	// ������֣����ڵ���ṩ��ֵ���ڵ��÷��ṩ��ֵ����˵�����֧�������ڵ㣬����һ��֧�ڵ�����
	// ��Ҫ��ֵ,thisRank ��Ҫ���Ϊ��С��ֵ.
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


// ��ȡ��������
int BranchSymbo::GetRank()
{
	return this->rank;
}


// ��ȡΨһ��ʶ��
int BranchSymbo::GetBranchNode_id(std::string* branchNode_id)
{
	*branchNode_id = this->node_id;
	return 0;
}


// ��ӡbranch���ݵ����壬һ��rank_head�ڵ���ú������ܹ���������֧��ӡ����
// �����Զ�����
int BranchSymbo::PrintItSelfContent(std::string* stringBuf)
{
	// ���һ��end�ڵ��ӹ�
	if (this->downstreamNodeC->size() == 0)
		return 0;


	map<string, BranchSymbo*>::iterator it_ptr;

	// һ��С��֧һ��С��֧�Ĵ�ӡ��ʽ
	for (it_ptr = this->downstreamNodeC->begin();
		it_ptr != this->downstreamNodeC->end(); ++it_ptr) {

		string branch_id("");
		it_ptr->second->GetBranchNode_id(&branch_id);
		// ��ӡnode�ڵ�id
		*stringBuf += string(BRANCH_NODE_SYMBO) + "=" + branch_id + ";";
		// �����Ŵ�ӡ���ڵ�Ĺ�ϵ
		*stringBuf += string(BRANCH_RELATE_SYMBO) + "=" + it_ptr->first + ";\n";

		// ����ȷ����һ���ڵ�֮�󣬼�������һ���ڵ�Ϊ��׼ִ�д�ӡ����
		int child_rank = it_ptr->second->GetRank();
		// ն�Ͻڵ�ػ�
		if (this->rank < child_rank) {
			it_ptr->second->PrintItSelfContent(stringBuf);
		}
	}
	return 0;
}
