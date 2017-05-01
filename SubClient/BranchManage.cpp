#include "BranchManage.h"

using namespace std;


BranchManage::BranchManage()
	:branch_CN_C_ptr(nullptr)
	,model_ptr(nullptr)
{
	this->branch_CN_C_ptr = new map<string, BranchSymbo*>();
}


BranchManage::~BranchManage()
{
}


// 初始化模型branchManage
int BranchManage::Init(DataModel* model)
{
	this->model_ptr = model;
	return 0;
}


int BranchManage::PrintOutBranchContent(const char * branch_map, std::string* stringBuf)
{
	// 加载所有分支内容：内容是利用节点关系表示
	this->LoadBranchContentNode(branch_map);
	// 整理所有节点顺序
	this->TrimBranchContent();
	// 打印节点内容
	this->PrintBranch(stringBuf);

	return 0;
}


// 内部函数整理分支内容
int BranchManage::TrimBranchContent()
{
	BranchSymbo* b_one = this->branch_CN_C_ptr->begin()->second;
	vector<string> c = vector<string>();

	// 确定暂时参考点
	b_one->ResetToContentHead();
	// 模拟下级调用上级节点，b_one代表上级节点
	b_one->UpstreamArrayRankClear(1, &c);
	// 模拟上级节点调用下级节点，b_one代表下级节点
	b_one->DownstreamArrayRankClear(-1, &c);

	return 0;
}


// 打印分支内容
int BranchManage::PrintBranch(std::string* stringBuf)
{
	map<string, BranchSymbo*>::iterator it_ptr = this->branch_CN_C_ptr->begin();
	int min_atnow = 0;
	BranchSymbo* tmp = nullptr;

	for (; it_ptr != this->branch_CN_C_ptr->end(); ++it_ptr) {
		int rank_thisnode = it_ptr->second->GetRank();

		if (rank_thisnode <= min_atnow) {
			tmp = it_ptr->second; // 最后得到的应该是begin节点
		}
	}

	// 循环向下打印============================================
	tmp->PrintItSelfContent(stringBuf);

	return 0;
}


// 加载分支内容节点函数
int BranchManage::LoadBranchContentNode(const char* branch_map)
{
	TiXmlElement* content_Node = nullptr;
	do {
		// 获取一个该分支的节点，可能是任意节点
		this->model_ptr->LocateNextOneOfRelates(branch_map, &content_Node);
		if (content_Node != NULL) {
			//设定relate从属于 to 节点，整个content中存在一个begin节点一个end节点
			string relate_id = content_Node->Attribute(RELATE_ID_TAG);
			string from_id = content_Node->Attribute(RELATE_BEGIN);
			string to_id = content_Node->Attribute(RELATE_END);

			// 确定branch_id唯一标识
			BranchSymbo* b_to = nullptr;
			BranchSymbo* b_from = nullptr;
			map<string, BranchSymbo*>::iterator it_ptr = this->branch_CN_C_ptr->find(to_id);
			if (it_ptr != this->branch_CN_C_ptr->end()) {
				b_to = it_ptr->second;
			}
			else {
				b_to = new BranchSymbo(to_id);
				this->branch_CN_C_ptr->insert(pair<string, BranchSymbo*>(to_id, b_to));
			}

			it_ptr = this->branch_CN_C_ptr->find(from_id);
			if (it_ptr != this->branch_CN_C_ptr->end()) {
				b_from = it_ptr->second;
			}
			else {
				b_from = new BranchSymbo(from_id);
				this->branch_CN_C_ptr->insert(pair<string, BranchSymbo*>(from_id, b_from));
			}


			// 按照目标节点与关系的对应方式绑定
			b_to->BindPreviousNode(b_from, &relate_id);
			b_from->BindNextNode(b_to, &relate_id);
		}

	} while (content_Node != NULL);

	return 0;
}
