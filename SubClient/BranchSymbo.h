#include"BasicSupport.h"

class BranchSymbo
{
public:
	BranchSymbo(std::string& node_id);
	virtual ~BranchSymbo();
	// ���ϼ��ڵ�
	virtual int BindPreviousNode(BranchSymbo* previousNode, std::string* relate_id);
	// ���¼��ڵ�
	virtual int BindNextNode(BranchSymbo* nextNode, std::string* relate_id);
	// ȷ��һ��Ҫ���豾�ڵ�Ϊbranch�����ݹ����е�һ�ڵ�
	virtual int ResetToContentHead();
	// ��һ�ڵ���ñ�����������ȷ�����ڵ㴦�ڵ�λ�ã����µݹ�����rankԽ��Խ��
	// ����ֵ��DOWNSTREAM_ERROR�������淢���˻ػ�֧·
	virtual int DownstreamArrayRankClear(int previousRank, std::vector<std::string>* avoidList);
	// ���ݣ����Ŷ��еȼ�,rankԽ��ԽС
	// ����ֵ��UPSTREAM_ERROR�������淢���˻ػ�֧·
	virtual int UpstreamArrayRankClear(int thisRank, std::vector<std::string>* avoidList);
	// ��ȡ��������
	virtual int GetRank();
private:
	int rank;
	// ���ڵ��id���
	std::string node_id;
	// ��һ���ڵ�
	std::map<std::string, BranchSymbo*>* upstreamNodeC;
	// ��һ���ڵ�
	std::map<std::string, BranchSymbo*>* downstreamNodeC;
public:
	// ��ȡΨһ��ʶ��
	virtual int GetBranchNode_id(std::string* branchNode_id);
	// ��ӡbranch���ݵ�����
	virtual int PrintItSelfContent(std::string* stringBuf);
};

