#ifndef __ROLES_H__
#define __ROLES_H__

#include <zinx.h>

// 消息回显 类
class Echo : public Irole {

public:

	bool Init() ;

	UserData* ProcMsg(UserData& _poUserData) ;

	void Fini() ;

};


// 命令控制类
class CmdControl : public Irole {

public:

	bool Init() ;

	UserData* ProcMsg(UserData& _poUserData) ;

	void Fini() ;

private:

	// 记录输出通道
	Ichannel* m_pOutChannel;

};



// 添加日期前缀类
class AddDate : public Irole {

public:

	bool Init() ;

	UserData* ProcMsg(UserData& _poUserData) ;

	void Fini() ;

	// 获取和设置 日期前缀
	void setIsDate(bool isdate);
	bool getIsDate();

	// 得到当前日期的函数
    static std::string getCurrentDate();

private:
	
	// 记录是否需要添加日期前缀
	bool m_isDate;

};

#endif 