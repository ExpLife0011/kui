// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "iconv.h"


//����ת��:��һ�ֱ���תΪ��һ�ֱ���
int code_convert(char *from_charset, char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	iconv_t cd;
	const char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset, from_charset);
	if (cd == 0) 
		return -1;
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, &inlen, pout, &outlen) == -1)
		return -1;
	iconv_close(cd);
	return 0;
}
//UNICODE��תΪGB2312��
int u2g(const char *inbuf, int inlen, char *outbuf, int outlen)
{
	return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}
//GB2312��תΪUNICODE��
int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen)
{
	return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}
#define  OUTLEN 1024
int _tmain(int argc, _TCHAR* argv[])
{
	char *in_utf8 = "正在安装";
	char *in_gb2312 = "���ڰ�װ";
	char out[OUTLEN] = { 0 };

	int rc = 0;
	//unicode��תΪgb2312��
	rc = u2g(in_utf8, (int)strlen(in_utf8), out, OUTLEN);
	printf("utf-8-->gb2312 out=%s\n", out);
	//gb2312��תΪunicode��
	rc = g2u(in_gb2312, (int)strlen(in_gb2312), out, OUTLEN);
	printf("gb2312-->utf-8 out=%s\n", out);
	system("pause");
	return 0;
}
