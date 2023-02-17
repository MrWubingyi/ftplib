#ifndef _H_THREAD_LIST_
#define _H_THREAD_LIST_
#pragma once

#include"ftpstdafx.h"
//�߳����ݽṹ
typedef struct tFtpLibThread
{
	u32 m_dwThreadId;		//�߳�����
	u32 m_dwState;			//�߳�״̬

	BOOL m_bIsRcvThread;	//�Ƿ�Ϊ�����߳�
	BOOL m_bThreadIsStart;	//�߳��Ƿ�����

	u32 m_dwChnlHighLevel;		//��һ��
	u32 m_dwChnlLowLevel;		//��һ��

	u32 m_dwRouseCnt;		//���Ѵ���

}TFtpLibThread;

//�߳�״̬
typedef enum eFtpLibThreadState
{
	E_THREAD_STATE_FREE = 0,		//�߳̿��У�û�е���epollwait
	E_THREAD_STATE_RUNING ,			//��������

	E_THREAD_STATE_RCVWAITE ,		//���ڽ������ݣ�����epollwait
	E_THREAD_STATE_RCVING ,			//���ڽ������ݣ�epollwait���������ڽ�������
	E_THREAD_STATE_RCVBLOCK ,		//���ڽ������ݣ��ڽ�������ʱ����

	E_THREAD_STATE_SNDWAITE ,		//���ڽ������ݣ�����epollwait
	E_THREAD_STATE_SNDING ,			//���ڽ������ݣ�epollwait���������ڽ�������
	E_THREAD_STATE_SNDBLOCK ,		//���ڽ������ݣ��ڽ�������ʱ����
}EFtpLibThreadState;

TFtpLibThread *g_ptFtpLib_RcvThreadList ;	//�����߳�
TFtpLibThread *g_ptFtpLib_SndThreadList ;	//�����߳�


/************************************************************************
��������ThreadListInit
���ܣ�	�߳��б��ʼ��
������
����ֵ���ɹ�����0��	ʧ�ܡ�������
************************************************************************/
u32 ThreadListInit();

/************************************************************************
��������ThreadListUnInit
���ܣ�	�߳��б���ʼ��
������
����ֵ���ɹ�����0��	ʧ�ܡ�������
************************************************************************/
u32 ThreadListUnInit();

/************************************************************************
��������ThreadListEpollThreadCreat
���ܣ�	�����߳�
������
����ֵ���ɹ�����0��	ʧ�ܡ�������
************************************************************************/
u32 ThreadListEpollThreadCreat();
#endif