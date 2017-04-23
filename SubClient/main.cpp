#include "main.h"

/*模型与模型控制器
**程序启动配置参数
**Processor.exe -fpath xmlfilepath
**程序名		指明加载的源文件路径
**Processor.exe -help
**显示程序帮助信息
**/

int main(int argc, char* argv[]) {



	//以下是正常工作部分代码
	if (argc < 3 || strcmp(argv[1], "-fpath")) {
		std::cout << "ERROR:程序启动参数错误！" << std::endl;
		return -1;
	}

	//以下开始工作
	FileOperate *foperate = new FileOperate();
	DataModel *model = new DataModel();
	ModelProcessor *processor = new ModelProcessor();
	OperateAccept *IO_Port = new OperateAccept();

	foperate->EnsureProcFileExist(argv[2]);//确保一定存在一个合法的数据模型文件
	model->InitModel(argv[2]);// 载入数据模型文件
	processor->InitProcessor(model, IO_Port);//装载基础设施
	processor->Loop();//进入消息循环处理过程


	return 0;
}