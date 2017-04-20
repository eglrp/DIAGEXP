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
	DataModel *model = new DataModel();
}