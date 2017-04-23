#include "main.h"

/*ģ����ģ�Ϳ�����
**�����������ò���
**Processor.exe -fpath xmlfilepath
**������		ָ�����ص�Դ�ļ�·��
**Processor.exe -help
**��ʾ���������Ϣ
**/

int main(int argc, char* argv[]) {



	//�����������������ִ���
	if (argc < 3 || strcmp(argv[1], "-fpath")) {
		std::cout << "ERROR:����������������" << std::endl;
		return -1;
	}

	//���¿�ʼ����
	FileOperate *foperate = new FileOperate();
	DataModel *model = new DataModel();
	ModelProcessor *processor = new ModelProcessor();
	OperateAccept *IO_Port = new OperateAccept();

	foperate->EnsureProcFileExist(argv[2]);//ȷ��һ������һ���Ϸ�������ģ���ļ�
	model->InitModel(argv[2]);// ��������ģ���ļ�
	processor->InitProcessor(model, IO_Port);//װ�ػ�����ʩ
	processor->Loop();//������Ϣѭ���������


	return 0;
}