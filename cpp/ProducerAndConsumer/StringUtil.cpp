#include "StringUtil.h"

using namespace std;

wstring string2wstring(string str) {
    wstring wstr(str.begin(), str.end());
    return  wstr;
}