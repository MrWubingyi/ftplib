#ifndef _H_FTPLIB_TOOL_
#define _H_FTPLIB_TOOL_
#pragma once
#include"LibFtpstdafx.h"



typedef void(*LibFtpPrintfCB)(IN const char* file, IN u32 line, IN const char* StrFunc, char* szLog);  //JT809Э��ջ��ӡ�ص�����


//log��־�ȼ�
typedef enum tagUpaLibFtpLogLeave
{
	//JT809PRO_LOG_CLOSE = 0,    //�ر���־
	LIBFTP_LOG_DEBUG,        //Debug�ȼ���־
	LIBFTP_LOG_ERR,          //����ȼ���־
	LIBFTP_LOG_NOTICE,       //֪ͨ�ȼ���־
	LIBFTP_LOG_MSG,          //��Ϣ��ӡ
}TUpaLibFtpLogLeave;


void static_kbd_callback(const char* name, int name_len,
	const char* instruction, int instruction_len,
	int num_prompts,
	const LIBSSH2_USERAUTH_KBDINT_PROMPT* prompts,
	LIBSSH2_USERAUTH_KBDINT_RESPONSE* responses,
	void** abstract);

static void kbd_callback(const char* name, int name_len,
	const char* instruction, int instruction_len,
	int num_prompts,
	const LIBSSH2_USERAUTH_KBDINT_PROMPT* prompts,
	LIBSSH2_USERAUTH_KBDINT_RESPONSE* responses,
	void** abstract);

char str_replace(char* src, char from, char to, char dst[]);
#endif