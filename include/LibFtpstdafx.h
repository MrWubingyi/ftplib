#ifndef _H_FTPSTDAFX_
#define _H_FTPSTDAFX_

#pragma warning (disable: 4996)

#pragma once


#define FTP_WIN32 1
#ifdef FTP_WIN32
#define FD_SETSIZE 1024                  //socket句柄数
//#define MAXIMUM_WAIT_OBJECTS    1024     //要等待的对象数
#endif

#ifndef FTP_WIN32
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif


#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <math.h>
#include <fcntl.h>

#include "00basictype/uvbasetype.h"
#include "00basictype/uverr.h"
#include "05apptype/vssdefine.h"
#include "10os/oal.h"
#include "10os/otl.h"
#include "05apptype/vsscomm.h"
#include "05apptype/vsstypes.h"
#include "20dataengine/uvtinyxml.h"

#ifdef FTP_WIN32

#include <mswsock.h>
#include <Windows.h>
#include <MMSystem.h>
#include <WinSock2.h>
#include <winapifamily.h>
#include <ctype.h>
#include <ws2tcpip.h>

//libssh支持库
#pragma comment(lib,"Crypt32.lib")
#pragma comment(lib,"ws2_32.lib")


#pragma comment(lib,"../libs/openssl/Lib/x64/Debug/lib/libcrypto.lib")
#pragma comment(lib,"../libs/openssl/Lib/x64/Debug/lib/libssl.lib")
#pragma comment(lib,"../libs/openssl/Lib/x64/Debug/lib/ssleay32.lib")
#pragma comment(lib,"../libs/openssl/Lib/x64/Debug/lib/libeay32.lib")
#pragma comment(lib,"../libs/openssl/Lib/openssl.lib")
#pragma comment(lib,"../libs/libssh2/lib/Debug/libssh2.lib")


#include"../libs/libssh2/include/libssh2.h"
#include"../libs/libssh2/include/libssh2_publickey.h"
#include"../libs/libssh2/include/libssh2_sftp.h"



//ftplib工程头文件
#include"LibFtp.h"
#include "LibFtp_sshpro.h"
#include "LibFtp_tool.h"
#include <LibFtp_RouseSock_thread.h>

#ifdef _WIN32
#define libftplog(logLeave, fmp,...) LibFtpRegPintfCB(LOGCODEPOS, logLeave, fmp, __VA_ARGS__)
#else
#define libftploglog(logLeave, fmp, arg...) LibFtpRegPintfCB(LOGCODEPOS, logLeave, fmp,##arg)
#endif



#ifndef MAXIMUM_WAIT_OBJECTS
#define MAXIMUM_WAIT_OBJECTS    1024     //要等待的对象数
#endif
#else
#include "unistd.h"
#include <sys/epoll.h>
#include "io_socket_linux.h"
#endif

#endif



