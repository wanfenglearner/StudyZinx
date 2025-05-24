#ifndef __CMDCHECK_H__
#define __CMDCHECK_H__
#include <zinx.h>

/*
        协议类
*/ 

// 命令识别类
class CmdCheck : public Iprotocol {
    
public:
	// 单例模式
	static CmdCheck* getInstance();
	
	UserData* raw2request(std::string _szInput) ;

	std::string* response2raw(UserData& _oUserData) ;

	Irole* GetMsgProcessor(UserDataMsg& _oUserDataMsg) ;

	Ichannel* GetMsgSender(BytesMsg& _oBytes) ;

	// 设置和获得 输出通道信息
	void setOutchannelInfo(std::string info);
	std::string getOutchannelInfo();

private:
	// 存储输出通道信息(info)
	std::string m_outchannelInfo{"stdout"};
};



#endif 