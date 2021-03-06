# DIAGEXP
> 自顶向下软件设计模式助手

## 软件设计目的
* 帮助软件开发人员在项目立项之初，方便快捷的设计软件架构，利用图形化的方式将软件架构表达出来，方便软件的理解和改进
* 在设计之初，帮助软件开发者明晰接口关系，降低重构概率
* 提供强大的重构工具，帮助软件开发者在开发的过程中重构更加合理高效的软件结构
* 提供运行环境，帮助开发者理解模块之间的交互关系，数据流向等信息
* 帮助软件开发者消除线程锁死锁现象
* 帮助软件开发者消除循环引用现象

## 软件结构设计
软件分为三个部分：
1. 软件交互界面：不同平台上采用不同技术编写
2. 软件数据模型与模型控制器：标准C++与平台API
3. 软件运行过程节点控制器：标准C++与平台API

不同部分之间采用匿名管道相互连接与通讯。
为了充分利用不同平台上的图形技术，不同平台上采用了不同的界面技术编写。
为了简化跨平台编程需求，因此软件交互界面集成最少的能力，只起到展示与交互功能，通用功能采用标准C++编写，在不同平台上编译一遍即可。

## 设计目标与当前进展
- [x] 设计软件概要架构
- [x] 设计软件界面概要交互方式
- [x] 设计软件不同部分通讯报文
- [x] 设计数据文件存储结构
- [x] 设计软件逻辑仿真过程软件运行方式
- [ ] 精细化软件各部分通讯报文，数据文件格式等细节
- [ ] 编写代码：块3，运行过程节点控制器
- [ ] 调试软件：块3，运行过程节点控制器
- [ ] 编写代码：块2，软件数据模型与模型控制器
- [ ] 调试软件：块2，软件数据模型与模型控制器
- [x] 编写代码：块1，交互界面定义
- [x] 编写代码：块1，交互式界面功能区分割
- [x] 编写代码：块1，交互式界面伸缩编辑区构建
- [x] 编写代码：块1，鼠标滑轮缩放
- [x] 编写代码：块1，交互式界面动态条目窗口绑定
- [ ] 编写代码：块1，交互式界面控件拖动操作
- [ ] 编写代码：块1，交互式界面控件拖方操作
- [ ] 编写代码：块1，交互式界面右键菜单
- [x] 编写代码：块1，交互式界面控件组合定义
- [ ] 调试软件：块1，交互界面功能窗口构建
- [ ] 调试软件：块1，交互式界面窗口绑定
- [ ] 将单一数据文件发展成为配置项目包裹，对界面未知，颜色，形状等显示细节文件等定义
- [ ] 软件完整性综合调试





- - -
April 19, 2017 12:52

独立开发一款软件实在是好烦啊。WPF使用实在是太繁琐了，Swing类库也不好用，还不如WPF，我手里也没有一本Swing的参考书，只能在网上搜索一些实例，开发很困难，因此放弃了。好歹WPF还有一本WPF编程宝典，还能看看。但是学习曲线好陡峭，让人不寒而栗。
我现在都不知道在其他两个平台上到底用什么技术好（MacOS上还是cocos吧，linux上呢？）。