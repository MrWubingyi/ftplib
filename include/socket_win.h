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
��������IoSocketCloseSock
���ܣ�	�ر�socket
������

����ֵ���ɹ�����0��ʧ�ܡ�������
************************************************************************/
u32 SocketCloseSock(SOCKHANDLE tSock);


/************************************************************************
��������IoSocketListenRcvTaskPrc
���ܣ�	������������߳�,������������
������

����ֵ���ɹ�����0��ʧ�ܡ�������
************************************************************************/
int SocketListenRcvTaskPrc(u32 dwParam);

/************************************************************************
��������IoSocketListenSndTaskPrc
���ܣ�	�����������߳�,������������
������

����ֵ���ɹ�����0��ʧ�ܡ�������
************************************************************************/
int SocketListenSndTaskPrc(u32 dwParam);

#endif