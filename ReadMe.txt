整个应用程序被重新划分为三个部分
	1.界面UI
	2.数据模型与模型控制器
	3.运行分支元素判定控制器模块
	每个部分之间采用文本协议的方式进行通讯，类比于SQL

	界面在不同的平台采用不同的技术，在界面上功能最小化，减少跨平台难度。
	数据模型与模型控制器、运行分支元素判定控制器模块则采用标准C++与少量平台API开发，最大限度的跨平台，有利于不同平台重用代码，只需要在不同平台上重新编译一下即可
	三者之间1->2->3都采用匿名管道技术进行连接。