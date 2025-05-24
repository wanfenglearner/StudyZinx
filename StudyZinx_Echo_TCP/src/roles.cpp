#include "roles.hpp"
#include "cmdmsg.hpp"
#include "cmdcheckprotocol.hpp"
#include <chrono>

bool Echo::Init() {

    return true;
}

UserData* Echo::ProcMsg(UserData& _poUserData) {


    // 将数据进行发送

    GET_REF2DATA(CmdMsg, usermsg, _poUserData);
    CmdMsg* msg = new CmdMsg(usermsg);
    // 此消息必须是一个新的消息对象
    ZinxKernel::Zinx_SendOut(*msg, *(CmdCheck::getInstance()));

    return nullptr;
}

void Echo::Fini(){


}


// ---------------  命令控制类-------------------

bool CmdControl::Init() {

    // 设置下一个 Irole 对象是 添加日期类

    Irole* pRetRole = nullptr;

    for(const auto& role : ZinxKernel::Zinx_GetAllRole()) {

        auto ptmprole = dynamic_cast<AddDate*>(role);
        if(ptmprole != nullptr) {

            pRetRole = ptmprole;
            break;
        }

    }
    if(pRetRole != nullptr) {
        SetNextProcessor(*(pRetRole));
    }

    return true;
}

UserData* CmdControl::ProcMsg(UserData& _poUserData) {


    // 将消息进行转换 判断是否可以进行输出
    GET_REF2DATA(CmdMsg, msg, _poUserData);

    if(msg.getIsOpen()) {

        // 将输出通道添加到框架中
        if(m_pOutChannel != nullptr) {

            ZinxKernel::Zinx_Add_Channel(*(m_pOutChannel));
            m_pOutChannel = nullptr;
        }

    } 
    else {

        // 将输出通道从框架中删除
        auto pchannel = ZinxKernel::Zinx_GetChannel_ByInfo("stdout");
        if(pchannel != nullptr) {
            
            m_pOutChannel = pchannel;
            ZinxKernel::Zinx_Del_Channel(*(pchannel));

        }
    }


    return new CmdMsg(msg);
}

void CmdControl::Fini(){


}


// --------------- 添加日期前缀类-------------------
bool AddDate::Init() {

    // 设置下一个 Irole 对象是 消息回显类

    Irole* pRetRole = nullptr;

    for(const auto &role : ZinxKernel::Zinx_GetAllRole()) {

        auto ptmprole = dynamic_cast<Echo*>(role);

        if(ptmprole != nullptr) {

            pRetRole = role;
            break;
        }

    }

    if(pRetRole != nullptr) {
        SetNextProcessor(*(pRetRole));
    }

    return true;
}

UserData* AddDate::ProcMsg(UserData& _poUserData) {

    // 转换消息格式, 判断是否日期前缀
    GET_REF2DATA(CmdMsg, msg, _poUserData);

    CmdMsg* resultStr = nullptr;
    if(msg.getIsCmd()) {

        if(msg.getDateFlag()) {

            // 说明此消息代表添加日期的前缀
            this->setIsDate(msg.getNeedDate());
        }

    }
    else {

        resultStr = new CmdMsg(msg);
        // 当前消息不是命令 根据记录的 是否添加日期
        if(this->getIsDate()) {

            std::string dateStr = AddDate::getCurrentDate();
            resultStr->setUserData(std::string(dateStr + "  " + msg.getUserdata()));
        }
        else {
            resultStr->setUserData(msg.getUserdata());
        }
    }
    return resultStr;
}

void AddDate::Fini(){


}

// 获取和设置 日期前缀
void AddDate::setIsDate(bool isdate) {

    m_isDate = isdate;
}
bool AddDate::getIsDate() {

    return m_isDate;

}
	// 得到当前日期的函数
std::string AddDate::getCurrentDate() {

    auto tm_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    struct tm *ptm = localtime(&tm_t);

    char buf[50] = {0};
    sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d", ptm->tm_year + 1900, ptm->tm_mon + 1,
            ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

    return std::string(buf);

}