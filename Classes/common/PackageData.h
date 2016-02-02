#ifndef __PACKAGEDATA_H__
#define __PACKAGEDATA_H__

#include "CocosHead.h"

// 更新zip包信息
struct PackageInfo
{
	PackageInfo(const ValueMap& info);
	bool Compare(const PackageInfo& info);


	std::string id;
	std::string url;
	std::string md5;
	std::string contentmd5;
	std::string dir;
	int			size;
};

// 总包信息

class PackageData
{
public:

	PackageData();

	PackageData(const string& file);

	~PackageData();

	static PackageData createWithString(const string& contentStr);

	map<string, PackageInfo> getPackInfoList();

	vector<PackageInfo> compare(PackageData& data);

private:

	string _version;

	map<string ,PackageInfo> _packageList;

};






#endif