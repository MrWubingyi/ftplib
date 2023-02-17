#ifndef _H_LIBFTP_
#define _H_LIBFTP_
#pragma once
#include"LibFtpstdafx.h"

#define LIBFTP_FILENAME_LEN			32		//文件名长度
#define LIBFTP_FILEDIR_LEN			128		//文件目录长度
#define LIBFTP_SVRNAME_LEN			32
#define LIBFTP_SVRDES_LEN			128


#define LIBFTP_INVALID_SOCKET 0xffffffff//127.0.0.1
#define LIBFTP_SYSTEM_FAIL			-1

#define LIBFTP_EPOLLEVENT_NUM 64//所有通道最大数
#define LIBFTP_CONNECTFD_SIZE 1024

#define PACKET_SIZE (1024 - sizeof(int) * 3)


#define INET_ADDRLEN 20

#define IP_MAX_LEN 255

#define FILE_BUF_SIZE 102400

#define LIBFTP_READFILE_LEN			10 << 10		//每次读文件长度
//
// 事件回调
typedef u32(*LibFtpEventCB)(IN u32 eEvtType, IN void* pEvtData);

//FtpLib事件类型
typedef enum eLibFtpEvntType
{
	E_LIBFTP_CONNECT_EVENT = 0,		//连接事件
	E_LIBFTP_DISCONNECT_EVENT,		//断链事件，断链后会自己释放通道
	E_LIBFTP_RCVDATA_EVENT,			//接收数据事件
	E_LIBFTP_SRRRCVDATA_EVENT,		//单次请求通道接收数据事件(回调接口返回值为返回后要发几条消息,方便换手)
	E_LIBFTP_UDPRCVDATA_EVENT,		//UDP接收数据事件
	E_LIBFTP_RCVFILE_EVENT,			//接收文件事件
	E_LIBFTP_SNDFILE_EVENT,			//发送文件事件

	E_LIBFTP_LOCAL_EVENT,			//本地消息事件

}EFtpLibEvntType;

////文件事件类型
//typedef enum eFtpLibFileEvtType
//{
//	E_FTPLIB_FILE_RCV_START = 0,		//文件接收开始,返回值为该文件的接收进度精度:1,10,1000;返回0为默认精度
//	E_FtpLib_FILE_RCV_PRO,			//文件接收进度
//	E_FtpLib_FILE_RCV_END,			//文件接收结束,返回值为1则会在回调后删除该文件,为0则保留 
//	E_FtpLib_FILE_RCV_FAIL,			//文件接收失败
//
//	E_FtpLib_FILE_SND_PRO,			//文件发送进度
//	E_FtpLib_FILE_SND_END,			//文件发送结束
//	E_FtpLib_FILE_SND_FAIL,			//文件发送失败
//}EFtpLibFileEvtType;
//
////连接/断链事件数据结构
//typedef struct tFtpLibConctEvtData
//{
//	u32 m_dwPeerIP;			//对端IP
//	u16 m_wPeerPort;		//对端端口
//
//	u64 m_qwChnlId;			//通道Id，全局唯一的ID
//}TFtpLibConctEvtData;
//
////接收数据事件数据结构
//typedef struct tFtpLibRcvEvtData
//{
//	u64 m_qwChnlId;			//通道Id
//
//	u8* m_ptDataBuf;		//数据buf
//	u32 m_dwDataSize;		//数据buf大小
//}TFtpLibRcvEvtData;
//
////接收数据事件数据结构
//typedef struct tFtpLibUdpRcvEvtData
//{
//	BOOL m_bIsClient;		//是否为客户端
//	u64 m_qwChnlId;			//通道Id，在m_bIsClient为TRUE时有效
//	u32 m_dwSvrId;			//服务Id，在m_bIsClient为FALSE时有效
//
//	u32 m_dwPeerIp;			//对端Ip
//	u16 m_wPeerPort;		//对端端口号
//	u8* m_ptDataBuf;		//数据buf
//	u32 m_dwDataSize;		//数据buf大小
//}TFtpLibUdpRcvEvtData;
//
////文件事件数据结构
//typedef struct tFtpLibFileEvtData
//{
//	u64 m_qwChnlId;					//通道Id
//	u32 m_FileEvt;					//文件事件
//	char m_achFileName[FTPLIB_FILENAME_LEN];		//文件名称
//
//	u64 m_qwFileLen;				//文件长度
//	u32 m_dwFilePro;				//文件进度
//
//}TFtpLibFileEvtData;
//
////本地消息事件数据结构
//typedef struct tFtpLibLocalEvtData
//{
//	u32 m_dwType;		//消息类型，返回用户发送消息时设置的消息类型
//	char* m_pData;		//消息指针,可能为NULL，当m_dwDataLen为0时
//	u32 m_dwDataLen;	//消息长度
//
//}TFtpLibLocalEvtData;

//
////服务端参数
//typedef struct tFtpLibSvrPara
//{
//	u32 m_dwCapSize;				//服务连接容量
//	u32 m_dwBindIp;					//服务绑定Ip，设置"0.0.0.0"允许所有ip连接，"127.0.0.1"只允许本机连接
//	u16 m_wBindPort;				//服务的tcp绑定端口号
//	u8  m_achSvrName[FTPLIB_SVRNAME_LEN];	//服务名称,最长32个字节
//
//	u32 m_dwSvrMaxDataLen;			//最大数据包长度,若为0则默认5k
//	u32 m_dwSvrSndLstNodeNum;		//发送数据缓冲Node数,若为0则默认为10
//
//	u32 m_dwSysRcvBufSize;			//系统接收数据缓冲大小，若为0则默认为10k
//	u32 m_dwSysSndBufSize;			//系统发送数据缓冲大小，若为0则默认为10k
//
//}TFtpLibSvrPara;
//
////udp服务端参数
//typedef struct tFtpLibUdpSvrPara
//{
//	u32 m_dwBindIp;					//服务绑定Ip，设置"0.0.0.0"允许所有ip连接，"127.0.0.1"只允许本机连接
//	u16 m_wBindPort;				//服务的tcp绑定端口号
//	u8  m_achSvrName[FTPLIB_SVRNAME_LEN];	//服务名称,最长32个字节
//
//	u32 m_dwSvrMaxDataLen;			//最大数据包长度,若为0则默认1400
//
//	u32 m_dwSysRcvBufSize;			//系统接收数据缓冲大小，若为0则默认为10k
//	u32 m_dwSysSndBufSize;			//系统发送数据缓冲大小，若为0则默认为10k
//
//	BOOL m_bUseDataCheck;			//是否使用数据校验
//
//}TFtpLibUdpSvrPara;
//
////客户端参数
//typedef struct tFtpLibCltPara
//{
//	u32 m_dwRemoteSvrIp;			//远端服务器Ip
//	u16 m_wRemoteSvrPort;			//远端服务器端口
//	u32 m_dwLocalBindIp;			//本地绑定Ip
//	u16 m_wLocalBindPort;			//本地绑定端口（建议不指定，会出现端口重用的问题，不指定填0即可）
//
//	char* m_pchCltLabel;			//通道Label
//	u32 m_dwLabelLen;				//label长度
//
//	u32 m_dwChnlMaxDataLen;			//最大数据包长度,若为0则默认10240
//	u32 m_dwChnlSndLstNodeNum;		//发送数据缓冲Node数,若为0则默认为10
//
//	u32 m_dwSysRcvBufSize;			//系统接收数据缓冲大小，若为0则默认为10k
//	u32 m_dwSysSndBufSize;			//系统发送数据缓冲大小，若为0则默认为10k
//
//}TFtpLibCltPara;
//
////客户端参数
//typedef struct tFtpLibUdpCltPara
//{
//	u32 m_dwLocalBindIp;			//本地绑定Ip，使用本机IP,绑定127.0.0.1只能发给本机
//	u16 m_wLocalBindPort;			//本地绑定端口,若端口设置为0则使用系统分配端口
//
//	u32 m_dwChnlMaxDataLen;			//最大数据包长度,若为0则默认1400
//
//	u32 m_dwSysRcvBufSize;			//系统接收数据缓冲大小，若为0则默认为10k
//	u32 m_dwSysSndBufSize;			//系统发送数据缓冲大小，若为0则默认为10k
//
//	BOOL m_bUseDataCheck;			//是否使用数据校验
//
//}TFtpLibUdpCltPara;
//

//文件事件类型
typedef enum eLibFtpFileType
{
	E_FTPLIB_FILE_DIR_RCV = 0,		//接收文件目录
	E_FTPLIB_FILE_DIR_READ,			//获取文件目录

}ELibFtpFileType;

//错误码
typedef enum eFtpLibErrCode
{
	LIBFTP_OK = 0,						   //操作成功
	LIBFTP_System,                          //系统错误
	LIBFTP_InstLimit,                       //无可用实例
	LIBFTP_InstInvalid,                     //无效实例
	LIBFTP_InvalidConn,                     //无效连接
	LIBFTP_NotInit,                         //未初始化
	LIBFTP_AlreadyInit,                     //已经初始化
	LIBFTP_ParamErr,                        //参数错误
	LIBFTP_MsgErr,                          //消息错误
	LIBFTP_MsgHeadErr,                      //消息错误
	LIBFTP_ObjNotExist,                     //操作对象不存在
	LIBFTP_ChnErr,                          //错误的通道号
	LIBFTP_SvrLimit,                        //服务器资源不足
	LIBFTP_Timeout,                         //超时
	LIBFTP_ISEXIST,                         //已存在

}EFtpLibErrCode;

//定义标记
typedef enum eMsgTag
{
	MSG_FILENAME = 1,        // 文件名称                服务器使用
	MSG_FILESIZE = 2,        // 文件大小                客户端使用
	MSG_READY_READ = 3,        // 准备接受                客户端使用
	MSG_SENDFILE = 4,        // 发送                    服务器使用
	MSG_SUCCESSED = 5,        // 传输完成                两者都使用
	MSG_OPENFILE_FAILD = 6         // 告诉客户端文件找不到    客户端使用
}EMSGTAG;

//基本信息
typedef struct eLibFtpBaseInfo
{
	u32 m_dwAllChnlMaxNum;					//所有通道最大数，包括TCP，UDP两种协议要用到的通道
	u32 m_dwSvrNum;							//服务容量
	u32 m_dwCltNum;							//客户端通道容量
	u32 m_dwSingleRRCltNum;					//单次客户端通道容量
	u32 m_dwRcvThreadNum;					//接收线程数，默认10
	u32 m_dwSndThreadNum;					//发送线程数，默认4
	u32 m_dwSRRCheckTime;					//SRR回收定时器，检查周期，默认30秒

	LibFtpEventCB m_pFtpLibEventPrc;			//上报事件函数

	u32 m_dwRcvEpollFd;						//接收epoll句柄
	u32 m_dwSndEpollFd;						//发送epoll句柄

	u32 m_dwEpollListenTask;				//epoll侦听事件线程
	u32 m_dwIsCheckUpSRR;					//是否检查SRR

	u32 m_dwExistSvrCnt;		// 创建服务端次数
	u32 m_dwExistCltCnt;		// 创建客户端次数
	u32 m_dwExistSRRCltCnt;		// 创建单次请求客户端次数

	u64 m_qwCreatSockNum;		// 创建socket次数
	u64 m_qwAccpetSockNum;		// 接受连接socket次数
	u64 m_qwCloseSockNum;		// 关闭socket次数

	u64 m_qwStartEpollRcvWait;		//开始epollwait事件总数
	u64 m_qwStartEpollSndWait;		//开始epollwait事件总数
	u64 m_qwEpollRcvWaitEvent;		//epollRcvwait事件总数
	u64 m_qwEpollSndWaitEvent;			//epollwait事件总数
	u64 m_qwEpollAccpetEvent;		//EpollAccpet事件总数
	u64 m_qwEpollRcvDataEvent;		//EpollRcvData事件总数
	u64 m_qwEpollUdpRcvDataEvent;		//EpollUdpRcvData事件总数
	u64 m_qwEpollSndDataEvent;		//EpollSndData事件总数
	u64 m_qwEpollAbnormalEvent;		//Epoll异常事件总数

}TLibFtpBaseInfo;

////实例标记
//typedef struct tFtpLibInstMark
//{
//	u32 m_dwHighLevel;					//高一级	（clt通道中表示服务索引）		（服务中表示服务索引）	
//	u32 m_dwLowLevel;					//低一级	（clt通道中表示clt通道索引）	（服务中表示服务类型，tcp或者udp）
//
//}TFtpLibInstMark;
//
////成员信息
//typedef struct tFtpLibChnl
//{
//	BOOL m_bUsed;				//是否被使用
//	BOOL m_bIsUdpChnl;			//是否为Udp通道
//	BOOL m_bUseDataCheck;			//是否使用数据校验，为Udp通道时有效
//	u32 m_dwChnlUseTimes;		//使用次数
//	u32 m_dwFtpLibId;			//连接在列表中的索引号
//	u64 m_qwChnlId;				//chnlId
//	TFtpLibInstMark m_tChnlMark;	//Chnl标记,高一级代表服务索引，低一级代表通道索引
//	BOOL m_bIsSRRChnl;			//是否为单次请求通道
//	u32 m_dwSRRChnlState;		//单次请求通道状态
//	BOOL m_bSRRCBING;			//单次请求是否处于正在回调状态
//	u32 m_SRRCbSndNum;			//回调后要发送消息数
//
//	u32 m_dwPackMaxLen;			//最大接收数据长度
//	u32 m_dwSndLstNodeNum;		//发送数据缓冲Node数
//
//	u32 m_dwOppIP;
//	u16 m_wOppPort;
//	u32 m_dwBindIp;					//远端服务器Ip
//	u16 m_wBindPort;				//本地绑定端口
//	BOOL m_bConnected;				//是否连接成功
//	char* m_pchChnlLabel;			//通道Label
//	u32 m_dwLabelLen;				//Label长度
//
//	u32 m_dwRcvDataState;				//接收数据状态
//	TFtpLibMsgHeader m_tRcvDataHeader;	//接收数据头
//	u32 m_dwRcvedHeaderLen;					//已接收数据头长度
//	u8* m_pchRcvBuf;						//接收数据体指针
//	u32 m_dwRcvBufLen;						//接收数据体长度
//	u32 m_dwRcvedBodyLen;					//已接收体长度
//
//	TLightLock m_tRcvLock;				//接收锁
//	TLightLock m_tSndLock;				//发送锁
//	TFtpLibSndDataNode* ptSndLinkList;	//发送数据列表
//	BOOL m_bSndListFull;				//发送list满
//	u32 m_dwSndDataState;				//接收数据状态
//	u32 m_dwSndNodeNum;					//接收数据链表成员数
//
//	u32 m_dwSysRcvBufSize;			//系统接收数据缓冲大小，若为0则默认为5k
//	u32 m_dwSysSndBufSize;			//系统发送数据缓冲大小，若为0则默认为5k
//
//	u8	m_abSequence;					//发送编号
//
//	//当前发送文件信息
//	char m_abSndFilePath[FTPLIB_FILEDIR_LEN + FTPLIB_FILENAME_LEN + 10];		//请求的文件名
//	char m_abSndFile[FTPLIB_FILENAME_LEN];		//请求的文件名
//	char m_abSndSaveFile[FTPLIB_FILENAME_LEN];		//保存的文件名
//	BOOL m_bSndNeedPro;				//是否需要进度
//	u32	 m_dwSndFilePro;			//文件进度
//	u64	 m_qwSndFileSeek;			//文件偏移
//	u64	 m_qwSndFileLen;			//文件长度
//	u32  m_dwSndResult;				//文件是否上传完成
//	FILE* m_pSndFileFd;				//文件句柄
//
//	char m_abRcvFilePath[FTPLIB_FILEDIR_LEN + FTPLIB_FILENAME_LEN + 10];		//请求的文件名
//	char m_abRcvFile[FTPLIB_FILENAME_LEN];		//请求的文件名
//	char m_abRcvSaveFile[FTPLIB_FILENAME_LEN];		//保存的文件名
//	u32  m_dwRcvProPrecision;		//是否需要进度
//	u32	 m_dwRcvFilePro;			//文件进度
//	u64	 m_qwRcvFileSeek;			//文件偏移
//	u64	 m_qwRcvFileLen;			//文件长度
//	//u32  m_dwFileState;			//文件状态
//	u32  m_dwRcvResult;				//文件是否上传完成
//	FILE* m_pRcvFileFd;				//文件句柄
//
//	SOCKHANDLE m_hTCPSock;
//
//	//统计
//	u32 m_dwConnectTimeS;		//调用连接时间,连接超时处理用
//	u32 m_dwLastRcvTimeS;		// 最后读数据的时间
//	u32 m_dwLastRcvDataLen;		//最后一次读的数据长度
//	u32 m_dwLastSndDataLen;		//最后一次发送数据长度
//
//	u64 m_qwRcvByteCnt;				//接收字节数
//	u64 m_qwSndByteCnt;				//发送字节数
//
//	u64 m_qwSndMsgCnt;					// 发送数据次数
//	u64 m_qwSndUserMsgCnt;				// 发送用户消息次数
//	u64 m_qwSndSRRCnt;					// 发送SRR连接次数
//	u64 m_qwSndLabelCnt;				// 发送Label数
//	u64 m_qwSndFileStartCnt;			// 发送文件开始数
//	u64 m_qwSndFileGetCnt;				// 发送获取文件数
//	u64 m_qwSndCloseChnlCnt;			// 发送关闭通道数
//
//	u64 m_qwRcvMsgCnt;			// 接收数据数
//	u64 m_qwRcvUserMsgCnt;		// 接收用户消息次数
//	u64 m_qwRcvSRRCnt;			// 接受SRR连接次数
//	u64 m_qwRcvLabelCnt;		// 接收Label数
//	u64 m_qwRcvFileStartCnt;	// 接收文件开始数
//	u64 m_qwRcvFileGetCnt;		// 接收获取文件数
//	u64 m_qwRcvCloseChnlCnt;	// 接收关闭通道数
//
//	u64 m_qwRcvSumCnt;				//接收数据总数
//	u64 m_qwRcvSucCnt;				//接收数据成功数
//	u64 m_qwRcvNoDataCnt;			//接收数据没数据数
//	u64 m_qwRcvFailCnt;				//接收数据失败总数
//
//	u64 m_qwRcvHeadLenErrCnt;		//接收数据头长度错误
//	u64 m_qwRcvBodyLenErrCnt;		//接收数据体长度错误
//	u64 m_qwRcvBufLenOverCnt;		//接收数据长度超出范围
//
//	u64 m_qwRcvHeaderCnt;			//接收数据头数
//	u64 m_qwRcvHeaderSucCnt;		//接收数据成功数
//	u64 m_qwRcvHeaderNoDataCnt;		//接收数据头没数据数
//	u64 m_qwRcvHeaderFailCnt;		//接收数据失败总数
//
//	u64 m_qwRcvBodyCnt;				//接收数据体数
//	u64 m_qwRcvBodySucCnt;			//接收数据成功数
//	u64 m_qwRcvBodyNoDataCnt;		//接收数据体没数据数
//	u64 m_qwRcvBodyFailCnt;			//接收数据失败总数
//
//	u64 m_qwSndSumCnt;				//数据发送次数
//	u64 m_qwSndSucCnt;				//数据发送成功次数
//	u64 m_qwSndTryAgainCnt;			//数据发送TryAgain次数
//	u64 m_qwSndFailCnt;				//数据发送失败次数
//
//	u64 m_qwSndHeadCnt;				//数据头发送数
//	u64 m_qwSndHeadSucCnt;			//数据头发送成功数
//	u64 m_qwSndHeadTryAgainCnt;		//数据头发送TryAgain次数
//	u64 m_qwSndHeadFailCnt;			//数据头发送失败数
//
//	u64 m_qwSndBodyCnt;				//发送数据体数
//	u64 m_qwSndBodySucCnt;			//发送数据体成功数
//	u64 m_qwSndBodyTryAgainCnt;		//数据体发送TryAgain次数
//	u64 m_qwSndBodyFailCnt;			//发送数据体失败数
//
//	u64 m_qwListSndCnt;				//发送数据列表数
//	u64 m_qwListSndSucCnt;			//发送数据列表成功数
//	u64 m_qwListSndTryAgainCnt;		//数据列表发送TryAgain次数
//	u64 m_qwListSndFailCnt;			//发送数据列表失败数
//
//	u64 m_qwSndFileCnt;				// 发送文件数
//	u64 m_qwListSndFileCnt;			// 发送列表发送文件数
//	u64	m_qwSndFileNodeCnt;			// 发送文件节点数
//	u64 m_qwSndFileSucCnt;			// 发送成功文件数
//	u64 m_qwSndFileFailCnt;			// 发送失败文件数
//
//	u64 m_qwConnectCBCnt;			// 回调连接事件
//	u64 m_qwDisConnectCBCnt;		// 回调断链事件
//	u64 m_qwRcvDataCBCnt;			// 回调数据接收事件
//
//	u64 m_qwSndFileProCbCnt;			// 发送文件进度回调数
//	u64 m_qwSndFileEndCbCnt;			// 发送文件完成回调数
//	u64 m_qwSndFileFailCbCnt;			// 发送文件失败调数
//
//	u64 m_qwStartRcvFileCbCnt;			// 开始接收文件回调数
//	u64 m_qwRcvFileProCbCnt;			// 接收文件进度回调数
//	u64 m_qwRcvFileEndCbCnt;			// 接收文件完成回调数
//	u64 m_qwRcvFileFailCbCnt;			// 接收文件失败回调数
//
//	u64 m_qwSndFileDataCnt;				// 发送文件数据数
//	u64 m_qwSndFileTryAgainCnt;			// 发送文件TryAgain次数
//	u64 m_qwSndFileDataSucCnt;			// 发送成功文件数据数
//	u64 m_qwSndFileDataFailCnt;			// 发送失败文件数据数
//
//	u64 m_qwRcvFileCnt;					// 接收文件数
//	u64 m_qwRcvFileSucCnt;				// 接收成功文件数
//	u64 m_qwRcvFileFailCnt;				// 接收失败文件数
//
//	u64 m_qwRcvFileDataCnt;				// 接收文件数据数
//	u64 m_qwRcvFileDataSucCnt;			// 接收成功文件数据数
//	u64 m_qwRcvFileDataNoDataCnt;		// 接收文件没数据数
//	u64 m_qwRcvFileDataFailCnt;			// 接收失败文件数据数
//
//}TFtpLibChnl;
//
//
////服务信息
//typedef struct tTFtpLibServer
//{
//	BOOL m_bSvrUsed;		//是否被使用
//	BOOL m_bIsUdpSvr;		//是否为Udp服务
//	BOOL m_bUseDataCheck;			//是否使用数据校验,Udp服务时有效
//
//	u8 m_achSvrName[FTPLIB_SVRNAME_LEN + 1];	//服务名称
//	char m_achSvrWebId[FTPLIB_SVRDES_LEN];		//服务网管Id名称
//	char m_achSvrWebDes[FTPLIB_SVRDES_LEN];		//服务网管描述名称
//
//	char m_achSvrInfoWebId[FTPLIB_SVRDES_LEN];		//服务信息Id名称
//	char m_achSvrInfoWebDes[FTPLIB_SVRDES_LEN];		//服务信息描述名称
//	char m_achSvrChnlWebId[FTPLIB_SVRDES_LEN];		//服务通道信息Id名称
//	char m_achSvrChnlWebDes[FTPLIB_SVRDES_LEN];		//服务通道信息描述名称
//
//	u32 m_dwPackMaxLen;			//最大接收数据长度
//	u32 m_dwSndLstNodeNum;		//发送数据缓冲Node数
//
//	u32 m_dwSysRcvBufSize;			//系统接收数据缓冲大小，若为0则默认为5k
//	u32 m_dwSysSndBufSize;			//系统发送数据缓冲大小，若为0则默认为5k
//
//	u32 m_dwCapSize;						//tcp连接容量
//	u32 m_dwBindIp;							//服务绑定Ip
//	u16 m_wBindPort;						//tcp绑定端口号
//
//	TFtpLibInstMark m_tSvrMark;				//Server标记
//	SOCKET m_dwListenSocket;					//socket
//	BOOL m_bStartListen;
//
//	TLightLock m_tChnlLock;				//通道锁
//
//	u32 m_ChnlNextId;			//下一个轮询使用的成员Id
//	TFtpLibChnl* ptChnlList;		//通道列表
//	// 统计
//	u32 m_dwChnlUsingNum;	//成员使用数量
//
//	u64 m_qwAcceptNum;			// 接受连接次数
//	u64 m_qwAcceptSucNum;		// 接受成功次数
//	u64 m_qwAcceptFailNum;		// 接受失败次数
//	int m_iAcceptFailCode;		// 接受失败码次数
//	u64 m_qwCloseSockNum;		// 关闭socket次数
//
//	u64 m_qwRcvMsgNum;			// 接收数据数
//	u64 m_qwRcvUserMsgNum;		// 接收用户消息次数
//	u64 m_qwRcvSRRNum;			// 接受SRR连接次数
//	u64 m_qwRcvLabelNum;		// 接收Label数
//	u64 m_qwRcvFileStartNum;	// 接收文件开始数
//	u64 m_qwRcvFileGetNum;		// 接收获取文件数
//	u64 m_qwRcvCloseChnlNum;	// 接收关闭通道数
//
//	u64 m_qwRcvNum;				// 接收数据数
//	u64 m_qwRcvSucNum;			// 接收数据成功数
//	u64 m_qwRcvFailNum;			// 接收数据失败数
//
//	u64 m_qwRcvHeadNum;				// 接收数据头数
//	u64 m_qwRcvHeadSucNum;			// 接收数据头成功数
//	u64 m_qwRcvHeadFailNum;			// 接收数据头失败数
//
//	u64 m_qwRcvBodyNum;				// 接收数据体数
//	u64 m_qwRcvBodySucNum;			// 接收数据体成功数
//	u64 m_qwRcvBodyFailNum;			// 接收数据体失败数
//
//	u64 m_qwSndMsgNum;					// 发送数据次数
//	u64 m_qwSndUserMsgNum;				// 发送用户消息次数
//	u64 m_qwSndSRRNum;					// 发送SRR连接次数
//	u64 m_qwSndLabelNum;				// 发送Label数
//	u64 m_qwSndFileStartNum;			// 发送文件开始数
//	u64 m_qwSndFileGetNum;				// 发送获取文件数
//	u64 m_qwSndCloseChnlNum;			// 发送关闭通道数
//
//	u64 m_qwSndHeadNum;					// 发送数据头次数
//	u64 m_qwSndHeadSucNum;				// 发送数据头成功次数
//	u64 m_qwSndHeadTryAgainNum;			// 发送数据头尝试次数
//	u64 m_qwSndHeadFailNum;				// 发送数据头失败次数
//
//	u64 m_qwSndBodyNum;					// 发送数据体次数
//	u64 m_qwSndBodySucNum;				// 发送数据体成功次数
//	u64 m_qwSndBodyTryAgainNum;			// 发送数据体尝试次数
//	u64 m_qwSndBodyFailNum;				// 发送数据体失败次数
//
//	u64 m_qwListSndNum;				//发送数据列表数
//	u64 m_qwListSndSucNum;			//发送数据列表成功数
//	u64 m_qwListSndTryAgainNum;		//发送数据列表尝试次数
//	u64 m_qwListSndFailNum;			//发送数据列表失败数
//
//	u64 m_qwSndFileNum;				// 发送文件数
//	u64 m_qwListSndFileNum;			// 发送文件列表节点数
//	u64 m_qwSndFileSucNum;			// 发送成功文件数
//	u64 m_qwSndFileFailNum;			// 发送失败文件数
//
//	u64 m_qwRcvFileNum;				// 发送文件数
//	u64 m_qwRcvFileSucNum;			// 发送成功文件数
//	u64 m_qwRcvFileFailNum;			// 发送失败文件数
//
//	u64 m_qwDataCheckUpFail;		//消息数据检查失败
//	u64 m_qwDataCheckUpSuc;			//消息数据检查成功
//
//	u64 m_qwConnectCBNum;		//回调连接事件
//	u64 m_qwDisConnectCBNum;		//回调断链事件
//	u64 m_qwRcvDataCBNum;		//回调数据接收事件
//	u64 m_qwUdpRcvDataCBNum;		//回调Udp数据接收事件
//	u64 m_qwFileDataCBNum;		//回调数据接收事件
//
//}TFtpLibServer;
//
////数据头 
//typedef struct tFtpLibMsgHeader
//{
//	u8 m_chFirstFlag;			//第一位标识
//	u8 m_chSecondFlag;			//第二位标识
//	u8 m_chVersion;				//版本号
//	u8 m_chSequence;			//序号
//
//	u32 m_dwMsgType;			//类型
//	u32 m_dwDataBodyLen;		//消息长度
//	u32 m_dwHeadCheck;			//消息头检查位
//}TFtpLibMsgHeader;
//
////发送数据信息
//typedef struct tFtpLibSndDataNode
//{
//	u32 m_dwDataType;		//数据类型
//	u32 m_dwDataLen;		//数据长度
//	u32 m_dwSndedLen;		//已发送数据
//	u8* m_pchDataBuf;
//
//	//发送文件数据
//	FILE* m_dwFileFd;			//文件句柄
//	char m_achTransFilePath[FTPLIB_FILEDIR_LEN + FTPLIB_FILENAME_LEN];		//文件目录
//	char m_achTransFileName[FTPLIB_FILENAME_LEN];	//文件名
//	char m_achSaveFileName[FTPLIB_FILENAME_LEN];		//保存文件名
//	u64 m_qwFileLen;			//文件长度
//	u64 m_qwSeekLen;			//偏移长度
//	u32 m_dwProPrecision;				//进度精度
//
//	struct tFtpLibSndDataNode* ptNextNode;
//
//}TFtpLibSndDataNode;




//初始化参数数据结构
typedef struct tLibFtpInitPara
{
	u32 m_dwAllChnlMaxNum;					//所有通道最大数，包括TCP，UDP两种协议要用到的通道
	u32 m_dwSvrNum;							//服务容量
	u32 m_dwCltNum;							//客户端通道容量
	u32 m_dwSingleRRCltNum;					//单次客户端通道容量
	u32 m_dwRcvThreadNum;					//接收线程数
	u32 m_dwSndThreadNum;					//发送线程数

	u16 m_wRcvRousePort;					//接收线程唤醒使用端口,默认9050,内部使用
	u16 m_wSndRousePort;					//发送线程唤醒使用端口，默认9051，内部使用

	u32 m_dwMaxLocalMsgLen;					//本地消息最大长度，单位字节，默认1k

	u32 m_dwSRRCheckTimerSec;				//SRR回收定时器，检查周期，默认30秒

	LibFtpEventCB m_pHpComEventPrc;			//上报事件函数



}TLibFtpInitPara;


//文件事件数据结构
typedef struct tLibFtpEvtData
{
	u64 m_qwChnlId;					//通道Id

	s8* m_achIP;
	s8* m_achPort;
	s8* m_achUsername;
	s8* m_achPassword;
	s8* m_achSFtpPath;

	u64 m_qwFileLen;				//文件长度
	u32 m_dwFilePro;				//文件进度
}TLibFtpEvtData;

//文件传输信息
typedef struct tFtpLibTranFileInfo
{
	char m_achRcvFileDir[LIBFTP_FILEDIR_LEN];		//接收文件目录
	char m_achReadFileDir[LIBFTP_FILEDIR_LEN];	//读取文件目录
	//u32 m_dwRcvProPre;							//接收进度精度
	//u32 m_dwSndProPre;							//发送进度精度

	FILE* m_pTransFileFd;			//文件句柄

	u64 m_qwSndFileNum;			//发送文件总数
	u64 m_qwSndFileSucNum;			//发送文件成功数
	u64 m_qwSndFileFailNum;			//发送文件失败数
}TFtpLibTranFileInfo;



#endif