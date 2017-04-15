// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//
#include <windows.h>
#include <thread>
#include "Pipe.h"
using namespace std;

void read();
void Loop();

Pipe * pipe;        //属于全局变量


int main()//那个啥，你就是当作这是Main文件的Main方法不
{
	thread t1(read);//需要C++11标准
	thread t2(Loop);

	pipe = new Pipe("cmd");
	t1.join();
	t2.join();
	return 0;
}
void read() {

	while (true) {
		char str[200];
		cin >> str;
		pipe->sendCommand(str);//　　提交命令
	}
}

void Loop() {
	while (true) {
		Sleep(1000);
		if (pipe->getStatus() == -11) {
			cout << " ERROR " << endl;
			return;
		}
	}
}