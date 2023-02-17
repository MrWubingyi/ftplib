#ifndef _H_FTPLIB_TOOL_
#define _H_FTPLIB_TOOL_
#pragma once
#include"LibFtpstdafx.h"



typedef void(*LibFtpPrintfCB)(IN const char* file, IN u32 line, IN const char* StrFunc, char* szLog);  //JT809协议栈打印回调函数


//log日志等级
typedef enum tagUpaLibFtpLogLeave
{
	//JT809PRO_LOG_CLOSE = 0,    //关闭日志
	LIBFTP_LOG_DEBUG,        //Debug等级日志
	LIBFTP_LOG_ERR,          //错误等级日志
	LIBFTP_LOG_NOTICE,       //通知等级日志
	LIBFTP_LOG_MSG,          //消息打印
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