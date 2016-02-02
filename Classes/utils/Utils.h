#ifndef _UTILS_H_
#define _UTILS_H_

#include "CocosHead.h"

extern vector<string> string_spilt(const string& src,const string& split);

extern vector<string> string_spilt(const string& src, const char& split);

extern string string_trim(const string& str);

extern string string_replace(const string& str, const string& src, const string& dest);

extern bool isUTF_BOM(const string& content);






#endif