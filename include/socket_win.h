#ifndef _H_SOCKET_WIN_
#define _H_SOCKET_WIN_
#include"LibFtpstdafx.h"
#pragma once



#define TCPErr_OK    0

#define TCPErr_Base 1000
#define TCPErr_CLOSE   (TCPErr_Base+1)
#define TCPErr_SND_BUFFULL (TCPErr_Base+2)
#define TCPErr_RECV_NODATA	(TCPErr_Base+3)

#define SNDFILE_OK	0
#define SNDFILE_ERR	0xffffffff

#define MSGDATA_CHECKUP_NUM		0x56565656
/************************************************************************
函数名：IoSocketCloseSock
功能：	关闭socket
参数：

返回值：成功——0，失败——其他
************************************************************************/
u32 SocketCloseSock(SOCKHANDLE tSock);


/************************************************************************
函数名：IoSocketListenRcvTaskPrc
功能：	侦听任务接收线程,侦听建链请求
参数：

返回值：成功——0，失败——其他
************************************************************************/
int SocketListenRcvTaskPrc(u32 dwParam);

/************************************************************************
函数名：IoSocketListenSndTaskPrc
功能：	侦听任务发送线程,侦听建链请求
参数：

返回值：成功——0，失败——其他
************************************************************************/
int SocketListenSndTaskPrc(u32 dwParam);

#endif