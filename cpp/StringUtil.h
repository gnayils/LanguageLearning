#ifndef STRINGUTIL_H
#define	STRINGUTIL_H

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define LOG(msg, args...) {\
    char logChars[128];\
    memset(logChars, 0, sizeof(logChars));\
    sprintf(logChars, msg, ##args);\
    string logString(logChars);\
    cout << logString;\
}\

#define WLOG(msg, ...) {\
    int logCharsLength = 128;\
    wchar_t logChars[logCharsLength];\
    memset(logChars, 0, logCharsLength * sizeof(wchar_t));\
    swprintf(logChars, logCharsLength, msg, ##__VA_ARGS__);\
    wstring logString(logChars);\
    wcout << logString;\
}\

wstring string2wstring(string str);

#endif