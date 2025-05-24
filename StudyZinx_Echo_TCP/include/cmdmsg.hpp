#ifndef __CMDDATA_H__
#define __CMDDATA_H__

#include <zinx.h>

// 消息类
class CmdMsg : public UserData {

public:
    CmdMsg();
    virtual ~CmdMsg();

    // 设置用户数据
    void setUserData(std::string userdata);

    // 获得用户数据
    std::string getUserdata() const;

    // 设置 获取 是否打开
    void setIsOpen(bool isopen);
    bool getIsOpen();
    
    // 设置 获取 是否为命令
    void setIsCmd(bool isCmd);
    bool getIsCmd();


    // 设置 获取 是否添加日期前缀
    void setNeedDate(bool needdate);
    bool getNeedDate();
    void setDateFlag(bool flag);
    bool getDateFlag();

private:

    // 存储用户数据
    std::string m_userData;

    // 记录当前信息是否是命令
    bool m_isCmd;
    // 记录当前信息是否可以输出
    bool m_isOpen;

    // 记录是否添加日期前缀
    bool m_needDate;
    bool m_dateFlag;

};

#endif 