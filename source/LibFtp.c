#include "LibFtp.h"



TCommInitParam		g_tCommInitParam = { 0 };//��������
TLibFtpInitPara		g_tFtpLibInitPara = { 0 };//��ʼ���������ݽṹ
TLibFtpBaseInfo		g_tFtpLibRunBaseInfo = { 0 };	//����������Ϣ
TFtpLibTranFileInfo	g_FtpLibRcvFileInfo,g_tFtpLibTranFileInfo = { 0 };			//���գ������ļ���Ϣ


u32 g_dwFtpLibMemTag = 0;							//�ڴ��ǩ
u32 g_dwFtpLibXmlTag = INVALID_U32ID;							//Xml��ǩ

#define STORAGE "D:/tmp/VSCodeUserSetup-x64-1.49.2.exe" /* this is the local file name this example uses to store the downloaded file in */

FILE* tempstorage;				//char* g_fileBuf;          // ���ܴ洢�ļ�����

 char* ip							= "192.168.50.41";
 int port							= 21;
 char* keyfile1					= "~/.ssh/id_rsa.pub";
 char* keyfile2				= "~/.ssh/id_rsa";
 char* username				= "sxd";
 char* password				= "ds";
 char* sftppath				= "VSCodeUserSetup-x64-1.49.2.exe";// ������������͹������ļ���
 char* LinuxFtpProtrol		= "SSH-2.0-OpenSSH_7.4\r\n";
 char* WinFtpProtrol		= "220 Microsoft FTP Service\r\n";
 char* CodingFormat		= "UTF8 ON";
 char* LocalIP					= "192.168.50.199";
 int* SigSendPort			= 0;//������ģʽ����˿� Ĭ��63000    
 char* PortCommandSuc = "200 PORT command successful";
 char* NLSTCommandSuc = "125 Data connection already open; Transfer starting.";
/// <summary>
/// ��ʼ��libftpЭ��ջ
/// </summary>
void LibFtpInit(IN  TCommInitParam *ptCommInitParam, IN TLibFtpInitPara tFtpLibInitPara)
{
	u32 dwRet = 0;

	dwRet = LibFtpSaveInitParam(ptCommInitParam, tFtpLibInitPara);//��ʼ������

	dwRet = InitFtpSocket();//��ʼ��SOCKET
	if (dwRet != 0)
	{
		printf("SOCKET init faild");
		return;
	}
	printf("SOCKET OK\n");

	dwRet = libssh2_init(0);//��ʼ��libssh��


	if (dwRet != 0)
	{
		printf("libssh init faild");
		return;
	}
	printf("libssh2_init OK\n");
	
	//��ʼ��telnet
	//��ʼ�������б�
	//��ʼ���ͻ����б�
	//��ʼ���ͻ����б����
	//�̳߳�ʼ��
	//��������socket
	//����epoll
	//�����߳�
	//��ʼ��SOCKET

}

/// <summary>
/// �����ʼ������
/// </summary>
u32 LibFtpSaveInitParam(IN  TCommInitParam *ptCommInit, IN TLibFtpInitPara tInitPara)
{
	if (NULL == tInitPara.m_pHpComEventPrc ||
		(0 == tInitPara.m_dwSvrNum && 0 == tInitPara.m_dwCltNum && 0 == tInitPara.m_dwSingleRRCltNum) ||
		NULL == ptCommInit)
	{
		return LIBFTP_ParamErr;
	}
	
	g_tFtpLibRunBaseInfo.m_dwSvrNum = tInitPara.m_dwSvrNum;		//���������
	g_tFtpLibRunBaseInfo.m_dwCltNum = tInitPara.m_dwCltNum;		//�ͻ��������
	g_tFtpLibRunBaseInfo.m_dwSingleRRCltNum = tInitPara.m_dwSingleRRCltNum;	//��������ͻ��������

	g_tFtpLibRunBaseInfo.m_dwRcvThreadNum = tInitPara.m_dwRcvThreadNum;		//�����߳���
	if (0 >= g_tFtpLibRunBaseInfo.m_dwRcvThreadNum)
	{
		g_tFtpLibRunBaseInfo.m_dwRcvThreadNum = 10;		//����Ĭ��ֵ
	}
	g_tFtpLibRunBaseInfo.m_dwSndThreadNum = tInitPara.m_dwSndThreadNum;		//�����߳���
	if (0 >= g_tFtpLibRunBaseInfo.m_dwSndThreadNum)
	{
		g_tFtpLibRunBaseInfo.m_dwSndThreadNum = 4;		//����Ĭ��ֵ
	}
	g_tFtpLibRunBaseInfo.m_dwSRRCheckTime = tInitPara.m_dwSRRCheckTimerSec;		//SRR���ʱ��
	if (0 >= g_tFtpLibRunBaseInfo.m_dwSRRCheckTime)
	{
		g_tFtpLibRunBaseInfo.m_dwSRRCheckTime = 30;		//SRR���ʱ��
	}

#ifdef HPCOM_WIN32
	g_tFtpLibRunBaseInfo.m_dwRcvThreadNum = 1;		//WindowsĬ�Ͻ����߳���Ϊ1
	g_tFtpLibRunBaseInfo.m_dwSndThreadNum = 1;		//WindowsĬ�Ϸ����߳���Ϊ1
#endif

	g_RouseThreadSock.m_wRcvThreadPort = tInitPara.m_wRcvRousePort;		//�����̻߳��Ѷ˿�
	if (0 == g_RouseThreadSock.m_wRcvThreadPort)
	{
		return LIBFTP_ParamErr;
		//g_RouseThreadSock.m_wRcvThreadPort = 9000;
	}
	g_RouseThreadSock.m_wSndThreadPort = tInitPara.m_wSndRousePort;		//�����̻߳��Ѷ˿�
	if (0 == g_RouseThreadSock.m_wSndThreadPort)
	{
		return LIBFTP_ParamErr;
		//g_RouseThreadSock.m_wSndThreadPort = 9001;
	}

	g_RouseThreadSock.m_dwMaxMsgLen = tInitPara.m_dwMaxLocalMsgLen;		//������Ϣ��󳤶�
	if (0 == g_RouseThreadSock.m_dwMaxMsgLen)
	{
		g_RouseThreadSock.m_dwMaxMsgLen = 1024;
	}

	g_tFtpLibRunBaseInfo.m_dwAllChnlMaxNum = tInitPara.m_dwAllChnlMaxNum;	//����ͨ�������
	if (LIBFTP_EPOLLEVENT_NUM >= g_tFtpLibRunBaseInfo.m_dwAllChnlMaxNum)
	{
		g_tFtpLibRunBaseInfo.m_dwAllChnlMaxNum = LIBFTP_CONNECTFD_SIZE;		//����Ĭ��ֵ
	}
	g_tFtpLibRunBaseInfo.m_pFtpLibEventPrc = tInitPara.m_pHpComEventPrc;		//�ص��¼�
	g_tFtpLibRunBaseInfo.m_dwExistSvrCnt = 0;	//���÷�����
	g_tFtpLibRunBaseInfo.m_dwExistCltCnt = 0;	//���ÿͻ�����
	g_tFtpLibRunBaseInfo.m_dwRcvEpollFd = LIBFTP_INVALID_SOCKET;		//����server�е�socket
	g_tFtpLibRunBaseInfo.m_dwSndEpollFd = LIBFTP_INVALID_SOCKET;		//����server�е�socket
	g_tCommInitParam = *ptCommInit;		//��������

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
	u8* g_recvBuf = ""; // ������Ϣ������
	struct sockaddr_in	SigSerAddr, //FTP������  ����ͨ��  �Զ˵�ַ�˿�
									TransSerAddr, //FTP������  ����ͨ��  WIN ����ģʽ�£��Զ˵�ַ�˿�     ����ģʽ�£����˵�ַ�˿�
									LinuxTransSerAddr,						//FTP������                  LINUX �ļ����� �Զ˵�ַ�˿�
									TransFileSerAddr,////FTP������  �ļ�ͨ��  WIN ����ģʽ�£��Զ˵�ַ�˿�     ����ģʽ�£����˵�ַ�˿�
									SigClientAddr, //FTP�ͻ���  ����ͨ��  ���˵�ַ�˿�
									TransClientAddr, //FTP�ͻ���  ����ͨ��  WIN ����ģʽ�£��Զ˵�ַ�˿�     ����ģʽ�£����˵�ַ�˿�
									LinuxTransClientAddr,									//FTP�ͻ���                  LINUX �ļ����� ���˵�ַ�˿�
									TransFileClientAddr;//�ļ�ͨ��  WIN ����ģʽ�£��Զ˵�ַ�˿�     ����ģʽ�£����˵�ַ�˿�

	char* ipAddress[INET_ADDRSTRLEN];//������ʮ���Ƶ�ip��ַ
	struct timeval timeout;
	char Comma = ',';//����
	char FullPoint = '.';//���
	char DstIp[1024];//192��168��xxx��xxx��ʽ��ip

	fd_set fd;
	fd_set fd2;


#ifdef WIN32
	//��ʼ��sock
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))        // ����Э��,�ɹ�����0
	{
		printf("WSAStartup faild: %d\n", WSAGetLastError());
		return;
	}
	printf("FtpInitWinSocket OK\n");
#endif // WIN32

	//��ʼ��libssh��
	dwRet = libssh2_init(0);
	if (dwRet != 0)
	{
		printf("libssh init faild");
		return;
	}
	printf("libssh2_init OK\n");

	//����������·server socket�׽��� ��ַ���˿ں�,AF_INET��IPV4
	SOCKET SigSerfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//����������·server socket�׽��� ��ַ���˿ں�,AF_INET��IPV4
	SOCKET TransSerfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//�����ļ�������·server socket�׽��� ��ַ���˿ں�,AF_INET��IPV4
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
	printf("All socket OK:SigSerfd=%lld��TransSerfd=%lld��TransFileSerfd=%lld\n", SigSerfd, TransSerfd,TransFileSerfd);


	// ��SigSer socket�󶨶Զ�IP��ַ�Ͷ˿ں�
	SigSerAddr.sin_family = AF_INET;
	SigSerAddr.sin_port = htons(port);                       // htons�ѱ����ֽ���תΪ�����ֽ���
	SigSerAddr.sin_addr.S_un.S_addr = inet_addr(ip); // ��������IP��ַ
	// ��TransSer socket�󶨶Զ�IP��ַ�Ͷ˿ں�
	LinuxTransSerAddr.sin_family = AF_INET;
	LinuxTransSerAddr.sin_port = htons(port);                       // htons�ѱ����ֽ���תΪ�����ֽ���
	LinuxTransSerAddr.sin_addr.S_un.S_addr = inet_addr(ip); // ��������IP��ַ
	//�󶨿ͻ��ˣ����ˣ�����ͨ����ip�˿�
	SigClientAddr.sin_family = AF_INET;
	if(SigSendPort!=0)//����Ϊ���
	{
	SigClientAddr.sin_port = htons(SigSendPort);
	}
	SigClientAddr.sin_addr.S_un.S_addr = inet_addr(LocalIP);//����IP
	bind(SigSerfd, (struct sockaddr*)&SigClientAddr, sizeof(SigClientAddr));

	// ���ӵ�������
	if (0 != connect(SigSerfd, (struct sockaddr*)&SigSerAddr, sizeof(SigSerAddr)))
	{
		printf("connect faild:%d", WSAGetLastError());
		return;
	}
	printf("connect OK:\n");

	//int* clientAddrLen = sizeof(SigClientAddr);//��ʱָ�룬��getsockname�ĳ���ʹ��
	int* SigSerAddrLen= sizeof(SigSerAddr);
	dwRet = getsockname(SigSerfd, (struct sockaddr*)&SigSerAddr, &SigSerAddrLen);//��ȡtcp�ͻ��˶˿�
	printf("port=%d\n", ntohs(SigSerAddr.sin_port));
	
	//������ģʽָ��˿�
	TransSerAddr.sin_family = AF_INET;
	int tmpTransSendPort = ntohs(SigSerAddr.sin_port);//�˿�ת��Ϊ�����ֽ���
	tmpTransSendPort++;
	TransSerAddr.sin_port = htons(tmpTransSendPort);//���ض˿�+1
	TransSerAddr.sin_addr.S_un.S_addr = inet_addr(LocalIP);//����IP
	bind(TransSerfd, (struct sockaddr*)&TransSerAddr, sizeof(TransSerAddr));

	//������ģʽ�ļ�����˿�
	TransFileSerAddr.sin_family = AF_INET;
	tmpTransSendPort++;
	TransFileSerAddr.sin_port = htons(tmpTransSendPort);//���ض˿�+2
	TransFileSerAddr.sin_addr.S_un.S_addr = inet_addr(LocalIP);//����IP
	bind(TransFileSerfd, (struct sockaddr*)&TransFileSerAddr, sizeof(TransFileSerAddr));


	char* buf;
	buf = malloc(4096);
	char* transbuf;
	transbuf= malloc(4096);
	char* transfilebuf;
	transfilebuf = malloc(FILE_BUF_SIZE);

	//���մ���İ汾�ţ�WIN��LIUNX
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

//���Ϊwin����linux��ftp������
	if (strcmp(buf, WinFtpProtrol))
	{

		//	Linux��ftp������
		
		// ���ӵ�������
		if (0 != connect(TransSerfd, (struct sockaddr*)&LinuxTransSerAddr, sizeof(LinuxTransSerAddr)))
		{
			printf("connect faild:%d", WSAGetLastError());
			return;
		}
		printf("connect OK:\n");//���ӳɹ�
		char* LinuxTransClientAddrLen = sizeof(LinuxTransClientAddr);
		dwRet = getsockname(TransSerfd, (struct sockaddr*)&LinuxTransClientAddr, &LinuxTransClientAddrLen);//��ȡtcp�ͻ��˶˿�
		if (dwRet != LIBFTP_OK)
		{
			printf("get sock ip:port faild");
			return LIBFTP_System;
		}
		printf("TransClient:client ddress = %s:%d\n", inet_ntop(AF_INET, &TransClientAddr.sin_addr, ipAddress, sizeof(ipAddress)), ntohs(TransClientAddr.sin_port));




		LIBSSH2_SESSION* session; //ssh�Ự
		LIBSSH2_SFTP* sftp_session;//sftp�Ự
		LIBSSH2_SFTP_HANDLE* sftp_handle;//sftp���


		session = libssh2_session_init();//ssh�Ự��ʼ��
		if (!session)
			return -1;

		/* Since we have set non-blocking, tell libssh2 we are blocking */
		libssh2_session_set_blocking(session, 1);//����ssh�Ự����

		/* ... start it up. This will �汾Э�̣�trade welcome banners��,��Կ������ exchange keys��,
		 * and �����㷨Э�̣�setup crypto��, ѹ���㷨Э��compression, and MAC layers
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
		fingerprint = libssh2_hostkey_hash(session, LIBSSH2_HOSTKEY_HASH_SHA1);//�����Կ
		fprintf(stderr, "Fingerprint: ");
		for (i = 0; i < 20; i++) {
			fprintf(stderr, "%02X ", (unsigned char)fingerprint[i]);
		}
		fprintf(stderr, "\n");


		for (i = 0; i < 20; i++) {
			printf(stderr, "%02X ", (unsigned char)fingerprint[i]);
		}
		printf(stderr, "\n");
		/* check what authentication methods are available �����õ������֤����*/
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
			/* We could authenticate via password ͨ���û������������֤ */
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
		//��д����ļ�
		tempstorage = fopen(STORAGE, "wb");
		if (!tempstorage) {
			fprintf(stderr, "Can't open temp storage file %s\n", STORAGE);
			goto shutdown;
		}
		/* Request a file via SFTP ͨ��·�������ļ� */
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

		//ָ�������ʽ
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


		//�����û���
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

		//����PASS
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



		//һ���ͻ����й���ip������ʹ������ģʽPORT
		//���� �ͻ���ֻ������IP��û�й���IP ʹ��PASV
		// �����ͻ����й���IP������װ�˷���ǽ��ʹ��PASV����1024���ϵĸ߶˿�
		// �ģ�������������׼��cm*natpro*y���FTP���񣬱���Ҫ��PASV��ʽ
		// �壺

		//��192.168.xxx.xxx�滻��192��168��xxx��xxx
		str_replace(LocalIP, FullPoint, Comma, DstIp);

		//����PORTģʽ������ģʽ��
		//����ģʽ
		// 
		// �򿪼����˿�
		if (0 != listen(TransSerfd, 20))
		{
			printf("Trans connect faild:%d", WSAGetLastError());
			return;
		}
		printf("Trans connect OK:\n");
		char* TransSerAddrLen = sizeof(TransSerAddr);
		dwRet = getsockname(TransSerfd , (struct sockaddr*)&TransSerAddr, &TransSerAddrLen);
		//����PORTָ��
		int TmpPort = ntohs(TransSerAddr.sin_port);//TransSendPort;
		printf("tmpport=%d", TmpPort);
		printf("port= %d\n", ntohs(TransSerAddr.sin_port));
		sprintf(buf, "PORT %s,%d,%d\r\n", DstIp, (TmpPort /256), (TmpPort % 256));//�������*256+��������=�˿�
		
		dwRet = send(SigSerfd, buf, strlen(buf), 0);
		if (0 >= dwRet)
		{
			perror("send");
			exit(EXIT_FAILURE);
		}
		printf("send:%s", buf);
		//����tcp����
		socklen_t len = sizeof(TransClientAddr);
		SOCKET TransClientfd=accept(TransSerfd, (struct sockadd*)&TransClientAddr, &len);
		if (TransClientfd == 0)
		{
			printf("Sigsocket faild:%d", WSAGetLastError());
			return;
		}
		printf("connection from % s, port% d\n",inet_ntop(AF_INET, &TransClientAddr.sin_addr, buf, sizeof(buf)),
			ntohs(TransClientAddr.sin_port));

		//�ж��Ƿ�ɹ������ļ�������ͨ��
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
		//����ģʽ
		else
		{
			//����PASV
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
			//���ӷ�����
			if (0 != connect(TransSerfd, (struct sockaddr*)&TransSerAddr, sizeof(TransSerAddr)))
			{
				printf("Trans connect faild:%d", WSAGetLastError());
				return;
			}
			printf("Trans connect OK:\n");

		}

		//NLST���� �鿴Ŀ¼
		sprintf(buf, "NLST\r\n" );
		dwRet = send(SigSerfd, buf, strlen(buf), 0);
		if (0 >= dwRet)
		{
			perror("send");
			exit(EXIT_FAILURE);
		}
		printf("send:%s", buf);
		//��������
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
		//����Ŀ¼
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

		//��ȡ�ļ�
		// ���������ļ���socket
		if (0 != listen(TransFileSerfd, 20))
		{
			printf("TransFile connect faild:%d", WSAGetLastError());
			return;
		}
		printf("TransFile connect OK:\n");
		TmpPort = ntohs(TransFileSerAddr.sin_port);//TransSendPort;
		sprintf(buf, "PORT %s,%d,%d\r\n", DstIp, (TmpPort / 256), (TmpPort % 256));//�������*256+��������=�˿�
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
		//�����ļ���socket
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

		//��д����ļ�
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
/// ��ʼ��Sock
/// </summary>
BOOL InitFtpSocket()
{
	u32 dwRet = 0;
#ifdef FTP_WIN32
	WSADATA wsadata;

	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))        // ����Э��,�ɹ�����0
	{
		printf("WSAStartup faild: %d\n", WSAGetLastError());
		return LIBFTP_OK;
	}
	printf("FtpInitWinSocket OK\n");

#endif // WIN32

}


/// <summary>
/// �ر�Sock
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
��������ThreadListEpollThreadCreat
���ܣ�	�����߳�
������
����ֵ���ɹ�����0��	ʧ�ܡ�������
************************************************************************/
//ThreadListEpollThreadCreat()
//{
//	u32 dwLoop = 0;
//	TASKHANDLE tTaskFd = NULL;
//
//	//���������߳�
//	for (dwLoop = 0; dwLoop < g_tFtpLibRunBaseInfo.m_dwRcvThreadNum; dwLoop++)
//	{
//		g_ptFtpLib_RcvThreadList[dwLoop].m_bThreadIsStart = TRUE;	//�߳��Ƿ�ʼ
//		//������������,������������
//		tTaskFd = OalTaskCreate((void*)IoSocketListenRcvTaskPrc, "IoSocketListenRcvTaskPrc", PRI_NORMAL, (u32)128 << 10, dwLoop, 0, &g_ptFtpLib_RcvThreadList[dwLoop].m_dwThreadId);
//		if (NULL == tTaskFd)
//		{
//		//	hpcomprt(HPCOM_LOG_ERR, "HpCom RcvThread Creat fail, Loop=%u", dwLoop);		//��ӡ����
//		}
//	}
//
//	//���������߳�
//	for (dwLoop = 0; dwLoop < g_tFtpLibRunBaseInfo.m_dwSndThreadNum; dwLoop++)
//	{
//		g_ptFtpLib_SndThreadList[dwLoop].m_bThreadIsStart = TRUE;	//�߳��Ƿ�ʼ
//		//������������,������������
//		OalTaskCreate((void*)IoSocketListenSndTaskPrc, "IoSocketListenSndTaskPrc", PRI_NORMAL, (u32)128 << 10, dwLoop, 0, &g_ptFtpLib_SndThreadList[dwLoop].m_dwThreadId);
//		if (NULL == tTaskFd)
//		{
//		//	hpcomprt(HPCOM_LOG_ERR, "HpCom SndThread Creat fail, Loop=%u", dwLoop);		//��ӡ����
//		}
//	}
//
//	return FTPLIB_OK;
//
//}

