#ifndef _H_FTPLIB_SSHPRO_
#define _H_FTPLIB_SSHPRO_
#pragma once
#include"LibFtpstdafx.h"

/*
* ssh-2.0Э��ģ��
* ���̣�
* һ���汾Э��
* �����㷨Э������Կ����
* ��������ͨ�ţ����ܺ���2��3���֣�
* ����������������������������������������������������������������
* ���ݰ���
* |�����ȣ�Packet Length��| ��䳤����Padding Length��| ��Ϣ���루Msg code��| ��Ϣ���� | ���ֵ��Padding String�� 
��5�������
��������������������������������
*/
/* �㷨Э��:���壨��Ϣ���ݣ���
*       cookie(�����ֵ��16byte)
        kex_algorithms����Կ�⽻���㷨��
        server_host_key_algorithms��������������Կ����������ô������������Բ��ã�
        encryption_algorithms_client_to_server������ͨ��ʹ�õļ����㷨��
        encryption_algorithms_server_to_client
        mac_algorithms_client_to_server������У���õ�hash�㷨��
        mac_algorithms_server_to_client
        compression_algorithms_client_to_server��ѹ���㷨��
        compression_algorithms_server_to_client
        languages_client_to_server
        languages_server_to_client
        first_kex_packet_follows
        0��4byte��������չ�õģ�
 *����
        Packet Length: 1276
        Padding Length: 10
        Key Exchange
            Message Code: Key Exchange Init (20)
            Algorithms
                Cookie: 4917292a3d532b274cd608e8ba002133
                kex_algorithms length: 320
                kex_algorithms string [truncated]: curve25519-sha256,curve25519-sha256@libssh.org,ecdh-sha2-nistp256,ecdh-sha2-nistp384,ecdh-sha2-nistp521,diffie-hellman-group-exchange-sha256,diffie-hellman-group16-sha512,diffie-hellman-group18-sha512,dif
                server_host_key_algorithms length: 65
                server_host_key_algorithms string: ssh-rsa,rsa-sha2-512,rsa-sha2-256,ecdsa-sha2-nistp256,ssh-ed25519
                encryption_algorithms_client_to_server length: 175
                encryption_algorithms_client_to_server string: chacha20-poly1305@openssh.com,aes128-ctr,aes192-ctr,aes256-ctr,aes128-gcm@openssh.com,aes256-gcm@openssh.com,aes128-cbc,aes192-cbc,aes256-cbc,blowfish-cbc,cast128-cbc,3des-cbc
                encryption_algorithms_server_to_client length: 175
                encryption_algorithms_server_to_client string: chacha20-poly1305@openssh.com,aes128-ctr,aes192-ctr,aes256-ctr,aes128-gcm@openssh.com,aes256-gcm@openssh.com,aes128-cbc,aes192-cbc,aes256-cbc,blowfish-cbc,cast128-cbc,3des-cbc
                mac_algorithms_client_to_server length: 213
                mac_algorithms_client_to_server string [truncated]: umac-64-etm@openssh.com,umac-128-etm@openssh.com,hmac-sha2-256-etm@openssh.com,hmac-sha2-512-etm@openssh.com,hmac-sha1-etm@openssh.com,umac-64@openssh.com,umac-128@openssh.com,hmac-sha2-2
                mac_algorithms_server_to_client length: 213
                mac_algorithms_server_to_client string [truncated]: umac-64-etm@openssh.com,umac-128-etm@openssh.com,hmac-sha2-256-etm@openssh.com,hmac-sha2-512-etm@openssh.com,hmac-sha1-etm@openssh.com,umac-64@openssh.com,umac-128@openssh.com,hmac-sha2-2
                compression_algorithms_client_to_server length: 21
                compression_algorithms_client_to_server string: none,zlib@openssh.com
                compression_algorithms_server_to_client length: 21
                compression_algorithms_server_to_client string: none,zlib@openssh.com
                languages_client_to_server length: 0
                languages_client_to_server string: [Empty]
                languages_server_to_client length: 0
                languages_server_to_client string: [Empty]
                KEX First Packet Follows: 0
                Reserved: 00000000
            Padding String: 00000000000000000000   
��������������������������������
*/

#define KEI   (char) 20
#define NK      (char) 21
//SSH�㷨��
#define VER "SSH-2.0-DSFTP_1.0\r\n"
#define COOKIE "0123456789ABCDEF"//  cookie(�����ֵ��16byte)
#define VKEX "diffie-hellman-group-exchange-sha256"
#define VSHK "ssh-rsa"
#define VECS "aes128-cbc"
#define VESC "aes128-cbc"
#define VMCS "hmac-sha1"
#define VMSC "hmac-sha1"
#define VCCS "none"
#define VCSC "none"
#define VLCS ""
#define VLSC ""
#define KFPF ""


typedef struct tKeyExData
{
    struct tsshhead* ptsshhead;
    char cookie[16];
    u32 kex_algorithms_len;
    char* kex_algorithms;
    u32   server_host_key_algorithms_len;
    char* server_host_key_algorithms;
    u32  encryption_algorithms_client_to_server_len;
    char* encryption_algorithms_client_to_server;
    u32   encryption_algorithms_server_to_client_len;
    char* encryption_algorithms_server_to_client;
    u32   mac_algorithms_client_to_server_len;
    char* mac_algorithms_client_to_server;
    u32    mac_algorithms_server_to_client_len;
    char* mac_algorithms_server_to_client;
    u32 compression_algorithms_client_to_server_len;
    char* compression_algorithms_client_to_server;
    u32 compression_algorithms_server_to_client_len;
    char* compression_algorithms_server_to_client;
    u32  languages_client_to_server_len;
    char* languages_client_to_server;
    u32  languages_server_to_client_len;
    char* languages_server_to_client;
    u32  first_kex_packet_follows;
    u64 Reserved;
}TKeyExData;

typedef struct tsshhead//ssh���ݰ�ͷ                                          //struct sshhead
{
    u32 PcaketLen;//�����ȣ�Packet Length��                               //    unsigned int tlen;
    u8 PaddingLen; //��䳤����Padding Length)							//    unsigned char plen;
    u8 msgcode; //��Ϣ���루Msg code��							//    unsigned char msgcode;
    struct  tsshhead* ptsshhead;//�����ȣ�Packet Length��=6		//    sshhead() { tlen = 6; }
}TSshhead;






#endif