#include "cmdmsg.hpp"


CmdMsg::CmdMsg():
    m_isCmd(false),
    m_isOpen(true),
    m_needDate(false),
    m_dateFlag(false)
{
}


CmdMsg::~CmdMsg() {



}

// 设置用户数据
void CmdMsg::setUserData(std::string userdata) {

    m_userData = userdata;
}

// 获得用户数据
std::string CmdMsg::getUserdata() const {

    return m_userData;
}

// 设置 获取 是否打开
void  CmdMsg::setIsOpen(bool isopen) {

    m_isOpen = isopen;
}
bool CmdMsg::getIsOpen() {

    return m_isOpen;
}

// 设置 获取 是否为命令
void CmdMsg::setIsCmd(bool iscmd) {

    m_isCmd = iscmd;

}
bool CmdMsg::getIsCmd() {

    return m_isCmd;
}

// 设置 获取 是否添加日期前缀
void CmdMsg::setNeedDate(bool needdate) {

    m_needDate = needdate;

}


bool CmdMsg::getNeedDate() {

    return m_needDate;
}

void CmdMsg::setDateFlag(bool flag) {

    m_dateFlag = flag;
}
bool CmdMsg::getDateFlag() {

    return m_dateFlag;

}
