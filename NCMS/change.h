//
// Created by root on 20-4-26.
//

#ifndef IPTEST_CHANGE_H
#define IPTEST_CHANGE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iconv.h>

int UTF8_to_GB2312(char* inbuf, size_t* inlen, char* outbuf, size_t* outlen);

int UTF8_to_UNICODE(char* inbuf, size_t* inlen, char* outbuf, size_t* outlen);

int UTF8_to_GBK(char* inbuf, size_t* inlen, char* outbuf, size_t* outlen);

int UTF8_to_URL(char* url);



#endif //IPTEST_CHANGE_H
