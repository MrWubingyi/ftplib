#ifndef _H_THREAD_LIST_
#define _H_THREAD_LIST_
#pragma once

#include"ftpstdafx.h"
//线程数据结构
typedef struct tFtpLibThread
{
	u32 m_dwThreadId;		//线程索引
	u32 m_dwState;			//线程状态

	BOOL m_bIsRcvThread;	//是否为接收线程
	BOOL m_bThreadIsStart;	//线程是否启动

	u32 m_dwChnlHighLevel;		//高一级
	u32 m_dwChnlLowLevel;		//低一级

	u32 m_dwRouseCnt;		//唤醒次数

}TFtpLibThread;

//线程状态
typedef enum eFtpLibThreadState
{
	E_THREAD_STATE_FREE = 0,		//线程空闲，没有调用epollwait
	E_THREAD_STATE_RUNING ,			//正在运行

	E_THREAD_STATE_RCVWAITE ,		//正在接收数据，处于epollwait
	E_THREAD_STATE_RCVING ,			//正在接收数据，epollwait触发，正在接收数据
	E_THREAD_STATE_RCVBLOCK ,		//正在接收数据，在接收数据时阻塞

	E_THREAD_STATE_SNDWAITE ,		//正在接收数据，处于epollwait
	E_THREAD_STATE_SNDING ,			//正在接收数据，epollwait触发，正在接收数据
	E_THREAD_STATE_SNDBLOCK ,		//正在接收数据，在接收数据时阻塞
}EFtpLibThreadState;

TFtpLibThread *g_ptFtpLib_RcvThreadList ;	//接收线程
TFtpLibThread *g_ptFtpLib_SndThreadList ;	//发送线程


/************************************************************************
函数名：ThreadListInit
功能：	线程列表初始化
参数：
返回值：成功——0；	失败——其他
************************************************************************/
u32 ThreadListInit();

/************************************************************************
函数名：ThreadListUnInit
功能：	线程列表反初始化
参数：
返回值：成功——0；	失败——其他
************************************************************************/
u32 ThreadListUnInit();

/************************************************************************
函数名：ThreadListEpollThreadCreat
功能：	创建线程
参数：
返回值：成功——0；	失败——其他
************************************************************************/
u32 ThreadListEpollThreadCreat();
#endif