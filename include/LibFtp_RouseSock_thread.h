#ifndef _H_ROUSE_SOCKTHREAD_WIN_
#define _H_ROUSE_SOCKTHREAD_WIN_
#include "LibFtpstdafx.h"

//����socket
typedef struct tLibFtpRouseSocket
{
	u32 m_dwSndThreadSock;		//���ѷ����߳�sock
	u32 m_dwRcvThreadSock;		//���ѽ����߳�sock

	u32 m_dwThreadIp;			//Ip
	u16 m_wSndThreadPort;		//�����̶߳˿�
	u16 m_wRcvThreadPort;		//�����̶߳˿�

	u32 m_dwMaxMsgLen;			//������Ϣ��󳤶ȣ���λ�ֽڣ�Ĭ��1k
	u32 m_dwLocalMsgSndNum;		//������Ϣ������		
	u32 m_dwLocalMsgSndSucNum;	//������Ϣ���ͳɹ���		
	u32 m_dwLocalEvtCbNum;		//�ϱ��¼���	

}TLibFtpRouseSocket;

//��Ϣ����
typedef enum eLibFtpReuseMsgType
{
	E_LIBFTP_ROUSE_THREAD_RCV = 0x10,		//���ѽ����߳�
	E_LIBFTP_ROUSE_USER_DATA,				//���ѽ����̡߳��������û�����

	E_LIBFTP_ROUSE_THREAD_SND = 0x20,		//���ѷ����߳�

}ELibFtpReuseMsgType;

//��Ϣ����
typedef struct tLibFtpLocalUserMsgData
{
	u32 m_dwUserMsgType;	//�û���Ϣ����
	char* m_pData;			//��Ϣָ��
	u32 m_dwDataLen;		//��Ϣ����
}TLibFtpLocalUserMsgData;

#pragma pack(push) //�������״̬
#pragma pack(1)

//��Ϣͷ����Ϊ������Ϣ����ֻ��ͷ
typedef struct tLibFtpRouseMsgHeader
{
	u8 m_chFirstFlag;			//��һλ��ʶ��HPCOM_DATAHEADER_FIRST
	u8 m_chSecondFlag;			//�ڶ�λ��ʶ��HPCOM_DATAHEADER_SEC
	u8 m_chVersion;				//�汾�ţ�HPCOM_VER

	u32 m_dwMsgType;			//��Ϣ����
	u32 m_dwUserMsgType;		//�û���Ϣ����,��msgtypeΪE_HPCOM_ROUSE_USER_DATAʱ��
	u32 m_dwDataLen;			//��Ϣ����,��Ϊ�û�����ʱ��Ч
}TLibFtpRouseMsgHeader;

#pragma pack(pop)

TLibFtpRouseSocket g_RouseThreadSock;		//�����߳�socket

/************************************************************************
��������RouseThreadSockCreat
���ܣ�	���������߳�socket
������

����ֵ���ɹ�����0��ʧ�ܡ�������
************************************************************************/
u32 RouseThreadSockCreat();

/************************************************************************
��������RouseThreadSockDestroy
���ܣ�	���ٻ����߳�socket
������

����ֵ���ɹ�����0��ʧ�ܡ�������
************************************************************************/
u32 RouseThreadSockDestroy();

/************************************************************************
��������RouseThreadSndRouseMsg
���ܣ�	������Ϣ
������

����ֵ���ɹ�����0��ʧ�ܡ�������
************************************************************************/
u32 RouseThreadSndMsg(IN ELibFtpReuseMsgType eMsg, IN u32 dwType, IN u8* pData, IN u32 dwDataLen);

/************************************************************************
��������RouseThreadRecvMsg
���ܣ�	������Ϣ
������

����ֵ���ɹ�����0��ʧ�ܡ�������
************************************************************************/
u32 RouseThreadRecvMsg(IN ELibFtpReuseMsgType eMsg);

#endif