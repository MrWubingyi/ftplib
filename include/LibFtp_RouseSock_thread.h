#ifndef _H_ROUSE_SOCKTHREAD_WIN_
#define _H_ROUSE_SOCKTHREAD_WIN_
#include "LibFtpstdafx.h"

//唤醒socket
typedef struct tLibFtpRouseSocket
{
	u32 m_dwSndThreadSock;		//唤醒发送线程sock
	u32 m_dwRcvThreadSock;		//唤醒接收线程sock

	u32 m_dwThreadIp;			//Ip
	u16 m_wSndThreadPort;		//发送线程端口
	u16 m_wRcvThreadPort;		//接收线程端口

	u32 m_dwMaxMsgLen;			//本地消息最大长度，单位字节，默认1k
	u32 m_dwLocalMsgSndNum;		//本地消息发送数		
	u32 m_dwLocalMsgSndSucNum;	//本地消息发送成功数		
	u32 m_dwLocalEvtCbNum;		//上报事件数	

}TLibFtpRouseSocket;

//消息类型
typedef enum eLibFtpReuseMsgType
{
	E_LIBFTP_ROUSE_THREAD_RCV = 0x10,		//唤醒接收线程
	E_LIBFTP_ROUSE_USER_DATA,				//唤醒接收线程——发送用户数据

	E_LIBFTP_ROUSE_THREAD_SND = 0x20,		//唤醒发送线程

}ELibFtpReuseMsgType;

//消息类型
typedef struct tLibFtpLocalUserMsgData
{
	u32 m_dwUserMsgType;	//用户消息类型
	char* m_pData;			//消息指针
	u32 m_dwDataLen;		//消息长度
}TLibFtpLocalUserMsgData;

#pragma pack(push) //保存对齐状态
#pragma pack(1)

//消息头，若为唤醒消息，则只有头
typedef struct tLibFtpRouseMsgHeader
{
	u8 m_chFirstFlag;			//第一位标识，HPCOM_DATAHEADER_FIRST
	u8 m_chSecondFlag;			//第二位标识，HPCOM_DATAHEADER_SEC
	u8 m_chVersion;				//版本号，HPCOM_VER

	u32 m_dwMsgType;			//消息类型
	u32 m_dwUserMsgType;		//用户消息类型,当msgtype为E_HPCOM_ROUSE_USER_DATA时用
	u32 m_dwDataLen;			//消息长度,当为用户数据时有效
}TLibFtpRouseMsgHeader;

#pragma pack(pop)

TLibFtpRouseSocket g_RouseThreadSock;		//唤醒线程socket

/************************************************************************
函数名：RouseThreadSockCreat
功能：	创建唤醒线程socket
参数：

返回值：成功——0，失败——其他
************************************************************************/
u32 RouseThreadSockCreat();

/************************************************************************
函数名：RouseThreadSockDestroy
功能：	销毁唤醒线程socket
参数：

返回值：成功——0，失败——其他
************************************************************************/
u32 RouseThreadSockDestroy();

/************************************************************************
函数名：RouseThreadSndRouseMsg
功能：	发送消息
参数：

返回值：成功——0，失败——其他
************************************************************************/
u32 RouseThreadSndMsg(IN ELibFtpReuseMsgType eMsg, IN u32 dwType, IN u8* pData, IN u32 dwDataLen);

/************************************************************************
函数名：RouseThreadRecvMsg
功能：	接收消息
参数：

返回值：成功——0，失败——其他
************************************************************************/
u32 RouseThreadRecvMsg(IN ELibFtpReuseMsgType eMsg);

#endif