#ifndef _H_LIBFTP_
#define _H_LIBFTP_
#pragma once
#include"LibFtpstdafx.h"

#define LIBFTP_FILENAME_LEN			32		//�ļ�������
#define LIBFTP_FILEDIR_LEN			128		//�ļ�Ŀ¼����
#define LIBFTP_SVRNAME_LEN			32
#define LIBFTP_SVRDES_LEN			128


#define LIBFTP_INVALID_SOCKET 0xffffffff//127.0.0.1
#define LIBFTP_SYSTEM_FAIL			-1

#define LIBFTP_EPOLLEVENT_NUM 64//����ͨ�������
#define LIBFTP_CONNECTFD_SIZE 1024

#define PACKET_SIZE (1024 - sizeof(int) * 3)


#define INET_ADDRLEN 20

#define IP_MAX_LEN 255

#define FILE_BUF_SIZE 102400

#define LIBFTP_READFILE_LEN			10 << 10		//ÿ�ζ��ļ�����
//
// �¼��ص�
typedef u32(*LibFtpEventCB)(IN u32 eEvtType, IN void* pEvtData);

//FtpLib�¼�����
typedef enum eLibFtpEvntType
{
	E_LIBFTP_CONNECT_EVENT = 0,		//�����¼�
	E_LIBFTP_DISCONNECT_EVENT,		//�����¼�����������Լ��ͷ�ͨ��
	E_LIBFTP_RCVDATA_EVENT,			//���������¼�
	E_LIBFTP_SRRRCVDATA_EVENT,		//��������ͨ�����������¼�(�ص��ӿڷ���ֵΪ���غ�Ҫ��������Ϣ,���㻻��)
	E_LIBFTP_UDPRCVDATA_EVENT,		//UDP���������¼�
	E_LIBFTP_RCVFILE_EVENT,			//�����ļ��¼�
	E_LIBFTP_SNDFILE_EVENT,			//�����ļ��¼�

	E_LIBFTP_LOCAL_EVENT,			//������Ϣ�¼�

}EFtpLibEvntType;

////�ļ��¼�����
//typedef enum eFtpLibFileEvtType
//{
//	E_FTPLIB_FILE_RCV_START = 0,		//�ļ����տ�ʼ,����ֵΪ���ļ��Ľ��ս��Ⱦ���:1,10,1000;����0ΪĬ�Ͼ���
//	E_FtpLib_FILE_RCV_PRO,			//�ļ����ս���
//	E_FtpLib_FILE_RCV_END,			//�ļ����ս���,����ֵΪ1����ڻص���ɾ�����ļ�,Ϊ0���� 
//	E_FtpLib_FILE_RCV_FAIL,			//�ļ�����ʧ��
//
//	E_FtpLib_FILE_SND_PRO,			//�ļ����ͽ���
//	E_FtpLib_FILE_SND_END,			//�ļ����ͽ���
//	E_FtpLib_FILE_SND_FAIL,			//�ļ�����ʧ��
//}EFtpLibFileEvtType;
//
////����/�����¼����ݽṹ
//typedef struct tFtpLibConctEvtData
//{
//	u32 m_dwPeerIP;			//�Զ�IP
//	u16 m_wPeerPort;		//�Զ˶˿�
//
//	u64 m_qwChnlId;			//ͨ��Id��ȫ��Ψһ��ID
//}TFtpLibConctEvtData;
//
////���������¼����ݽṹ
//typedef struct tFtpLibRcvEvtData
//{
//	u64 m_qwChnlId;			//ͨ��Id
//
//	u8* m_ptDataBuf;		//����buf
//	u32 m_dwDataSize;		//����buf��С
//}TFtpLibRcvEvtData;
//
////���������¼����ݽṹ
//typedef struct tFtpLibUdpRcvEvtData
//{
//	BOOL m_bIsClient;		//�Ƿ�Ϊ�ͻ���
//	u64 m_qwChnlId;			//ͨ��Id����m_bIsClientΪTRUEʱ��Ч
//	u32 m_dwSvrId;			//����Id����m_bIsClientΪFALSEʱ��Ч
//
//	u32 m_dwPeerIp;			//�Զ�Ip
//	u16 m_wPeerPort;		//�Զ˶˿ں�
//	u8* m_ptDataBuf;		//����buf
//	u32 m_dwDataSize;		//����buf��С
//}TFtpLibUdpRcvEvtData;
//
////�ļ��¼����ݽṹ
//typedef struct tFtpLibFileEvtData
//{
//	u64 m_qwChnlId;					//ͨ��Id
//	u32 m_FileEvt;					//�ļ��¼�
//	char m_achFileName[FTPLIB_FILENAME_LEN];		//�ļ�����
//
//	u64 m_qwFileLen;				//�ļ�����
//	u32 m_dwFilePro;				//�ļ�����
//
//}TFtpLibFileEvtData;
//
////������Ϣ�¼����ݽṹ
//typedef struct tFtpLibLocalEvtData
//{
//	u32 m_dwType;		//��Ϣ���ͣ������û�������Ϣʱ���õ���Ϣ����
//	char* m_pData;		//��Ϣָ��,����ΪNULL����m_dwDataLenΪ0ʱ
//	u32 m_dwDataLen;	//��Ϣ����
//
//}TFtpLibLocalEvtData;

//
////����˲���
//typedef struct tFtpLibSvrPara
//{
//	u32 m_dwCapSize;				//������������
//	u32 m_dwBindIp;					//�����Ip������"0.0.0.0"��������ip���ӣ�"127.0.0.1"ֻ����������
//	u16 m_wBindPort;				//�����tcp�󶨶˿ں�
//	u8  m_achSvrName[FTPLIB_SVRNAME_LEN];	//��������,�32���ֽ�
//
//	u32 m_dwSvrMaxDataLen;			//������ݰ�����,��Ϊ0��Ĭ��5k
//	u32 m_dwSvrSndLstNodeNum;		//�������ݻ���Node��,��Ϊ0��Ĭ��Ϊ10
//
//	u32 m_dwSysRcvBufSize;			//ϵͳ�������ݻ����С����Ϊ0��Ĭ��Ϊ10k
//	u32 m_dwSysSndBufSize;			//ϵͳ�������ݻ����С����Ϊ0��Ĭ��Ϊ10k
//
//}TFtpLibSvrPara;
//
////udp����˲���
//typedef struct tFtpLibUdpSvrPara
//{
//	u32 m_dwBindIp;					//�����Ip������"0.0.0.0"��������ip���ӣ�"127.0.0.1"ֻ����������
//	u16 m_wBindPort;				//�����tcp�󶨶˿ں�
//	u8  m_achSvrName[FTPLIB_SVRNAME_LEN];	//��������,�32���ֽ�
//
//	u32 m_dwSvrMaxDataLen;			//������ݰ�����,��Ϊ0��Ĭ��1400
//
//	u32 m_dwSysRcvBufSize;			//ϵͳ�������ݻ����С����Ϊ0��Ĭ��Ϊ10k
//	u32 m_dwSysSndBufSize;			//ϵͳ�������ݻ����С����Ϊ0��Ĭ��Ϊ10k
//
//	BOOL m_bUseDataCheck;			//�Ƿ�ʹ������У��
//
//}TFtpLibUdpSvrPara;
//
////�ͻ��˲���
//typedef struct tFtpLibCltPara
//{
//	u32 m_dwRemoteSvrIp;			//Զ�˷�����Ip
//	u16 m_wRemoteSvrPort;			//Զ�˷������˿�
//	u32 m_dwLocalBindIp;			//���ذ�Ip
//	u16 m_wLocalBindPort;			//���ذ󶨶˿ڣ����鲻ָ��������ֶ˿����õ����⣬��ָ����0���ɣ�
//
//	char* m_pchCltLabel;			//ͨ��Label
//	u32 m_dwLabelLen;				//label����
//
//	u32 m_dwChnlMaxDataLen;			//������ݰ�����,��Ϊ0��Ĭ��10240
//	u32 m_dwChnlSndLstNodeNum;		//�������ݻ���Node��,��Ϊ0��Ĭ��Ϊ10
//
//	u32 m_dwSysRcvBufSize;			//ϵͳ�������ݻ����С����Ϊ0��Ĭ��Ϊ10k
//	u32 m_dwSysSndBufSize;			//ϵͳ�������ݻ����С����Ϊ0��Ĭ��Ϊ10k
//
//}TFtpLibCltPara;
//
////�ͻ��˲���
//typedef struct tFtpLibUdpCltPara
//{
//	u32 m_dwLocalBindIp;			//���ذ�Ip��ʹ�ñ���IP,��127.0.0.1ֻ�ܷ�������
//	u16 m_wLocalBindPort;			//���ذ󶨶˿�,���˿�����Ϊ0��ʹ��ϵͳ����˿�
//
//	u32 m_dwChnlMaxDataLen;			//������ݰ�����,��Ϊ0��Ĭ��1400
//
//	u32 m_dwSysRcvBufSize;			//ϵͳ�������ݻ����С����Ϊ0��Ĭ��Ϊ10k
//	u32 m_dwSysSndBufSize;			//ϵͳ�������ݻ����С����Ϊ0��Ĭ��Ϊ10k
//
//	BOOL m_bUseDataCheck;			//�Ƿ�ʹ������У��
//
//}TFtpLibUdpCltPara;
//

//�ļ��¼�����
typedef enum eLibFtpFileType
{
	E_FTPLIB_FILE_DIR_RCV = 0,		//�����ļ�Ŀ¼
	E_FTPLIB_FILE_DIR_READ,			//��ȡ�ļ�Ŀ¼

}ELibFtpFileType;

//������
typedef enum eFtpLibErrCode
{
	LIBFTP_OK = 0,						   //�����ɹ�
	LIBFTP_System,                          //ϵͳ����
	LIBFTP_InstLimit,                       //�޿���ʵ��
	LIBFTP_InstInvalid,                     //��Чʵ��
	LIBFTP_InvalidConn,                     //��Ч����
	LIBFTP_NotInit,                         //δ��ʼ��
	LIBFTP_AlreadyInit,                     //�Ѿ���ʼ��
	LIBFTP_ParamErr,                        //��������
	LIBFTP_MsgErr,                          //��Ϣ����
	LIBFTP_MsgHeadErr,                      //��Ϣ����
	LIBFTP_ObjNotExist,                     //�������󲻴���
	LIBFTP_ChnErr,                          //�����ͨ����
	LIBFTP_SvrLimit,                        //��������Դ����
	LIBFTP_Timeout,                         //��ʱ
	LIBFTP_ISEXIST,                         //�Ѵ���

}EFtpLibErrCode;

//������
typedef enum eMsgTag
{
	MSG_FILENAME = 1,        // �ļ�����                ������ʹ��
	MSG_FILESIZE = 2,        // �ļ���С                �ͻ���ʹ��
	MSG_READY_READ = 3,        // ׼������                �ͻ���ʹ��
	MSG_SENDFILE = 4,        // ����                    ������ʹ��
	MSG_SUCCESSED = 5,        // �������                ���߶�ʹ��
	MSG_OPENFILE_FAILD = 6         // ���߿ͻ����ļ��Ҳ���    �ͻ���ʹ��
}EMSGTAG;

//������Ϣ
typedef struct eLibFtpBaseInfo
{
	u32 m_dwAllChnlMaxNum;					//����ͨ�������������TCP��UDP����Э��Ҫ�õ���ͨ��
	u32 m_dwSvrNum;							//��������
	u32 m_dwCltNum;							//�ͻ���ͨ������
	u32 m_dwSingleRRCltNum;					//���οͻ���ͨ������
	u32 m_dwRcvThreadNum;					//�����߳�����Ĭ��10
	u32 m_dwSndThreadNum;					//�����߳�����Ĭ��4
	u32 m_dwSRRCheckTime;					//SRR���ն�ʱ����������ڣ�Ĭ��30��

	LibFtpEventCB m_pFtpLibEventPrc;			//�ϱ��¼�����

	u32 m_dwRcvEpollFd;						//����epoll���
	u32 m_dwSndEpollFd;						//����epoll���

	u32 m_dwEpollListenTask;				//epoll�����¼��߳�
	u32 m_dwIsCheckUpSRR;					//�Ƿ���SRR

	u32 m_dwExistSvrCnt;		// ��������˴���
	u32 m_dwExistCltCnt;		// �����ͻ��˴���
	u32 m_dwExistSRRCltCnt;		// ������������ͻ��˴���

	u64 m_qwCreatSockNum;		// ����socket����
	u64 m_qwAccpetSockNum;		// ��������socket����
	u64 m_qwCloseSockNum;		// �ر�socket����

	u64 m_qwStartEpollRcvWait;		//��ʼepollwait�¼�����
	u64 m_qwStartEpollSndWait;		//��ʼepollwait�¼�����
	u64 m_qwEpollRcvWaitEvent;		//epollRcvwait�¼�����
	u64 m_qwEpollSndWaitEvent;			//epollwait�¼�����
	u64 m_qwEpollAccpetEvent;		//EpollAccpet�¼�����
	u64 m_qwEpollRcvDataEvent;		//EpollRcvData�¼�����
	u64 m_qwEpollUdpRcvDataEvent;		//EpollUdpRcvData�¼�����
	u64 m_qwEpollSndDataEvent;		//EpollSndData�¼�����
	u64 m_qwEpollAbnormalEvent;		//Epoll�쳣�¼�����

}TLibFtpBaseInfo;

////ʵ�����
//typedef struct tFtpLibInstMark
//{
//	u32 m_dwHighLevel;					//��һ��	��cltͨ���б�ʾ����������		�������б�ʾ����������	
//	u32 m_dwLowLevel;					//��һ��	��cltͨ���б�ʾcltͨ��������	�������б�ʾ�������ͣ�tcp����udp��
//
//}TFtpLibInstMark;
//
////��Ա��Ϣ
//typedef struct tFtpLibChnl
//{
//	BOOL m_bUsed;				//�Ƿ�ʹ��
//	BOOL m_bIsUdpChnl;			//�Ƿ�ΪUdpͨ��
//	BOOL m_bUseDataCheck;			//�Ƿ�ʹ������У�飬ΪUdpͨ��ʱ��Ч
//	u32 m_dwChnlUseTimes;		//ʹ�ô���
//	u32 m_dwFtpLibId;			//�������б��е�������
//	u64 m_qwChnlId;				//chnlId
//	TFtpLibInstMark m_tChnlMark;	//Chnl���,��һ�����������������һ������ͨ������
//	BOOL m_bIsSRRChnl;			//�Ƿ�Ϊ��������ͨ��
//	u32 m_dwSRRChnlState;		//��������ͨ��״̬
//	BOOL m_bSRRCBING;			//���������Ƿ������ڻص�״̬
//	u32 m_SRRCbSndNum;			//�ص���Ҫ������Ϣ��
//
//	u32 m_dwPackMaxLen;			//���������ݳ���
//	u32 m_dwSndLstNodeNum;		//�������ݻ���Node��
//
//	u32 m_dwOppIP;
//	u16 m_wOppPort;
//	u32 m_dwBindIp;					//Զ�˷�����Ip
//	u16 m_wBindPort;				//���ذ󶨶˿�
//	BOOL m_bConnected;				//�Ƿ����ӳɹ�
//	char* m_pchChnlLabel;			//ͨ��Label
//	u32 m_dwLabelLen;				//Label����
//
//	u32 m_dwRcvDataState;				//��������״̬
//	TFtpLibMsgHeader m_tRcvDataHeader;	//��������ͷ
//	u32 m_dwRcvedHeaderLen;					//�ѽ�������ͷ����
//	u8* m_pchRcvBuf;						//����������ָ��
//	u32 m_dwRcvBufLen;						//���������峤��
//	u32 m_dwRcvedBodyLen;					//�ѽ����峤��
//
//	TLightLock m_tRcvLock;				//������
//	TLightLock m_tSndLock;				//������
//	TFtpLibSndDataNode* ptSndLinkList;	//���������б�
//	BOOL m_bSndListFull;				//����list��
//	u32 m_dwSndDataState;				//��������״̬
//	u32 m_dwSndNodeNum;					//�������������Ա��
//
//	u32 m_dwSysRcvBufSize;			//ϵͳ�������ݻ����С����Ϊ0��Ĭ��Ϊ5k
//	u32 m_dwSysSndBufSize;			//ϵͳ�������ݻ����С����Ϊ0��Ĭ��Ϊ5k
//
//	u8	m_abSequence;					//���ͱ��
//
//	//��ǰ�����ļ���Ϣ
//	char m_abSndFilePath[FTPLIB_FILEDIR_LEN + FTPLIB_FILENAME_LEN + 10];		//������ļ���
//	char m_abSndFile[FTPLIB_FILENAME_LEN];		//������ļ���
//	char m_abSndSaveFile[FTPLIB_FILENAME_LEN];		//������ļ���
//	BOOL m_bSndNeedPro;				//�Ƿ���Ҫ����
//	u32	 m_dwSndFilePro;			//�ļ�����
//	u64	 m_qwSndFileSeek;			//�ļ�ƫ��
//	u64	 m_qwSndFileLen;			//�ļ�����
//	u32  m_dwSndResult;				//�ļ��Ƿ��ϴ����
//	FILE* m_pSndFileFd;				//�ļ����
//
//	char m_abRcvFilePath[FTPLIB_FILEDIR_LEN + FTPLIB_FILENAME_LEN + 10];		//������ļ���
//	char m_abRcvFile[FTPLIB_FILENAME_LEN];		//������ļ���
//	char m_abRcvSaveFile[FTPLIB_FILENAME_LEN];		//������ļ���
//	u32  m_dwRcvProPrecision;		//�Ƿ���Ҫ����
//	u32	 m_dwRcvFilePro;			//�ļ�����
//	u64	 m_qwRcvFileSeek;			//�ļ�ƫ��
//	u64	 m_qwRcvFileLen;			//�ļ�����
//	//u32  m_dwFileState;			//�ļ�״̬
//	u32  m_dwRcvResult;				//�ļ��Ƿ��ϴ����
//	FILE* m_pRcvFileFd;				//�ļ����
//
//	SOCKHANDLE m_hTCPSock;
//
//	//ͳ��
//	u32 m_dwConnectTimeS;		//��������ʱ��,���ӳ�ʱ������
//	u32 m_dwLastRcvTimeS;		// �������ݵ�ʱ��
//	u32 m_dwLastRcvDataLen;		//���һ�ζ������ݳ���
//	u32 m_dwLastSndDataLen;		//���һ�η������ݳ���
//
//	u64 m_qwRcvByteCnt;				//�����ֽ���
//	u64 m_qwSndByteCnt;				//�����ֽ���
//
//	u64 m_qwSndMsgCnt;					// �������ݴ���
//	u64 m_qwSndUserMsgCnt;				// �����û���Ϣ����
//	u64 m_qwSndSRRCnt;					// ����SRR���Ӵ���
//	u64 m_qwSndLabelCnt;				// ����Label��
//	u64 m_qwSndFileStartCnt;			// �����ļ���ʼ��
//	u64 m_qwSndFileGetCnt;				// ���ͻ�ȡ�ļ���
//	u64 m_qwSndCloseChnlCnt;			// ���͹ر�ͨ����
//
//	u64 m_qwRcvMsgCnt;			// ����������
//	u64 m_qwRcvUserMsgCnt;		// �����û���Ϣ����
//	u64 m_qwRcvSRRCnt;			// ����SRR���Ӵ���
//	u64 m_qwRcvLabelCnt;		// ����Label��
//	u64 m_qwRcvFileStartCnt;	// �����ļ���ʼ��
//	u64 m_qwRcvFileGetCnt;		// ���ջ�ȡ�ļ���
//	u64 m_qwRcvCloseChnlCnt;	// ���չر�ͨ����
//
//	u64 m_qwRcvSumCnt;				//������������
//	u64 m_qwRcvSucCnt;				//�������ݳɹ���
//	u64 m_qwRcvNoDataCnt;			//��������û������
//	u64 m_qwRcvFailCnt;				//��������ʧ������
//
//	u64 m_qwRcvHeadLenErrCnt;		//��������ͷ���ȴ���
//	u64 m_qwRcvBodyLenErrCnt;		//���������峤�ȴ���
//	u64 m_qwRcvBufLenOverCnt;		//�������ݳ��ȳ�����Χ
//
//	u64 m_qwRcvHeaderCnt;			//��������ͷ��
//	u64 m_qwRcvHeaderSucCnt;		//�������ݳɹ���
//	u64 m_qwRcvHeaderNoDataCnt;		//��������ͷû������
//	u64 m_qwRcvHeaderFailCnt;		//��������ʧ������
//
//	u64 m_qwRcvBodyCnt;				//������������
//	u64 m_qwRcvBodySucCnt;			//�������ݳɹ���
//	u64 m_qwRcvBodyNoDataCnt;		//����������û������
//	u64 m_qwRcvBodyFailCnt;			//��������ʧ������
//
//	u64 m_qwSndSumCnt;				//���ݷ��ʹ���
//	u64 m_qwSndSucCnt;				//���ݷ��ͳɹ�����
//	u64 m_qwSndTryAgainCnt;			//���ݷ���TryAgain����
//	u64 m_qwSndFailCnt;				//���ݷ���ʧ�ܴ���
//
//	u64 m_qwSndHeadCnt;				//����ͷ������
//	u64 m_qwSndHeadSucCnt;			//����ͷ���ͳɹ���
//	u64 m_qwSndHeadTryAgainCnt;		//����ͷ����TryAgain����
//	u64 m_qwSndHeadFailCnt;			//����ͷ����ʧ����
//
//	u64 m_qwSndBodyCnt;				//������������
//	u64 m_qwSndBodySucCnt;			//����������ɹ���
//	u64 m_qwSndBodyTryAgainCnt;		//�����巢��TryAgain����
//	u64 m_qwSndBodyFailCnt;			//����������ʧ����
//
//	u64 m_qwListSndCnt;				//���������б���
//	u64 m_qwListSndSucCnt;			//���������б�ɹ���
//	u64 m_qwListSndTryAgainCnt;		//�����б���TryAgain����
//	u64 m_qwListSndFailCnt;			//���������б�ʧ����
//
//	u64 m_qwSndFileCnt;				// �����ļ���
//	u64 m_qwListSndFileCnt;			// �����б����ļ���
//	u64	m_qwSndFileNodeCnt;			// �����ļ��ڵ���
//	u64 m_qwSndFileSucCnt;			// ���ͳɹ��ļ���
//	u64 m_qwSndFileFailCnt;			// ����ʧ���ļ���
//
//	u64 m_qwConnectCBCnt;			// �ص������¼�
//	u64 m_qwDisConnectCBCnt;		// �ص������¼�
//	u64 m_qwRcvDataCBCnt;			// �ص����ݽ����¼�
//
//	u64 m_qwSndFileProCbCnt;			// �����ļ����Ȼص���
//	u64 m_qwSndFileEndCbCnt;			// �����ļ���ɻص���
//	u64 m_qwSndFileFailCbCnt;			// �����ļ�ʧ�ܵ���
//
//	u64 m_qwStartRcvFileCbCnt;			// ��ʼ�����ļ��ص���
//	u64 m_qwRcvFileProCbCnt;			// �����ļ����Ȼص���
//	u64 m_qwRcvFileEndCbCnt;			// �����ļ���ɻص���
//	u64 m_qwRcvFileFailCbCnt;			// �����ļ�ʧ�ܻص���
//
//	u64 m_qwSndFileDataCnt;				// �����ļ�������
//	u64 m_qwSndFileTryAgainCnt;			// �����ļ�TryAgain����
//	u64 m_qwSndFileDataSucCnt;			// ���ͳɹ��ļ�������
//	u64 m_qwSndFileDataFailCnt;			// ����ʧ���ļ�������
//
//	u64 m_qwRcvFileCnt;					// �����ļ���
//	u64 m_qwRcvFileSucCnt;				// ���ճɹ��ļ���
//	u64 m_qwRcvFileFailCnt;				// ����ʧ���ļ���
//
//	u64 m_qwRcvFileDataCnt;				// �����ļ�������
//	u64 m_qwRcvFileDataSucCnt;			// ���ճɹ��ļ�������
//	u64 m_qwRcvFileDataNoDataCnt;		// �����ļ�û������
//	u64 m_qwRcvFileDataFailCnt;			// ����ʧ���ļ�������
//
//}TFtpLibChnl;
//
//
////������Ϣ
//typedef struct tTFtpLibServer
//{
//	BOOL m_bSvrUsed;		//�Ƿ�ʹ��
//	BOOL m_bIsUdpSvr;		//�Ƿ�ΪUdp����
//	BOOL m_bUseDataCheck;			//�Ƿ�ʹ������У��,Udp����ʱ��Ч
//
//	u8 m_achSvrName[FTPLIB_SVRNAME_LEN + 1];	//��������
//	char m_achSvrWebId[FTPLIB_SVRDES_LEN];		//��������Id����
//	char m_achSvrWebDes[FTPLIB_SVRDES_LEN];		//����������������
//
//	char m_achSvrInfoWebId[FTPLIB_SVRDES_LEN];		//������ϢId����
//	char m_achSvrInfoWebDes[FTPLIB_SVRDES_LEN];		//������Ϣ��������
//	char m_achSvrChnlWebId[FTPLIB_SVRDES_LEN];		//����ͨ����ϢId����
//	char m_achSvrChnlWebDes[FTPLIB_SVRDES_LEN];		//����ͨ����Ϣ��������
//
//	u32 m_dwPackMaxLen;			//���������ݳ���
//	u32 m_dwSndLstNodeNum;		//�������ݻ���Node��
//
//	u32 m_dwSysRcvBufSize;			//ϵͳ�������ݻ����С����Ϊ0��Ĭ��Ϊ5k
//	u32 m_dwSysSndBufSize;			//ϵͳ�������ݻ����С����Ϊ0��Ĭ��Ϊ5k
//
//	u32 m_dwCapSize;						//tcp��������
//	u32 m_dwBindIp;							//�����Ip
//	u16 m_wBindPort;						//tcp�󶨶˿ں�
//
//	TFtpLibInstMark m_tSvrMark;				//Server���
//	SOCKET m_dwListenSocket;					//socket
//	BOOL m_bStartListen;
//
//	TLightLock m_tChnlLock;				//ͨ����
//
//	u32 m_ChnlNextId;			//��һ����ѯʹ�õĳ�ԱId
//	TFtpLibChnl* ptChnlList;		//ͨ���б�
//	// ͳ��
//	u32 m_dwChnlUsingNum;	//��Աʹ������
//
//	u64 m_qwAcceptNum;			// �������Ӵ���
//	u64 m_qwAcceptSucNum;		// ���ܳɹ�����
//	u64 m_qwAcceptFailNum;		// ����ʧ�ܴ���
//	int m_iAcceptFailCode;		// ����ʧ�������
//	u64 m_qwCloseSockNum;		// �ر�socket����
//
//	u64 m_qwRcvMsgNum;			// ����������
//	u64 m_qwRcvUserMsgNum;		// �����û���Ϣ����
//	u64 m_qwRcvSRRNum;			// ����SRR���Ӵ���
//	u64 m_qwRcvLabelNum;		// ����Label��
//	u64 m_qwRcvFileStartNum;	// �����ļ���ʼ��
//	u64 m_qwRcvFileGetNum;		// ���ջ�ȡ�ļ���
//	u64 m_qwRcvCloseChnlNum;	// ���չر�ͨ����
//
//	u64 m_qwRcvNum;				// ����������
//	u64 m_qwRcvSucNum;			// �������ݳɹ���
//	u64 m_qwRcvFailNum;			// ��������ʧ����
//
//	u64 m_qwRcvHeadNum;				// ��������ͷ��
//	u64 m_qwRcvHeadSucNum;			// ��������ͷ�ɹ���
//	u64 m_qwRcvHeadFailNum;			// ��������ͷʧ����
//
//	u64 m_qwRcvBodyNum;				// ������������
//	u64 m_qwRcvBodySucNum;			// ����������ɹ���
//	u64 m_qwRcvBodyFailNum;			// ����������ʧ����
//
//	u64 m_qwSndMsgNum;					// �������ݴ���
//	u64 m_qwSndUserMsgNum;				// �����û���Ϣ����
//	u64 m_qwSndSRRNum;					// ����SRR���Ӵ���
//	u64 m_qwSndLabelNum;				// ����Label��
//	u64 m_qwSndFileStartNum;			// �����ļ���ʼ��
//	u64 m_qwSndFileGetNum;				// ���ͻ�ȡ�ļ���
//	u64 m_qwSndCloseChnlNum;			// ���͹ر�ͨ����
//
//	u64 m_qwSndHeadNum;					// ��������ͷ����
//	u64 m_qwSndHeadSucNum;				// ��������ͷ�ɹ�����
//	u64 m_qwSndHeadTryAgainNum;			// ��������ͷ���Դ���
//	u64 m_qwSndHeadFailNum;				// ��������ͷʧ�ܴ���
//
//	u64 m_qwSndBodyNum;					// �������������
//	u64 m_qwSndBodySucNum;				// ����������ɹ�����
//	u64 m_qwSndBodyTryAgainNum;			// ���������峢�Դ���
//	u64 m_qwSndBodyFailNum;				// ����������ʧ�ܴ���
//
//	u64 m_qwListSndNum;				//���������б���
//	u64 m_qwListSndSucNum;			//���������б�ɹ���
//	u64 m_qwListSndTryAgainNum;		//���������б��Դ���
//	u64 m_qwListSndFailNum;			//���������б�ʧ����
//
//	u64 m_qwSndFileNum;				// �����ļ���
//	u64 m_qwListSndFileNum;			// �����ļ��б�ڵ���
//	u64 m_qwSndFileSucNum;			// ���ͳɹ��ļ���
//	u64 m_qwSndFileFailNum;			// ����ʧ���ļ���
//
//	u64 m_qwRcvFileNum;				// �����ļ���
//	u64 m_qwRcvFileSucNum;			// ���ͳɹ��ļ���
//	u64 m_qwRcvFileFailNum;			// ����ʧ���ļ���
//
//	u64 m_qwDataCheckUpFail;		//��Ϣ���ݼ��ʧ��
//	u64 m_qwDataCheckUpSuc;			//��Ϣ���ݼ��ɹ�
//
//	u64 m_qwConnectCBNum;		//�ص������¼�
//	u64 m_qwDisConnectCBNum;		//�ص������¼�
//	u64 m_qwRcvDataCBNum;		//�ص����ݽ����¼�
//	u64 m_qwUdpRcvDataCBNum;		//�ص�Udp���ݽ����¼�
//	u64 m_qwFileDataCBNum;		//�ص����ݽ����¼�
//
//}TFtpLibServer;
//
////����ͷ 
//typedef struct tFtpLibMsgHeader
//{
//	u8 m_chFirstFlag;			//��һλ��ʶ
//	u8 m_chSecondFlag;			//�ڶ�λ��ʶ
//	u8 m_chVersion;				//�汾��
//	u8 m_chSequence;			//���
//
//	u32 m_dwMsgType;			//����
//	u32 m_dwDataBodyLen;		//��Ϣ����
//	u32 m_dwHeadCheck;			//��Ϣͷ���λ
//}TFtpLibMsgHeader;
//
////����������Ϣ
//typedef struct tFtpLibSndDataNode
//{
//	u32 m_dwDataType;		//��������
//	u32 m_dwDataLen;		//���ݳ���
//	u32 m_dwSndedLen;		//�ѷ�������
//	u8* m_pchDataBuf;
//
//	//�����ļ�����
//	FILE* m_dwFileFd;			//�ļ����
//	char m_achTransFilePath[FTPLIB_FILEDIR_LEN + FTPLIB_FILENAME_LEN];		//�ļ�Ŀ¼
//	char m_achTransFileName[FTPLIB_FILENAME_LEN];	//�ļ���
//	char m_achSaveFileName[FTPLIB_FILENAME_LEN];		//�����ļ���
//	u64 m_qwFileLen;			//�ļ�����
//	u64 m_qwSeekLen;			//ƫ�Ƴ���
//	u32 m_dwProPrecision;				//���Ⱦ���
//
//	struct tFtpLibSndDataNode* ptNextNode;
//
//}TFtpLibSndDataNode;




//��ʼ���������ݽṹ
typedef struct tLibFtpInitPara
{
	u32 m_dwAllChnlMaxNum;					//����ͨ�������������TCP��UDP����Э��Ҫ�õ���ͨ��
	u32 m_dwSvrNum;							//��������
	u32 m_dwCltNum;							//�ͻ���ͨ������
	u32 m_dwSingleRRCltNum;					//���οͻ���ͨ������
	u32 m_dwRcvThreadNum;					//�����߳���
	u32 m_dwSndThreadNum;					//�����߳���

	u16 m_wRcvRousePort;					//�����̻߳���ʹ�ö˿�,Ĭ��9050,�ڲ�ʹ��
	u16 m_wSndRousePort;					//�����̻߳���ʹ�ö˿ڣ�Ĭ��9051���ڲ�ʹ��

	u32 m_dwMaxLocalMsgLen;					//������Ϣ��󳤶ȣ���λ�ֽڣ�Ĭ��1k

	u32 m_dwSRRCheckTimerSec;				//SRR���ն�ʱ����������ڣ�Ĭ��30��

	LibFtpEventCB m_pHpComEventPrc;			//�ϱ��¼�����



}TLibFtpInitPara;


//�ļ��¼����ݽṹ
typedef struct tLibFtpEvtData
{
	u64 m_qwChnlId;					//ͨ��Id

	s8* m_achIP;
	s8* m_achPort;
	s8* m_achUsername;
	s8* m_achPassword;
	s8* m_achSFtpPath;

	u64 m_qwFileLen;				//�ļ�����
	u32 m_dwFilePro;				//�ļ�����
}TLibFtpEvtData;

//�ļ�������Ϣ
typedef struct tFtpLibTranFileInfo
{
	char m_achRcvFileDir[LIBFTP_FILEDIR_LEN];		//�����ļ�Ŀ¼
	char m_achReadFileDir[LIBFTP_FILEDIR_LEN];	//��ȡ�ļ�Ŀ¼
	//u32 m_dwRcvProPre;							//���ս��Ⱦ���
	//u32 m_dwSndProPre;							//���ͽ��Ⱦ���

	FILE* m_pTransFileFd;			//�ļ����

	u64 m_qwSndFileNum;			//�����ļ�����
	u64 m_qwSndFileSucNum;			//�����ļ��ɹ���
	u64 m_qwSndFileFailNum;			//�����ļ�ʧ����
}TFtpLibTranFileInfo;



#endif