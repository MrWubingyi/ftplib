#include"socket_win.h"

/*���� Socket*/
u32 IoSocketListenSockCreat(IN u32 dwSvrId)
{

}

int SocketLastError(void)
{
	return WSAGetLastError();
}
// �������ݴ�����
u32 SocketSendErr()
{
	s32 nErr = SocketLastError();

	//hpcomprt(LIBFTP_LOG_DEBUG, "SocketSendErr send error=%d\n", nErr);

	if (nErr == WSAEWOULDBLOCK || nErr == WSAEINPROGRESS || nErr == WSAENETDOWN)
	{
		return TCPErr_SND_BUFFULL;// ���ͻ��������ˣ���Ҫ�ر�socket�������ݷ���ʧ��
	}

	return TCPErr_CLOSE;
}

/************************************************************************
��������IoSocketListenSockDestroy
���ܣ�	����socket
������

����ֵ���ɹ�����0��ʧ�ܡ�������
************************************************************************/
u32 SocketListenSockDestroy(IN u32 dwSvrId)
{

}

/************************************************************************
��������IoSocketEpollCreat
���ܣ�	����epoll
������

����ֵ���ɹ�����0��ʧ�ܡ�������
************************************************************************/
u32 SocketEpollCreat()
{
	//��������ֱ�ӷ��سɹ�
	return LIBFTP_OK;
}

/************************************************************************
��������IoSocketEpollDestroy
���ܣ�	����epoll
������

����ֵ���ɹ�����0��ʧ�ܡ�������
************************************************************************/
u32 SocketEpollDestroy()
{
	//��������ֱ�ӷ��سɹ�
	return LIBFTP_OK;
}

/************************************************************************
��������IoSocketHandleTcpRcvData
���ܣ�	����TcpSvr���¼�
������

����ֵ����
************************************************************************/
void SocketHandleTcpRcvData()
{

}



u32 SocketRcvData(SOCKET socket, char* buf)
{
	fd_set fd;
	fd_set fd2;
	FILE* tempstorage;				//char* g_fileBuf;          // ���ܴ洢�ļ�����
	s32 nReadlen = 0;		//�����ݳ���
	s32 nWritelen = 0;		//д���ݳ���
	int iErr = 0;
	u32 dwRet = 0;
	u8 abCount;//�����ݼ���
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