#include "LibFtp.h"



TCommInitParam		g_tCommInitParam = { 0 };//公共参数
TLibFtpInitPara		g_tFtpLibInitPara = { 0 };//初始化参数数据结构
TLibFtpBaseInfo		g_tFtpLibRunBaseInfo = { 0 };	//基本运行信息
TFtpLibTranFileInfo	g_FtpLibRcvFileInfo,g_tFtpLibTranFileInfo = { 0 };			//接收，发送文件信息


u32 g_dwFtpLibMemTag = 0;							//内存标签
u32 g_dwFtpLibXmlTag = INVALID_U32ID;							//Xml标签

#define STORAGE "D:/tmp/VSCodeUserSetup-x64-1.49.2.exe" /* this is the local file name this example uses to store the downloaded file in */

FILE* tempstorage;				//char* g_fileBuf;          // 接受存储文件内容

 char* ip							= "192.168.50.41";
 int port							= 21;
 char* keyfile1					= "~/.ssh/id_rsa.pub";
 char* keyfile2				= "~/.ssh/id_rsa";
 char* username				= "sxd";
 char* password				= "ds";
 char* sftppath				= "VSCodeUserSetup-x64-1.49.2.exe";// 保存服务器发送过来的文件名
 char* LinuxFtpProtrol		= "SSH-2.0-OpenSSH_7.4\r\n";
 char* WinFtpProtrol		= "220 Microsoft FTP Service\r\n";
 char* CodingFormat		= "UTF8 ON";
 char* LocalIP					= "192.168.50.199";
 int* SigSendPort			= 0;//主被动模式信令端口 默认63000    
 char* PortCommandSuc = "200 PORT command successful";
 char* NLSTCommandSuc = "125 Data connection already open; Transfer starting.";
/// <summary>
/// 初始化libftp协议栈
/// </summary>
void LibFtpInit(IN  TCommInitParam *ptCommInitParam, IN TLibFtpInitPara tFtpLibInitPara)
{
	u32 dwRet = 0;

	dwRet = LibFtpSaveInitParam(ptCommInitParam, tFtpLibInitPara);//初始化参数

	dwRet = InitFtpSocket();//初始化SOCKET
	if (dwRet != 0)
	{
		printf("SOCKET init faild");
		return;
	}
	printf("SOCKET OK\n");

	dwRet = libssh2_init(0);//初始化libssh库


	if (dwRet != 0)
	{
		printf("libssh init faild");
		return;
	}
	printf("libssh2_init OK\n");
	
	//初始化telnet
	//初始化服务列表
	//初始化客户端列表
	//初始化客户端列表服务
	//线程初始化
	//创建唤醒socket
	//创建epoll
	//创建线程
	//初始化SOCKET

}

/// <summary>
/// 保存初始化参数
/// </summary>
u32 LibFtpSaveInitParam(IN  TCommInitParam *ptCommInit, IN TLibFtpInitPara tInitPara)
{
	if (NULL == tInitPara.m_pHpComEventPrc ||
		(0 == tInitPara.m_dwSvrNum && 0 == tInitPara.m_dwCltNum && 0 == tInitPara.m_dwSingleRRCltNum) ||
		NULL == ptCommInit)
	{
		return LIBFTP_ParamErr;
	}
	
	g_tFtpLibRunBaseInfo.m_dwSvrNum = tInitPara.m_dwSvrNum;		//服务最大数
	g_tFtpLibRunBaseInfo.m_dwCltNum = tInitPara.m_dwCltNum;		//客户端最大数
	g_tFtpLibRunBaseInfo.m_dwSingleRRCltNum = tInitPara.m_dwSingleRRCltNum;	//单次请求客户端最大数

	g_tFtpLibRunBaseInfo.m_dwRcvThreadNum = tInitPara.m_dwRcvThreadNum;		//接收线程数
	if (0 >= g_tFtpLibRunBaseInfo.m_dwRcvThreadNum)
	{
		g_tFtpLibRunBaseInfo.m_dwRcvThreadNum = 10;		//设置默认值
	}
	g_tFtpLibRunBaseInfo.m_dwSndThreadNum = tInitPara.m_dwSndThreadNum;		//发送线程数
	if (0 >= g_tFtpLibRunBaseInfo.m_dwSndThreadNum)
	{
		g_tFtpLibRunBaseInfo.m_dwSndThreadNum = 4;		//设置默认值
	}
	g_tFtpLibRunBaseInfo.m_dwSRRCheckTime = tInitPara.m_dwSRRCheckTimerSec;		//SRR检查时间
	if (0 >= g_tFtpLibRunBaseInfo.m_dwSRRCheckTime)
	{
		g_tFtpLibRunBaseInfo.m_dwSRRCheckTime = 30;		//SRR检查时间
	}

#ifdef HPCOM_WIN32
	g_tFtpLibRunBaseInfo.m_dwRcvThreadNum = 1;		//Windows默认接收线程数为1
	g_tFtpLibRunBaseInfo.m_dwSndThreadNum = 1;		//Windows默认发送线程数为1
#endif

	g_RouseThreadSock.m_wRcvThreadPort = tInitPara.m_wRcvRousePort;		//接收线程唤醒端口
	if (0 == g_RouseThreadSock.m_wRcvThreadPort)
	{
		return LIBFTP_ParamErr;
		//g_RouseThreadSock.m_wRcvThreadPort = 9000;
	}
	g_RouseThreadSock.m_wSndThreadPort = tInitPara.m_wSndRousePort;		//发送线程唤醒端口
	if (0 == g_RouseThreadSock.m_wSndThreadPort)
	{
		return LIBFTP_ParamErr;
		//g_RouseThreadSock.m_wSndThreadPort = 9001;
	}

	g_RouseThreadSock.m_dwMaxMsgLen = tInitPara.m_dwMaxLocalMsgLen;		//本地消息最大长度
	if (0 == g_RouseThreadSock.m_dwMaxMsgLen)
	{
		g_RouseThreadSock.m_dwMaxMsgLen = 1024;
	}

	g_tFtpLibRunBaseInfo.m_dwAllChnlMaxNum = tInitPara.m_dwAllChnlMaxNum;	//所有通道最大数
	if (LIBFTP_EPOLLEVENT_NUM >= g_tFtpLibRunBaseInfo.m_dwAllChnlMaxNum)
	{
		g_tFtpLibRunBaseInfo.m_dwAllChnlMaxNum = LIBFTP_CONNECTFD_SIZE;		//设置默认值
	}
	g_tFtpLibRunBaseInfo.m_pFtpLibEventPrc = tInitPara.m_pHpComEventPrc;		//回调事件
	g_tFtpLibRunBaseInfo.m_dwExistSvrCnt = 0;	//设置服务数
	g_tFtpLibRunBaseInfo.m_dwExistCltCnt = 0;	//设置客户端数
	g_tFtpLibRunBaseInfo.m_dwRcvEpollFd = LIBFTP_INVALID_SOCKET;		//设置server中的socket
	g_tFtpLibRunBaseInfo.m_dwSndEpollFd = LIBFTP_INVALID_SOCKET;		//设置server中的socket
	g_tCommInitParam = *ptCommInit;		//公共参数

	return LIBFTP_OK;
}

static int waitsocket(int socket_fd, LIBSSH2_SESSION* session)
{
	struct timeval timeout;
	int rc;
	fd_set fd;
	fd_set* writefd = NULL;
	fd_set* readfd = NULL;
	int dir;

	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	FD_ZERO(&fd);

	FD_SET(socket_fd, &fd);

	/* now make sure we wait in the correct direction */
	dir = libssh2_session_block_directions(session);

	if (dir & LIBSSH2_SESSION_BLOCK_INBOUND)
		readfd = &fd;

	if (dir & LIBSSH2_SESSION_BLOCK_OUTBOUND)
		writefd = &fd;

	rc = select(socket_fd + 1, readfd, writefd, NULL, &timeout);

	return rc;
}


int main(int argc, char* argv[])
{
	const char* fingerprint;
	int i, auth_pw = 0;
	char* userauthlist;
	int dwRet;
	u8* g_recvBuf = ""; // 接受消息缓冲区
	struct sockaddr_in	SigSerAddr, //FTP服务器  控制通道  对端地址端口
									TransSerAddr, //FTP服务器  传输通道  WIN 被动模式下：对端地址端口     主动模式下：本端地址端口
									LinuxTransSerAddr,						//FTP服务器                  LINUX 文件传输 对端地址端口
									TransFileSerAddr,////FTP服务器  文件通道  WIN 被动模式下：对端地址端口     主动模式下：本端地址端口
									SigClientAddr, //FTP客户端  控制通道  本端地址端口
									TransClientAddr, //FTP客户端  传输通道  WIN 被动模式下：对端地址端口     主动模式下：本端地址端口
									LinuxTransClientAddr,									//FTP客户端                  LINUX 文件传输 本端地址端口
									TransFileClientAddr;//文件通道  WIN 被动模式下：对端地址端口     主动模式下：本端地址端口

	char* ipAddress[INET_ADDRSTRLEN];//保存点分十进制的ip地址
	struct timeval timeout;
	char Comma = ',';//逗号
	char FullPoint = '.';//点号
	char DstIp[1024];//192，168，xxx，xxx格式的ip

	fd_set fd;
	fd_set fd2;


#ifdef WIN32
	//初始化sock
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))        // 启动协议,成功返回0
	{
		printf("WSAStartup faild: %d\n", WSAGetLastError());
		return;
	}
	printf("FtpInitWinSocket OK\n");
#endif // WIN32

	//初始化libssh库
	dwRet = libssh2_init(0);
	if (dwRet != 0)
	{
		printf("libssh init faild");
		return;
	}
	printf("libssh2_init OK\n");

	//创建信令链路server socket套接字 地址、端口号,AF_INET是IPV4
	SOCKET SigSerfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//创建传输链路server socket套接字 地址、端口号,AF_INET是IPV4
	SOCKET TransSerfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//创建文件传输链路server socket套接字 地址、端口号,AF_INET是IPV4
	SOCKET TransFileSerfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == SigSerfd)
	{
		printf("Sigsocket faild:%d", WSAGetLastError());
		return;
	}
	if (INVALID_SOCKET == TransSerfd)
	{
		printf("Sigsocket faild:%d", WSAGetLastError());
		return;
	}
	if (INVALID_SOCKET == TransFileSerfd)
	{
		printf("Sigsocket faild:%d", WSAGetLastError());
		return;
	}
	printf("All socket OK:SigSerfd=%lld，TransSerfd=%lld，TransFileSerfd=%lld\n", SigSerfd, TransSerfd,TransFileSerfd);


	// 给SigSer socket绑定对端IP地址和端口号
	SigSerAddr.sin_family = AF_INET;
	SigSerAddr.sin_port = htons(port);                       // htons把本地字节序转为网络字节序
	SigSerAddr.sin_addr.S_un.S_addr = inet_addr(ip); // 服务器的IP地址
	// 给TransSer socket绑定对端IP地址和端口号
	LinuxTransSerAddr.sin_family = AF_INET;
	LinuxTransSerAddr.sin_port = htons(port);                       // htons把本地字节序转为网络字节序
	LinuxTransSerAddr.sin_addr.S_un.S_addr = inet_addr(ip); // 服务器的IP地址
	//绑定客户端（本端）控制通道的ip端口
	SigClientAddr.sin_family = AF_INET;
	if(SigSendPort!=0)//不填为随机
	{
	SigClientAddr.sin_port = htons(SigSendPort);
	}
	SigClientAddr.sin_addr.S_un.S_addr = inet_addr(LocalIP);//本地IP
	bind(SigSerfd, (struct sockaddr*)&SigClientAddr, sizeof(SigClientAddr));

	// 连接到服务器
	if (0 != connect(SigSerfd, (struct sockaddr*)&SigSerAddr, sizeof(SigSerAddr)))
	{
		printf("connect faild:%d", WSAGetLastError());
		return;
	}
	printf("connect OK:\n");

	//int* clientAddrLen = sizeof(SigClientAddr);//临时指针，给getsockname的长度使用
	int* SigSerAddrLen= sizeof(SigSerAddr);
	dwRet = getsockname(SigSerfd, (struct sockaddr*)&SigSerAddr, &SigSerAddrLen);//获取tcp客户端端口
	printf("port=%d\n", ntohs(SigSerAddr.sin_port));
	
	//绑定主动模式指令端口
	TransSerAddr.sin_family = AF_INET;
	int tmpTransSendPort = ntohs(SigSerAddr.sin_port);//端口转换为本地字节数
	tmpTransSendPort++;
	TransSerAddr.sin_port = htons(tmpTransSendPort);//本地端口+1
	TransSerAddr.sin_addr.S_un.S_addr = inet_addr(LocalIP);//本地IP
	bind(TransSerfd, (struct sockaddr*)&TransSerAddr, sizeof(TransSerAddr));

	//绑定主动模式文件传输端口
	TransFileSerAddr.sin_family = AF_INET;
	tmpTransSendPort++;
	TransFileSerAddr.sin_port = htons(tmpTransSendPort);//本地端口+2
	TransFileSerAddr.sin_addr.S_un.S_addr = inet_addr(LocalIP);//本地IP
	bind(TransFileSerfd, (struct sockaddr*)&TransFileSerAddr, sizeof(TransFileSerAddr));


	char* buf;
	buf = malloc(4096);
	char* transbuf;
	transbuf= malloc(4096);
	char* transfilebuf;
	transfilebuf = malloc(FILE_BUF_SIZE);

	//接收传输的版本号：WIN或LIUNX
	dwRet = recv(SigSerfd, buf, 4096, 0);
	if (0 == dwRet)
	{
		perror("recv");
		exit(EXIT_FAILURE);
	}
	buf[dwRet] = '\0';
	printf("%s", buf);
	sscanf(buf, "220");
	if (220 != 220 && 1)
	{
	exit(EXIT_FAILURE);
	}

//检查为win还是linux的ftp服务器
	if (strcmp(buf, WinFtpProtrol))
	{

		//	Linux的ftp服务器
		
		// 连接到服务器
		if (0 != connect(TransSerfd, (struct sockaddr*)&LinuxTransSerAddr, sizeof(LinuxTransSerAddr)))
		{
			printf("connect faild:%d", WSAGetLastError());
			return;
		}
		printf("connect OK:\n");//连接成功
		char* LinuxTransClientAddrLen = sizeof(LinuxTransClientAddr);
		dwRet = getsockname(TransSerfd, (struct sockaddr*)&LinuxTransClientAddr, &LinuxTransClientAddrLen);//获取tcp客户端端口
		if (dwRet != LIBFTP_OK)
		{
			printf("get sock ip:port faild");
			return LIBFTP_System;
		}
		printf("TransClient:client ddress = %s:%d\n", inet_ntop(AF_INET, &TransClientAddr.sin_addr, ipAddress, sizeof(ipAddress)), ntohs(TransClientAddr.sin_port));




		LIBSSH2_SESSION* session; //ssh会话
		LIBSSH2_SFTP* sftp_session;//sftp会话
		LIBSSH2_SFTP_HANDLE* sftp_handle;//sftp句柄


		session = libssh2_session_init();//ssh会话初始化
		if (!session)
			return -1;

		/* Since we have set non-blocking, tell libssh2 we are blocking */
		libssh2_session_set_blocking(session, 1);//设置ssh会话阻塞

		/* ... start it up. This will 版本协商（trade welcome banners）,密钥交换（ exchange keys）,
		 * and 加密算法协商（setup crypto）, 压缩算法协商compression, and MAC layers
		 */
		dwRet = libssh2_session_handshake(session, TransSerfd);
		if (dwRet) {
			fprintf(stderr, "Failure establishing SSH session: %d\n", dwRet);
			return -1;
		}

		/* At this point we havn't yet authenticated.  The first thing to do
		 * is check the hostkey's fingerprint against our known hosts Your app
		 * may have it hard coded, may go to a file, may present it to the
		 * user, that's your call
		 */
		fingerprint = libssh2_hostkey_hash(session, LIBSSH2_HOSTKEY_HASH_SHA1);//检查密钥
		fprintf(stderr, "Fingerprint: ");
		for (i = 0; i < 20; i++) {
			fprintf(stderr, "%02X ", (unsigned char)fingerprint[i]);
		}
		fprintf(stderr, "\n");


		for (i = 0; i < 20; i++) {
			printf(stderr, "%02X ", (unsigned char)fingerprint[i]);
		}
		printf(stderr, "\n");
		/* check what authentication methods are available 检查可用的身份验证方法*/
		userauthlist = libssh2_userauth_list(session, username, strlen(username));

		printf(stderr, "Authentication methods: %s\n", userauthlist);
		if (strstr(userauthlist, "password") != NULL) {
			auth_pw |= 1;
		}
		if (strstr(userauthlist, "keyboard-interactive") != NULL) {
			auth_pw |= 2;
		}
		if (strstr(userauthlist, "publickey") != NULL) {
			auth_pw |= 4;
		}
		if (auth_pw & 1) {
			/* We could authenticate via password 通过用户名密码身份验证 */
			if (libssh2_userauth_password(session, username, password)) {
				fprintf(stderr, "Authentication by password failed.\n");
				goto shutdown;
			}
		}
		else if (auth_pw & 2) {
			/* Or via keyboard-interactive */
			if (libssh2_userauth_keyboard_interactive(session, username,
				&static_kbd_callback)) {
				fprintf(stderr,
					"\tAuthentication by keyboard-interactive failed!\n");
				goto shutdown;
			}
			else {
				fprintf(stderr,
					"\tAuthentication by keyboard-interactive succeeded.\n");
			}
		}
		else if (auth_pw & 4) {
			/* Or by public key */
			if (libssh2_userauth_publickey_fromfile(session, username, keyfile1,
				keyfile2, password)) {
				fprintf(stderr, "\tAuthentication by public key failed!\n");
				goto shutdown;
			}
			else {
				fprintf(stderr, "\tAuthentication by public key succeeded.\n");
			}
		}
		else {
			fprintf(stderr, "No supported authentication methods found!\n");
			goto shutdown;
		}

		fprintf(stderr, "libssh2_sftp_init()!\n");
		sftp_session = libssh2_sftp_init(session);

		if (!sftp_session) {
			fprintf(stderr, "Unable to init SFTP session\n");
			goto shutdown;
		}
		
		fprintf(stderr, "libssh2_sftp_open()!\n");
		//打开写入的文件
		tempstorage = fopen(STORAGE, "wb");
		if (!tempstorage) {
			fprintf(stderr, "Can't open temp storage file %s\n", STORAGE);
			goto shutdown;
		}
		/* Request a file via SFTP 通过路径请求文件 */
		do {
			sftp_handle = libssh2_sftp_open(sftp_session, sftppath,
				LIBSSH2_FXF_READ, 0);

			if (!sftp_handle) {
				if (libssh2_session_last_errno(session) != LIBSSH2_ERROR_EAGAIN) {
					fprintf(stderr, "Unable to open file with SFTP\n");
					goto shutdown;
				}
				else {
					fprintf(stderr, "non-blocking open\n");
					waitsocket(TransSerfd, session); /* now we wait */
				}
			}
		} while (!sftp_handle);

		fprintf(stderr, "libssh2_sftp_open() is done, now receive data!\n");
		do {
			do {
				/* read in a loop until we block */
				dwRet = libssh2_sftp_read(sftp_handle, g_recvBuf, sizeof(g_recvBuf));
				fprintf(stderr, "libssh2_sftp_read returned %d\n",
					dwRet);

				if (dwRet > 0) {
					/* write to stderr */
					write(2, g_recvBuf, dwRet);
					/* write to temporary storage area */
					fwrite(g_recvBuf, dwRet, 1, tempstorage);
				}
			} while (dwRet > 0);

			if (dwRet != LIBSSH2_ERROR_EAGAIN) {
				/* error or end of file */
				break;
			}

			timeout.tv_sec = 10;
			timeout.tv_usec = 0;

			FD_ZERO(&fd);
			FD_ZERO(&fd2);
			FD_SET(TransSerfd, &fd);
			FD_SET(TransSerfd, &fd2);

			/* wait for readable or writeable */
			dwRet = select(TransSerfd + 1, &fd, &fd2, NULL, &timeout);
			if (dwRet <= 0) {
				/* negative is error
				   0 is timeout */
				fprintf(stderr, "SFTP download timed out: %d\n", dwRet);
				break;
			}

		} while (1);

		libssh2_sftp_close(sftp_handle);
		fclose(tempstorage);

		tempstorage = fopen(STORAGE, "rb");
		if (!tempstorage) {
			/* weird, we can't read the file we just wrote to... */
			fprintf(stderr, "can't open %s for reading\n", STORAGE);
			goto shutdown;
		}


		libssh2_sftp_shutdown(sftp_session);

	shutdown:

		libssh2_session_disconnect(session, "Normal Shutdown");
		libssh2_session_free(session);


	}
	else {
		//winFtp

		//指定编码格式
		sprintf(buf, "OPTS %s\r\n", CodingFormat);
		dwRet = send(SigSerfd, buf, strlen(buf), 0);
		if (0 >= dwRet)
		{
			perror("send");
			exit(EXIT_FAILURE);
		}
		printf("send:%s", buf);
		dwRet = recv(SigSerfd, buf, 4096, 0);
		if (0 == dwRet)
		{
			perror("recv");
			exit(EXIT_FAILURE);
		}
		buf[dwRet] = '\0';
		printf("%s", buf);
		sscanf(buf, "220");
		if (220 != 220 && 1)
		{
			exit(EXIT_FAILURE);
		}


		//发送用户名
		sprintf(buf, "USER %s\r\n", username);
		dwRet = send(SigSerfd, buf, strlen(buf), 0);
		if (0 >= dwRet)
		{
			perror("send");
			exit(EXIT_FAILURE);
		}
		printf("send:%s", buf);
		dwRet = recv(SigSerfd, buf, 4096, 0);
		if (0 == dwRet)
		{
			perror("recv");
			exit(EXIT_FAILURE);
		}
		buf[dwRet] = '\0';
		printf("%s", buf);
		sscanf(buf, "331");
		if (331 != 331 && 1)
		{
			exit(EXIT_FAILURE);
		}

		//发送PASS
		sprintf(buf, "PASS %s\r\n", password);
		dwRet = send(SigSerfd, buf, strlen(buf), 0);
		if (0 >= dwRet)
		{
			perror("send");
			exit(EXIT_FAILURE);
		}
		printf("send:%s", buf);
		dwRet = recv(SigSerfd, buf, 4096, 0);
		if (0 == dwRet)
		{
			perror("recv");
			exit(EXIT_FAILURE);
		}
		buf[dwRet] = '\0';
		printf("%s", buf);

		sscanf(buf, "230");
		if (230 != 230 && 1)
		{
			exit(EXIT_FAILURE);
		}



		//一：客户端有公网ip，可以使用主动模式PORT
		//二： 客户端只有内网IP，没有公网IP 使用PASV
		// 三：客户端有公网IP，但安装了防火墙，使用PASV，打开1024以上的高端口
		// 四：连接用内网标准版cm*natpro*y搭建的FTP服务，必须要用PASV方式
		// 五：

		//将192.168.xxx.xxx替换成192，168，xxx，xxx
		str_replace(LocalIP, FullPoint, Comma, DstIp);

		//发送PORT模式（主动模式）
		//主动模式
		// 
		// 打开监听端口
		if (0 != listen(TransSerfd, 20))
		{
			printf("Trans connect faild:%d", WSAGetLastError());
			return;
		}
		printf("Trans connect OK:\n");
		char* TransSerAddrLen = sizeof(TransSerAddr);
		dwRet = getsockname(TransSerfd , (struct sockaddr*)&TransSerAddr, &TransSerAddrLen);
		//发送PORT指令
		int TmpPort = ntohs(TransSerAddr.sin_port);//TransSendPort;
		printf("tmpport=%d", TmpPort);
		printf("port= %d\n", ntohs(TransSerAddr.sin_port));
		sprintf(buf, "PORT %s,%d,%d\r\n", DstIp, (TmpPort /256), (TmpPort % 256));//第五个数*256+第六个数=端口
		
		dwRet = send(SigSerfd, buf, strlen(buf), 0);
		if (0 >= dwRet)
		{
			perror("send");
			exit(EXIT_FAILURE);
		}
		printf("send:%s", buf);
		//接收tcp连接
		socklen_t len = sizeof(TransClientAddr);
		SOCKET TransClientfd=accept(TransSerfd, (struct sockadd*)&TransClientAddr, &len);
		if (TransClientfd == 0)
		{
			printf("Sigsocket faild:%d", WSAGetLastError());
			return;
		}
		printf("connection from % s, port% d\n",inet_ntop(AF_INET, &TransClientAddr.sin_addr, buf, sizeof(buf)),
			ntohs(TransClientAddr.sin_port));

		//判断是否成功建立文件名传输通道
		dwRet = recv(SigSerfd, buf, 4096, 0);
		if (0 == dwRet)
		{
			perror("recv");
			exit(EXIT_FAILURE);
		}
		buf[dwRet] = '\0';
		printf("%s", buf);
		sscanf(buf, "200");
		if (200 != 200 && 1)
		{
			exit(EXIT_FAILURE);
		}

		if (strcmp(buf, PortCommandSuc))
		{
			printf("POST TRANS OK");
		}
		//被动模式
		else
		{
			//发送PASV
			sprintf(buf, "PASV\r\n");
			dwRet = send(SigSerfd, buf, strlen(buf), 0);
			if (0 >= dwRet)
			{
				perror("send");
				exit(EXIT_FAILURE);
			}
			printf("send:%s", buf);
			dwRet = recv(SigSerfd, buf, 4096, 0);
			if (0 == dwRet)
			{
				perror("recv");
				exit(EXIT_FAILURE);
			}
			buf[dwRet] = '\0';
			printf("%s", buf);

			sscanf(buf, "227");
			if (230 != 230 && 1)
			{
				exit(EXIT_FAILURE);
			}
			//连接服务器
			if (0 != connect(TransSerfd, (struct sockaddr*)&TransSerAddr, sizeof(TransSerAddr)))
			{
				printf("Trans connect faild:%d", WSAGetLastError());
				return;
			}
			printf("Trans connect OK:\n");

		}

		//NLST命令 查看目录
		sprintf(buf, "NLST\r\n" );
		dwRet = send(SigSerfd, buf, strlen(buf), 0);
		if (0 >= dwRet)
		{
			perror("send");
			exit(EXIT_FAILURE);
		}
		printf("send:%s", buf);
		//接收信令
		dwRet = recv(SigSerfd, buf, 4096, 0);
		if (0 == dwRet)
		{
			perror("recv");
			exit(EXIT_FAILURE);
		}
		buf[dwRet] = '\0';
		printf("%s", buf);
		sscanf(buf, "125");
		if (125 != 125 && 1)
		{
			exit(EXIT_FAILURE);
		}
		//接收目录
		dwRet = recv(TransClientfd, transbuf, 4096, 0);
		if (0 >= dwRet)
		{
			perror("recv");
			printf("error %d ",WSAGetLastError());
			exit(EXIT_FAILURE);	
		}

		transbuf[dwRet] = '\0';
		printf("%s\n", transbuf);
		sscanf(transbuf, "220");
		if (230 != 230 && 1)
		{
			exit(EXIT_FAILURE);
		}

		//获取文件
		// 创建接收文件的socket
		if (0 != listen(TransFileSerfd, 20))
		{
			printf("TransFile connect faild:%d", WSAGetLastError());
			return;
		}
		printf("TransFile connect OK:\n");
		TmpPort = ntohs(TransFileSerAddr.sin_port);//TransSendPort;
		sprintf(buf, "PORT %s,%d,%d\r\n", DstIp, (TmpPort / 256), (TmpPort % 256));//第五个数*256+第六个数=端口
		printf("port= %d\n", ntohs(TransFileSerAddr.sin_port));
		dwRet = send(SigSerfd, buf, strlen(buf), 0);
		if (0 >= dwRet)
		{
			perror("send");
			exit(EXIT_FAILURE);
		}
		printf("send:%s", buf);
		dwRet = recv(SigSerfd, buf, 4096, 0);
		if (0 == dwRet)
		{
			perror("recv");
			exit(EXIT_FAILURE);
		}
		buf[dwRet] = '\0';
		printf("%s", buf);
		sscanf(buf, "220");
		if (230 != 230 && 1)
		{
			exit(EXIT_FAILURE);
		}

		len = sizeof(TransFileClientAddr);
		//接收文件的socket
		SOCKET TransFileClientfd = accept(TransFileSerfd, (struct sockadd*)&TransFileClientAddr, &len);
		if (TransFileClientfd == 0)
		{
			printf("Sigsocket faild:%d", WSAGetLastError());
			return;
		}
		printf("connection from % s, port% d\n", inet_ntop(AF_INET, &TransFileClientAddr.sin_addr, buf, sizeof(buf)),
			ntohs(TransFileClientAddr.sin_port));
		if (strcmp(buf, PortCommandSuc))
		{
			printf("POST TRANS OK\n");
		}

		//打开写入的文件
		{
			tempstorage = fopen(STORAGE, "wb");
			if (!tempstorage) {
				fprintf(stderr, "Can't open temp storage file %s\n", STORAGE);
				goto Win_shutdown;
			}
			printf("OPEN %s success\n", STORAGE);
			sprintf(buf, "RETR %s\r\n", sftppath);
			dwRet = send(SigSerfd, buf, strlen(buf), 0);
			if (0 >= dwRet)
			{
				perror("send");
				exit(EXIT_FAILURE);
			}
			printf("send:%s\n", buf);
			sscanf(buf, "125");
			if (125 != 125 && 1)
			{
				exit(EXIT_FAILURE);
			}
			dwRet = recv(SigSerfd, buf, 4096, 0);
			if (0 == dwRet)
			{
				perror("recv");
				exit(EXIT_FAILURE);
			}
			buf[dwRet] = '\0';
			printf("%s", buf);
			sscanf(buf, "125");
			if (230 != 230 && 1)
			{
				exit(EXIT_FAILURE);
			}
		}
  		


		g_recvBuf = malloc(FILE_BUF_SIZE);

		u32 RcvfileLen=0;
		u8 count = 0;
		do {
			printf("start recv file:\n");
			do
			{
				
				//dwRet = recv(TransFileClientfd, g_recvBuf, sizeof(g_recvBuf), 0);
				dwRet = recv(TransFileClientfd, transfilebuf, 2048, 0);
				if (dwRet < 0)
				{
					printf("recv err :%d", WSAGetLastError());
					break;
				}
				/* write to stderr */
				write(2, transfilebuf, dwRet);
				/* write to temporary storage area */
				fwrite(transfilebuf, dwRet, 1, tempstorage);
				count += dwRet;
				RcvfileLen += dwRet;
			
				if (dwRet < sizeof(transfilebuf))
				{
					printf("\nsave in file err");
					return LIBFTP_System;
				}
			} while (dwRet > 0);
			printf("\ncount=%d" ,count);
			printf("\n recv=%d", dwRet);
			if (dwRet == LIBSSH2_ERROR_EAGAIN) {
				/* error or end of file */
				break;
			}

			timeout.tv_sec = 10;
			timeout.tv_usec = 0;

			FD_ZERO(&fd);
			FD_ZERO(&fd2);
			FD_SET(TransFileSerfd, &fd);
			FD_SET(TransFileSerfd, &fd2);

			/* wait for readable or writeable */
			dwRet = select(TransFileSerfd + 1, &fd, &fd2, NULL, &timeout);
			if (dwRet <= 0) {
				/* negative is error
				   0 is timeout */
				fprintf(stderr, "SFTP download timed out: %d\n", dwRet);
				break;
			}


	} while (1);
			fclose(tempstorage);

			tempstorage = fopen(STORAGE, "rb");
			if (!tempstorage) {
				/* weird, we can't read the file we just wrote to... */
				fprintf(stderr, "can't open %s for reading\n", STORAGE);
				goto Win_shutdown;
			}
		


	Win_shutdown:
		closesocket(SigSerfd);
		closesocket(TransSerfd);

	}
#ifdef WIN32
		closesocket(SigSerfd);
		closesocket(TransSerfd);
#else
		close(serfd);
#endif
		fprintf(stderr, "all done\n");

		libssh2_exit();

		return 0;

	
}





/// <summary>
/// 初始化Sock
/// </summary>
BOOL InitFtpSocket()
{
	u32 dwRet = 0;
#ifdef FTP_WIN32
	WSADATA wsadata;

	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))        // 启动协议,成功返回0
	{
		printf("WSAStartup faild: %d\n", WSAGetLastError());
		return LIBFTP_OK;
	}
	printf("FtpInitWinSocket OK\n");

#endif // WIN32

}


/// <summary>
/// 关闭Sock
/// </summary>
BOOL CloseFtpSocket()
{
	u32 dwRet = 0;
	dwRet=WSACleanup();
	if (dwRet !=0)
	{
		printf("WSAStartupERR:%d", WSAGetLastError());
		return dwRet;
	}

}



/************************************************************************
函数名：ThreadListEpollThreadCreat
功能：	创建线程
参数：
返回值：成功——0；	失败——其他
************************************************************************/
//ThreadListEpollThreadCreat()
//{
//	u32 dwLoop = 0;
//	TASKHANDLE tTaskFd = NULL;
//
//	//创建接收线程
//	for (dwLoop = 0; dwLoop < g_tFtpLibRunBaseInfo.m_dwRcvThreadNum; dwLoop++)
//	{
//		g_ptFtpLib_RcvThreadList[dwLoop].m_bThreadIsStart = TRUE;	//线程是否开始
//		//创建侦听任务,侦听连接请求
//		tTaskFd = OalTaskCreate((void*)IoSocketListenRcvTaskPrc, "IoSocketListenRcvTaskPrc", PRI_NORMAL, (u32)128 << 10, dwLoop, 0, &g_ptFtpLib_RcvThreadList[dwLoop].m_dwThreadId);
//		if (NULL == tTaskFd)
//		{
//		//	hpcomprt(HPCOM_LOG_ERR, "HpCom RcvThread Creat fail, Loop=%u", dwLoop);		//打印错误
//		}
//	}
//
//	//创建接收线程
//	for (dwLoop = 0; dwLoop < g_tFtpLibRunBaseInfo.m_dwSndThreadNum; dwLoop++)
//	{
//		g_ptFtpLib_SndThreadList[dwLoop].m_bThreadIsStart = TRUE;	//线程是否开始
//		//创建侦听任务,侦听连接请求
//		OalTaskCreate((void*)IoSocketListenSndTaskPrc, "IoSocketListenSndTaskPrc", PRI_NORMAL, (u32)128 << 10, dwLoop, 0, &g_ptFtpLib_SndThreadList[dwLoop].m_dwThreadId);
//		if (NULL == tTaskFd)
//		{
//		//	hpcomprt(HPCOM_LOG_ERR, "HpCom SndThread Creat fail, Loop=%u", dwLoop);		//打印错误
//		}
//	}
//
//	return FTPLIB_OK;
//
//}

