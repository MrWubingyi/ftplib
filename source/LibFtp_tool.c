#include"LibFtp_tool.h"

LibFtpPrintfCB            g_cbLibFtpPrintf = NULL;   //Э��ջ��ӡ�ص�����ָ��
/************************************************************************
��������ע����־�������
���ܣ�JT809Э��ջ���ڲ���־��Ϣͨ����ע��Ļص������������UPAģ�飬��UPAģ��ִ�д�ӡ
������
	cbFunc����ע��Ĵ�ӡ����ָ��
����ֵ��
************************************************************************/
void LibFtpRegPintfCB(LibFtpPrintfCB cbFunc)
{
	g_cbLibFtpPrintf = cbFunc; //ע��ص�����ָ��
}


/// <summary>
/// ��ӡ����
/// </summary>
void JT809ProSvcLog(const char* file, int line, const char* function, int level, const char* fmt, ...)
{
	va_list ap;

	char buff[1024] = { 0 };

	switch (level) {
	case LIBFTP_LOG_DEBUG:
		strcpy(buff, "[JT809-DEBUG]: ");
		break;
	case LIBFTP_LOG_NOTICE:
		strcpy(buff, "[JT809-NOTICE]: ");
		break;
	case LIBFTP_LOG_ERR:
		strcpy(buff, "[JT809-ERROR]: ");
		break;
	case LIBFTP_LOG_MSG:
		strcpy(buff, "[JT809-MSG]: ");
		break;
	default:
		strcpy(buff, "[JT809-unknown]: ");
	}

	va_start(ap, fmt);

	vsnprintf(buff + strlen(buff), sizeof(buff) - strlen(buff), fmt, ap);

	va_end(ap);

	// ��ӡ����
	if (g_cbLibFtpPrintf)
	{
		g_cbLibFtpPrintf(file, line, function, buff);
	}
	return;
}


/// <summary>
/// ��������ص�
/// </summary>
void static_kbd_callback(const char* name, int name_len,
	const char* instruction, int instruction_len,
	int num_prompts,
	const LIBSSH2_USERAUTH_KBDINT_PROMPT* prompts,
	LIBSSH2_USERAUTH_KBDINT_RESPONSE* responses,
	void** abstract)
{
	kbd_callback(name, name_len, instruction, instruction_len, num_prompts, prompts, responses, abstract);
}

/// <summary>
/// ��������ص�
/// </summary>
static void kbd_callback(const char* name, int name_len,
	const char* instruction, int instruction_len,
	int num_prompts,
	const LIBSSH2_USERAUTH_KBDINT_PROMPT* prompts,
	LIBSSH2_USERAUTH_KBDINT_RESPONSE* responses,
	void** abstract)
{
	int i;
	size_t n;
	char buf[1024];
	(void)abstract;

	fprintf(stderr, "Performing keyboard-interactive authentication.\n");

	fprintf(stderr, "Authentication name: '");
	fwrite(name, 1, name_len, stderr);
	fprintf(stderr, "'\n");

	fprintf(stderr, "Authentication instruction: '");
	fwrite(instruction, 1, instruction_len, stderr);
	fprintf(stderr, "'\n");

	fprintf(stderr, "Number of prompts: %d\n\n", num_prompts);

	for (i = 0; i < num_prompts; i++) {
		fprintf(stderr, "Prompt %d from server: '", i);
		fwrite(prompts[i].text, 1, prompts[i].length, stderr);
		fprintf(stderr, "'\n");

		fprintf(stderr, "Please type response: ");
		fgets(buf, sizeof(buf), stdin);
		n = strlen(buf);
		while (n > 0 && strchr("\r\n", buf[n - 1]))
			n--;
		buf[n] = 0;

		responses[i].text = strdup(buf);
		responses[i].length = n;

		fprintf(stderr, "Response %d from user is '", i);
		fwrite(responses[i].text, 1, responses[i].length, stderr);
		fprintf(stderr, "'\n\n");
	}

	fprintf(stderr,
		"Done. Sending keyboard-interactive responses to server now.\n");
}

//�����ַ�������
int length(char s[])
{
	int len = 0;
	while (s[len + 1] != '\0')
	{
		len++;
	}
	len++;
	return len;
}
//�ַ����滻
char str_replace(char* src, char from, char to, char dst[])
{

	char tmp[1024];
	strcpy(tmp, src);
	char  comma = ',';
	char  point = '.';
	int i = 0;
	int len = length(tmp);
	for (i = 0; i < len; i++)
	{
		if (tmp[i] == from)
		{
			tmp[i] = to;
		}
	}
	strcpy(dst, tmp);
	return dst;
}