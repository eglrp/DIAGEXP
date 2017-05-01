#include "DataModel.h"
#include "OperateAccept.h"
#include "BasicSupport.h"
#include "BranchSymbo.h"

class BranchManage
{
public:
	BranchManage();
	virtual ~BranchManage();
	// ��ʼ��ģ��branchManage
	virtual int Init(DataModel* model);
	virtual int PrintOutBranchContent(const char * branch_map, std::string* stringBuf);
private:
	// �ڲ����������֧����
	virtual int TrimBranchContent();
	// ��ӡ��֧����
	virtual int PrintBranch(std::string* stringBuf);
	// ��֧�ڵ����� branch_contentnode_collection
	std::map<std::string, BranchSymbo*>* branch_CN_C_ptr;
	DataModel* model_ptr;
	// ���ط�֧���ݽڵ㺯��
	virtual int LoadBranchContentNode(const char* branch_map);
};

