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


// ��ʼ��ģ��branchManage
int BranchManage::Init(DataModel* model)
{
	this->model_ptr = model;
	return 0;
}


int BranchManage::PrintOutBranchContent(const char * branch_map, std::string* stringBuf)
{
	// �������з�֧���ݣ����������ýڵ��ϵ��ʾ
	this->LoadBranchContentNode(branch_map);
	// �������нڵ�˳��
	this->TrimBranchContent();
	// ��ӡ�ڵ�����
	this->PrintBranch(stringBuf);

	return 0;
}


// �ڲ����������֧����
int BranchManage::TrimBranchContent()
{
	BranchSymbo* b_one = this->branch_CN_C_ptr->begin()->second;
	vector<string> c = vector<string>();

	// ȷ����ʱ�ο���
	b_one->ResetToContentHead();
	// ģ���¼������ϼ��ڵ㣬b_one�����ϼ��ڵ�
	b_one->UpstreamArrayRankClear(1, &c);
	// ģ���ϼ��ڵ�����¼��ڵ㣬b_one�����¼��ڵ�
	b_one->DownstreamArrayRankClear(-1, &c);

	return 0;
}


// ��ӡ��֧����
int BranchManage::PrintBranch(std::string* stringBuf)
{
	map<string, BranchSymbo*>::iterator it_ptr = this->branch_CN_C_ptr->begin();
	int min_atnow = 0;
	BranchSymbo* tmp = nullptr;

	for (; it_ptr != this->branch_CN_C_ptr->end(); ++it_ptr) {
		int rank_thisnode = it_ptr->second->GetRank();

		if (rank_thisnode <= min_atnow) {
			tmp = it_ptr->second; // ���õ���Ӧ����begin�ڵ�
		}
	}

	// ѭ�����´�ӡ============================================
	tmp->PrintItSelfContent(stringBuf);

	return 0;
}


// ���ط�֧���ݽڵ㺯��
int BranchManage::LoadBranchContentNode(const char* branch_map)
{
	TiXmlElement* content_Node = nullptr;
	do {
		// ��ȡһ���÷�֧�Ľڵ㣬����������ڵ�
		this->model_ptr->LocateNextOneOfRelates(branch_map, &content_Node);
		if (content_Node != NULL) {
			//�趨relate������ to �ڵ㣬����content�д���һ��begin�ڵ�һ��end�ڵ�
			string relate_id = content_Node->Attribute(RELATE_ID_TAG);
			string from_id = content_Node->Attribute(RELATE_BEGIN);
			string to_id = content_Node->Attribute(RELATE_END);

			// ȷ��branch_idΨһ��ʶ
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


			// ����Ŀ��ڵ����ϵ�Ķ�Ӧ��ʽ��
			b_to->BindPreviousNode(b_from, &relate_id);
			b_from->BindNextNode(b_to, &relate_id);
		}

	} while (content_Node != NULL);

	return 0;
}
