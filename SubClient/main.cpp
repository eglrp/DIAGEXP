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
	DataModel *model = new DataModel();
}