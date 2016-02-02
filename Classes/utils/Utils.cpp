#include "Utils.h"

vector<string> string_spilt(const string& src, const string& split)
{
	vector<string> strs;
	string::size_type pos = 0, last_pos = 0;
	while ((pos = src.find(split,last_pos)) != string::npos)
	{
		strs.push_back(src.substr(last_pos, pos - last_pos));
		last_pos = pos + split.size();
	}
	if (last_pos < src.size())
	{
		strs.push_back(src.substr(last_pos));
	}
	return strs;
}

vector<string> string_spilt(const string& src, const char& split)
{
	vector<string> strs;
	string::size_type pos = 0, last_pos = 0;
	while ((pos = src.find(split, last_pos)) != string::npos)
	{
		strs.push_back(src.substr(last_pos, pos - last_pos));
		last_pos = pos + 1;
	}
	if (last_pos < src.size())
	{
		strs.push_back(src.substr(last_pos));
	}
	return strs;
}

extern bool isUTF_BOM(const string& content)
{
	if (content.size() < 3)
	{
		return false;
	}
	if ((uint8_t)content[0] == 0xEF && (uint8_t)content[1] == 0xBB && (uint8_t)content[2] == 0xBF)
	{
		return true;
	}
	return false;
}


string string_trim(const string& str)
{
	string::size_type pos = str.find_first_not_of(' ');
	if (pos == string::npos)
	{
		return str;
	}
	string::size_type pos2 = str.find_last_not_of(' ');
	if (pos2 != string::npos)
	{
		return str.substr(pos, pos2 - pos + 1);
	}
	return str.substr(pos);
}

string string_replace(const string& str, const string& src, const string& dest)
{
	string ret;
	string::size_type pos_begin = 0;
	string::size_type pos = str.find(src);
	while (pos != string::npos)
	{
		ret.append(str.data() + pos_begin, pos - pos_begin);
		ret += dest;
		pos_begin = pos + 1;
		pos = str.find(src, pos_begin);
	}
	if (pos_begin < str.length())
	{
		ret.append(str.begin() + pos_begin, str.end());
	}
	return ret;
}