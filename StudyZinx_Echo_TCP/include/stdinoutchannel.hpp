#ifndef __STDINOUTCHANNEL_H__
#define __STDINOUTCHANNEL_H__
#include <zinx.h>
#include <ZinxTCP.h>

// 标准输入类
class StdInChannel : public Ichannel {

public:

    StdInChannel() = default;
    virtual ~StdInChannel() = default;


	bool Init();
	bool ReadFd(std::string& _input);
	bool WriteFd(std::string& _output);
	void Fini();
	int GetFd();
	std::string GetChannelInfo();
	AZinxHandler* GetInputNextStage(BytesMsg& _oInput);

};


// 标准输出类
class StdOutChannel : public Ichannel{

public:

    StdOutChannel() = default;
    virtual ~StdOutChannel() = default;


	bool Init();
	bool ReadFd(std::string& _input);
	bool WriteFd(std::string& _output);
	void Fini();
	int GetFd();
	std::string GetChannelInfo();
	AZinxHandler* GetInputNextStage(BytesMsg& _oInput);

};


// 自定义TCP数据类
class MyTcpData : public ZinxTcpData {

public:

	MyTcpData(int fd = -1);
	AZinxHandler* GetInputNextStage(BytesMsg& _oInput);

};

// 自定义 TCP连接工厂类
class MyTcpConnFactory : public IZinxTcpConnFact {

public:

	ZinxTcpData* CreateTcpDataChannel(int _fd);

};

#endif 