#include "stdinoutchannel.hpp"
#include <iostream>
#include "cmdcheckprotocol.hpp"
#include <thread>
#include <fstream>

//---------- 标准输入类------------------
bool StdInChannel::Init(){

    return true;
}

bool StdInChannel::ReadFd(std::string& _input){

    std::cin >> _input;
    return true;
}

bool StdInChannel::WriteFd(std::string& _output){

    return false;
}

void StdInChannel::Fini(){

}

int StdInChannel::GetFd(){

    return STDIN_FILENO;
}

std::string StdInChannel::GetChannelInfo(){

    return "stdin";
}

AZinxHandler* StdInChannel::GetInputNextStage(BytesMsg& _oInput)
{
    // 返回给协议层信息
    return CmdCheck::getInstance();
}



//---------- 标准输出类------------------

bool StdOutChannel::Init(){
    return true;
}
bool StdOutChannel::ReadFd(std::string& _input){

    return false;
}
bool StdOutChannel::WriteFd(std::string& _output){

    // 展示消息
    std::cout << "回显消息>> " << _output << std::endl;

    return true;
}
void StdOutChannel::Fini(){


}
int StdOutChannel::GetFd(){

    return STDOUT_FILENO;
}
std::string StdOutChannel::GetChannelInfo(){

    return "stdout";
}
AZinxHandler* StdOutChannel::GetInputNextStage(BytesMsg& _oInput){

    return nullptr;
}



MyTcpData::MyTcpData(int fd) :
    ZinxTcpData(fd)
{
}
AZinxHandler* MyTcpData::GetInputNextStage(BytesMsg& _oInput)
{
    return CmdCheck::getInstance();
}



ZinxTcpData* MyTcpConnFactory::CreateTcpDataChannel(int _fd)
{
    return new MyTcpData(_fd);
}


