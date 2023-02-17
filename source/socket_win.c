#include"socket_win.h"

/*创建 Socket*/
u32 IoSocketListenSockCreat(IN u32 dwSvrId)
{

}

int SocketLastError(void)
{
	return WSAGetLastError();
}
// 发送数据错误处理
u32 SocketSendErr()
{
	s32 nErr = SocketLastError();

	//hpcomprt(LIBFTP_LOG_DEBUG, "SocketSendErr send error=%d\n", nErr);

	if (nErr == WSAEWOULDBLOCK || nErr == WSAEINPROGRESS || nErr == WSAENETDOWN)
	{
		return TCPErr_SND_BUFFULL;// 发送缓冲区满了，不要关闭socket，但数据发送失败
	}

	return TCPErr_CLOSE;
}

/************************************************************************
函数名：IoSocketListenSockDestroy
功能：	销毁socket
参数：

返回值：成功——0，失败——其他
************************************************************************/
u32 SocketListenSockDestroy(IN u32 dwSvrId)
{

}

/************************************************************************
函数名：IoSocketEpollCreat
功能：	创建epoll
参数：

返回值：成功——0，失败——其他
************************************************************************/
u32 SocketEpollCreat()
{
	//不做处理，直接返回成功
	return LIBFTP_OK;
}

/************************************************************************
函数名：IoSocketEpollDestroy
功能：	销毁epoll
参数：

返回值：成功——0，失败——其他
************************************************************************/
u32 SocketEpollDestroy()
{
	//不做处理，直接返回成功
	return LIBFTP_OK;
}

/************************************************************************
函数名：IoSocketHandleTcpRcvData
功能：	处理TcpSvr读事件
参数：

返回值：无
************************************************************************/
void SocketHandleTcpRcvData()
{

}



u32 SocketRcvData(SOCKET socket, char* buf)
{
	fd_set fd;
	fd_set fd2;
	FILE* tempstorage;				//char* g_fileBuf;          // 接受存储文件内容
	s32 nReadlen = 0;		//读数据长度
	s32 nWritelen = 0;		//写数据长度
	int iErr = 0;
	u32 dwRet = 0;
	u8 abCount;//读数据计数
	u32 RcvfileLen = 0;
	struct timeval timeout;
	do {
		printf("start recv file:\n");
		do
		{

			dwRet = recv(socket, buf, sizeof(buf), 0);
			if (dwRet < 0)
			{
				printf("recv err :%d", WSAGetLastError());
				break;
			}
			/* write to stderr */
			write(2, buf, dwRet);
			/* write to temporary storage area */
			fwrite(buf, dwRet, 1, tempstorage);
			abCount += dwRet;
			RcvfileLen += dwRet;

			if (dwRet < sizeof(buf))
			{
				printf("\nsave in file err");
				return LIBFTP_System;
			}
		} while (dwRet > 0);
		printf("\ncount=%d", abCount);
		printf("\n recv=%d", dwRet);
		if (dwRet == LIBSSH2_ERROR_EAGAIN) {
			/* error or end of file */
			break;
		}

		timeout.tv_sec = 10;
		timeout.tv_usec = 0;

		FD_ZERO(&fd);
		FD_ZERO(&fd2);
		FD_SET(socket, &fd);
		FD_SET(socket, &fd2);

		/* wait for readable or writeable */
		dwRet = select(socket + 1, &fd, &fd2, NULL, &timeout);
		if (dwRet <= 0) {
			/* negative is error
			   0 is timeout */
			fprintf(stderr, "SFTP download timed out: %d\n", dwRet);
			break;
		}

		return nReadlen;
	} while (1);
}