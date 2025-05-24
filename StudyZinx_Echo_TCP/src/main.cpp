#include "stdinoutchannel.hpp"
#include <iostream>
#include "roles.hpp"
#include <memory>

int main() {

    
    // 初始化框架
    ZinxKernel::ZinxKernelInit();

    // 添加内容到框架
    ZinxKernel::Zinx_Add_Channel(*(new StdInChannel()));
    ZinxKernel::Zinx_Add_Channel(*(new StdOutChannel()));

    ZinxKernel::Zinx_Add_Role(*(new Echo()));
    ZinxKernel::Zinx_Add_Role(*(new AddDate()));
    ZinxKernel::Zinx_Add_Role(*(new CmdControl()));

    ZinxKernel::Zinx_Add_Channel(*(new ZinxTCPListen(8989, new MyTcpConnFactory())));
    // 运行框架
    ZinxKernel::Zinx_Run();

    // 完成框架
    ZinxKernel::ZinxKernelFini();

    return 0;
}