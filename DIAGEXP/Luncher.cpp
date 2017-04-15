// ConsoleApplication2.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <windows.h>
#include <thread>
#include "Pipe.h"
using namespace std;

void read();
void Loop();

Pipe * pipe;        //����ȫ�ֱ���


int main()//�Ǹ�ɶ������ǵ�������Main�ļ���Main������
{
	thread t1(read);//��ҪC++11��׼
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
		pipe->sendCommand(str);//�����ύ����
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