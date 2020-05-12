//
// Created by root on 20-4-26.
//
#include"change.h"

int UTF8_to_GB2312(char* inbuf, size_t* inlen, char* outbuf, size_t* outlen)
{
    int i = 0;
    char* To = "GB2312";//目的编码方式
    char* From = "UTF-8";//源编码方式
    iconv_t cd = iconv_open(To, From);
    if (cd == (iconv_t)-1)
    {
        perror("iconv_open");
    }
    char* inaddr = inbuf;
    char* outaddr = outbuf;
    size_t outsize = *outlen;
    size_t ret = iconv(cd, &inaddr, inlen, &outaddr, outlen);
    if (ret == -1)
    {
        perror("iconv");
        return 0;
    }
    /* 关闭句柄 */
    iconv_close(cd);
    return 1;
}

int UTF8_to_UNICODE(char* inbuf, size_t* inlen, char* outbuf, size_t* outlen)
{
    int i = 0;
    char* To = "UNICODE";
    char* From = "UTF-8";
    iconv_t cd = iconv_open(To, From);
    if (cd == (iconv_t)-1)
    {
        perror("iconv_open");
    }
    char* inaddr = inbuf;
    char* outaddr = outbuf;
    size_t outsize = *outlen;
    size_t ret = iconv(cd, &inaddr, inlen, &outaddr, outlen);
    if (ret == -1)
    {
        perror("iconv");
        return 0;
    }
    /* 关闭句柄 */
    iconv_close(cd);
    return 1;
}

int UTF8_to_GBK(char* inbuf, size_t* inlen, char* outbuf, size_t* outlen)
{
    int i = 0;
    char* To = "GBK";
    char* From = "UTF-8";
    iconv_t cd = iconv_open(To, From);
    if (cd == (iconv_t)-1)
    {
        perror("iconv_open");
    }
    char* inaddr = inbuf;
    char* outaddr = outbuf;
    size_t outsize = *outlen;
    size_t ret = iconv(cd, &inaddr, inlen, &outaddr, outlen);
    if (ret == -1)
    {
        perror("iconv");
        return 0;
    }
    /* 关闭句柄 */
    iconv_close(cd);
    return 1;
}

char dec_to_hex(short int c)
{
    if (0 <= c && c <= 9)
    {
        return c + '0';
    }
    else if (10 <= c && c <= 15)
    {
        return c + 'A' - 10;
    }
    else
    {
        return -1;
    }
}

int UTF8_to_URL(char* utf8)
{
    int i = 0;
    int UTF8_len = strlen(utf8);
    int URL_len = 0;
    char URL[1024];
    for (i = 0; i < UTF8_len; ++i)
    {
        char c = utf8[i];
        if (('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '/' || c == '.')
        {
            URL[URL_len++] = c;
        }
        else
        {
            int j = (short int)c;
            if (j < 0)
                j += 256;
            int i1, i0;
            i1 = j / 16;
            i0 = j - i1 * 16;
            URL[URL_len++] = '%';
            URL[URL_len++] = dec_to_hex(i1);
            URL[URL_len++] = dec_to_hex(i0);
        }
    }
    URL[URL_len] = '\0';
    strcpy(utf8, URL);
    return 1;
}


//int main()
//{
//	// 需要转换的字符串
//	char* text = "你";
//	char inbuf[1024] = {};
//	strcpy(inbuf, text);
//	size_t inlen = strlen(inbuf);
//
//	//存放转换后的字符串
//	char outbuf[1024] = {};
//	size_t outlen = 1024;
//
//	UTF8_to_GB2312(inbuf, &inlen, outbuf, &outlen);
//
//
//	size_t outsize = strlen(outbuf);
//	size_t insize = 1024;
//	char instr[1024] = {};
//
//	GB2312_to_UTF8(outbuf, &outsize, instr, &insize);
//
//	return 0;
//}

