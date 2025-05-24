#include "cmdcheckprotocol.hpp"
#include "cmdmsg.hpp"
#include <cstring>
#include "roles.hpp"


CmdCheck* CmdCheck::getInstance() {

    static CmdCheck instance;
    return &instance;

}

UserData* CmdCheck::raw2request(std::string _szInput)
{

    // 判读是否输入了 exit 命令, 输入了则直接退出即可
    if(strcasecmp(_szInput.c_str(), "exit") == 0) {

        std::cout << "CmdCheck::raw2request 输入exit " << std::endl;
        ZinxKernel::Zinx_Exit();
        return nullptr;
    }

    // 将原始数据转换成 UserData类型
    CmdMsg* msg = new CmdMsg();
    msg->setUserData(_szInput);
    
    if(strcasecmp(_szInput.c_str(), "open") == 0) {

        // 将此消息设置为 命令 和 可以输出
        msg->setIsCmd(true);
        msg->setIsOpen(true);

    }
    
    if(strcasecmp(_szInput.c_str(), "close") == 0) {

        // 将此消息设置为 命令 和 不可以输出
        msg->setIsCmd(true);
        msg->setIsOpen(false);
    }
    
    if(strcasecmp(_szInput.c_str(), "date") == 0) {

        msg->setIsCmd(true);
        msg->setNeedDate(true);
        msg->setDateFlag(true);
    }

    if(strcasecmp(_szInput.c_str(), "closedate") == 0) {

        msg->setIsCmd(true);
        msg->setNeedDate(false);
        msg->setDateFlag(true);

    }


    return msg;
}

std::string* CmdCheck::response2raw(UserData& _oUserData)
{
    // 将 UserData类型转换成 string类型

    GET_REF2DATA(CmdMsg, msg, _oUserData);

    return new std::string(msg.getUserdata());


}

Irole* CmdCheck::GetMsgProcessor(UserDataMsg& _oUserDataMsg)
{
    // 根据命令不同, 将消息传递不同的 Irole对象
    std::cout << "CmdCheck::GetMsgProcessor>>" << _oUserDataMsg.szInfo  << "  " << _oUserDataMsg.szInfo.size() << std::endl;
    // 获得当前的信息的来源信息
    if(strcasecmp(_oUserDataMsg.szInfo.c_str(), "stdin") == 0) {

        // 说明此消息的来源是标准输入， 那么将此消息回显到标准输出
        this->setOutchannelInfo("stdout");
    }
    else
    {
        this->setOutchannelInfo(_oUserDataMsg.szInfo);
    }
    // 判断当前消息类型
    GET_REF2DATA(CmdMsg, msg, *(_oUserDataMsg.poUserData));
    // 记录真正返回的 对象
    Irole* pRetRole = nullptr;

    bool isCmd = msg.getIsCmd();

    for(const auto& role : ZinxKernel::Zinx_GetAllRole()) {

        if(isCmd) {

            auto ptmpchannel = dynamic_cast<CmdControl*>(role);
            if(ptmpchannel != nullptr) {
                pRetRole = ptmpchannel;
                break;
            }
        }
        else {

            auto ptmpchannel = dynamic_cast<AddDate*>(role);
            if(ptmpchannel != nullptr) {
                pRetRole = ptmpchannel;
                break;
            }

        }
    }

    return pRetRole;

}

Ichannel* CmdCheck::GetMsgSender(BytesMsg& _oBytes)
{
    // 传递给标准输出通道
    // 框架里 获取 标准输出通道 info
    return ZinxKernel::Zinx_GetChannel_ByInfo(this->getOutchannelInfo());
}


// 设置和获得 输出通道信息
void CmdCheck::setOutchannelInfo(std::string info) {

    m_outchannelInfo = info;
}
std::string CmdCheck::getOutchannelInfo() {

    return m_outchannelInfo;
}