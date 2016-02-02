#include "PackageData.h"

PackageInfo::PackageInfo(const ValueMap& info)
{
	auto it_id = info.find("id");
	if (it_id != info.end())
	{
		id = it_id->second.asString();
	}
	auto it_url = info.find("url");
	if (it_url != info.end())
	{
		url = it_url->second.asString();
	}

	auto it_size = info.find("size");
	if (it_size != info.end())
	{
		size = it_size->second.asInt();
	}

	auto it_md5 = info.find("md5");
	if (it_md5 != info.end())
	{
		md5 = it_md5->second.asString();
	}

	auto it_contentmd5 = info.find("contentmd5");
	if (it_contentmd5 != info.end())
	{
		contentmd5 = it_contentmd5->second.asString();
	}

	auto it_dir = info.find("dir");
	if (it_dir != info.end())
	{
		dir = it_dir->second.asString();
	}
}

bool PackageInfo::Compare(const PackageInfo& info)
{
	if (info.md5 == this->md5 && info.contentmd5 == this->contentmd5)
	{
		return true;
	}

	return false;
}


PackageData::PackageData():
_version("")
{

}

PackageData::PackageData(const string& file)
{
	ValueMap filemap = FileUtils::getInstance()->getValueMapFromFile(file);

	auto it = filemap.find("version");
	if (it != filemap.end())
	{
		_version = it->second.asString();
	}

	it = filemap.find("packages");
	if (it != filemap.end())
	{
		ValueVector filearray = it->second.asValueVector();
		for (int i = 0; i < filearray.size(); ++i)
		{
			PackageInfo info = PackageInfo(filearray[i].asValueMap());
			_packageList.insert(make_pair(info.id,info));
		}
	}
}

PackageData::~PackageData()
{

}

vector<PackageInfo> PackageData::compare(PackageData& data)
{
	vector<PackageInfo> res;
	map<string, PackageInfo> newInfo = data.getPackInfoList();

	for (auto it = newInfo.begin(); it != newInfo.end(); ++it)
	{
		auto it_find = this->_packageList.find(it->first);
		if (it_find != this->_packageList.end())
		{
			if (it_find->second.Compare(it->second) == false)
			{
				res.push_back(it->second);
			}
		}
		else
		{
			res.push_back(it->second);
		}
	}

	return res;
}

map<string, PackageInfo> PackageData::getPackInfoList()
{
	return _packageList;
}

PackageData PackageData::createWithString(const string& contentStr)
{
	PackageData data;
	ValueMap filemap = FileUtils::getInstance()->getValueMapFromData(contentStr.c_str(), contentStr.length());

	auto it = filemap.find("version");
	if (it != filemap.end())
	{
		data._version = it->second.asString();
	}

	it = filemap.find("packages");
	if (it != filemap.end())
	{
		ValueVector filearray = it->second.asValueVector();
		for (int i = 0; i < filearray.size(); ++i)
		{
			PackageInfo info = PackageInfo(filearray[i].asValueMap());
			data._packageList.insert(make_pair(info.id, info));
		}
	}
	return data;
}


