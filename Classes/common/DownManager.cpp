/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "DownManager.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <vector>
#include <thread>

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#endif

#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "base/CCUserDefault.h"
#include "platform/CCFileUtils.h"

#include "unzip.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d;
using namespace std;
using namespace cocostudio;

#define LOW_SPEED_LIMIT 1L
#define LOW_SPEED_TIME 5L
#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

DownManager::DownManager() :
_curl(nullptr),
_ErrorCallback(nullptr),
_StateCallback(nullptr),
_SuccessCallback(nullptr),
_ProgressCallback(nullptr),
_downUrl("http ://127.0.0.1"),
_stateCode(StateCode::NORMAL),
_connectionTimeout(5),
_downindex(0),
_maxDownNum(0)
{
	loadConfig();
}

DownManager::~DownManager()
{

}

void DownManager::setStateCallback(const StateCallback& func)
{
	this->_StateCallback = func;
}

void DownManager::setErrorCallback(const ErrorCallback& func)
{
	this->_ErrorCallback = func;
}

void DownManager::setProgressCallback(const ProgressCallback& func)
{
	this->_ProgressCallback = func;
}

void DownManager::setSuccessCallback(const SuccessCallback& func)
{
	this->_SuccessCallback = func;
}

static size_t setGameData(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	string *version = (string*)userdata;
	version->append((char*)ptr, size * nmemb);

	return (size * nmemb);
}

bool DownManager::checkUpdate()
{
	_curl = curl_easy_init();
	if (!_curl)
	{
		CCLOG("can not init curl");
		return false;
	}

	string versionFileUrl = _downUrl + "/gamedata.plist";
	_gameDataPlist = "";

	CURLcode res;
	curl_easy_setopt(_curl, CURLOPT_URL, versionFileUrl.c_str());
	curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, setGameData);
	curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_gameDataPlist);
	if (_connectionTimeout) curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, _connectionTimeout);
	curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_LIMIT, LOW_SPEED_LIMIT);
	curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_TIME, LOW_SPEED_TIME);
	curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1);
	res = curl_easy_perform(_curl);

	if (res != 0)
	{
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
			if (this->_ErrorCallback)
				this->_ErrorCallback((int)(ErrorCode::NETWORK));
		});
		CCLOG("can not get version file content, error code is %d", res);
		curl_easy_cleanup(_curl);
		return false;
	}
	_difPackageData.clear();
	// 创建文件信息
	_newPackageData = PackageData::createWithString(_gameDataPlist);
	// 比较文件
	_difPackageData = _localPackageData.compare(_newPackageData);
	if (_difPackageData.empty())
	{
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
			if (this->_SuccessCallback)
				this->_SuccessCallback((int)SuccessCode::UPDATESUCCESS);
		});
		return false;
	}
	
	CCLOG("there is a new version");

	return true;
}


void DownManager::update()
{
	_stateCode = StateCode::NORMAL;
	if (checkUpdate() == false)
	{
		return;
	}

	auto t = std::thread(&DownManager::downloadAndUncompress, this);
	t.detach();
}

void DownManager::loadConfig()
{
	_downDir = FileUtils::getInstance()->getWritablePath() + "down";
	createDepthDir(_downDir);
	_resourceDir = FileUtils::getInstance()->getWritablePath() + "res";
	createDepthDir(_resourceDir);
	FileUtils::getInstance()->addSearchPath(_resourceDir,true);

	ValueMap filemap = FileUtils::getInstance()->getValueMapFromFile("config/defconfig.xml");

	auto it = filemap.find("version");
	if (it != filemap.end())
	{
		_version = it->second.asString();
	}

	it = filemap.find("downurl");
	if (it != filemap.end())
	{
		_downUrl = it->second.asString();
	}

	_downUrl += "/" + _version;
	_localPackageData = PackageData("config/gamedata.xml");
}

void DownManager::downloadAndUncompress()
{
	_maxDownNum = _difPackageData.size();
	for (_downindex = 0; _downindex < _maxDownNum; ++_downindex)
	{
		string packageId = _difPackageData[_downindex].id + ".zip";
		string packageUrl = _difPackageData[_downindex].url; 
		string uncompressDir = _difPackageData[_downindex].dir;

		// 开始下载
		_stateCode = StateCode::DOWNLOADER;
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
			if (_StateCallback)
			{
				this->_StateCallback((int)_stateCode);
			}
			
		});

		if (!downLoad(packageUrl, packageId)) break;

		// 开始解压
		_stateCode = StateCode::UNCOMPRESS;
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
			if (_StateCallback)
			{
				this->_StateCallback((int)_stateCode);
			}

		});

		if (!uncompress(packageId, uncompressDir))
		{
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
				if (this->_ErrorCallback)
					this->_ErrorCallback((int)ErrorCode::UNCOMPRESS);
			});
			break;
		}

		// 删除临时文件
		string zipfileName = this->_downDir + "/" +  packageId;
		if (remove(zipfileName.c_str()) != 0)
		{
			CCLOG("can not remove downloaded zip file %s", zipfileName.c_str());
		}
	}

	ValueMap plist = FileUtils::getInstance()->getValueMapFromData(_gameDataPlist.c_str(), _gameDataPlist.length());
	FileUtils::getInstance()->writeToFile(plist, _resourceDir + "/config/gamedata.xml");

	_stateCode = StateCode::NORMAL;
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this] {

		if (this->_SuccessCallback)
			this->_SuccessCallback((int)SuccessCode::UPDATESUCCESS);
	});
}

static size_t downLoadPackage(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	FILE *fp = (FILE*)userdata;
	size_t written = fwrite(ptr, size, nmemb, fp);
	return written;
}

int downManagerProgressFunc(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
	static int percent = 0;
	int tmp = (int)(nowDownloaded / totalToDownload * 100);

	if (percent != tmp)
	{
		percent = tmp;
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
			auto manager = static_cast<DownManager*>(ptr);
			if (manager->_ProgressCallback)
				manager->_ProgressCallback(percent);
			CCLOG("downloading... %d", percent);
		});
	}

	return 0;
}
bool DownManager::downLoad(const string& url, const string& name)
{
	const string outFileName = _downDir + "/" + name;
	const string downUrl = _downUrl + "/" + url;
	FILE *fp = fopen(outFileName.c_str(), "wb");
	if (!fp)
	{
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
			if (this->_ErrorCallback)
				this->_ErrorCallback((int)ErrorCode::CREATE_FILE);
		});
		CCLOG("can not create file %s", outFileName.c_str());
		return false;
	}
	if (!_curl)
	{
		_curl = curl_easy_init();
	}
	// Download pacakge
	CURLcode res;
	curl_easy_setopt(_curl, CURLOPT_URL, downUrl.c_str());
	curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, downLoadPackage);
	curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
	curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, downManagerProgressFunc);
	curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, this);
	curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_LIMIT, LOW_SPEED_LIMIT);
	curl_easy_setopt(_curl, CURLOPT_LOW_SPEED_TIME, LOW_SPEED_TIME);
	curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1);

	res = curl_easy_perform(_curl);
	curl_easy_cleanup(_curl);
	_curl = NULL;
	if (res != 0)
	{
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([&, this]{
			if (this->_ErrorCallback)
				this->_ErrorCallback((int)ErrorCode::NETWORK);
		});
		CCLOG("error when download package");
		fclose(fp);
		return false;
	}

	CCLOG("succeed downloading package %s", outFileName.c_str());

	fclose(fp);
	return true;
}

bool DownManager::uncompress(const string& name, const string& dir)
{
	// Open the zip file
	string outFileName = _downDir + "/" +  name;
	unzFile zipfile = unzOpen(outFileName.c_str());
	if (!zipfile)
	{
		CCLOG("can not open downloaded zip file %s", outFileName.c_str());
		return false;
	}

	// Get info about the zip file
	unz_global_info global_info;
	if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
		CCLOG("can not read file global info of %s", outFileName.c_str());
		unzClose(zipfile);
		return false;
	}

	// Buffer to hold data read from the zip file
	char readBuffer[BUFFER_SIZE];

	CCLOG("start uncompressing");

	// Loop to extract all files.
	uLong i;
	for (i = 0; i < global_info.number_entry; ++i)
	{
		// Get info about current file.
		unz_file_info fileInfo;
		char fileName[MAX_FILENAME];
		if (unzGetCurrentFileInfo(zipfile,
			&fileInfo,
			fileName,
			MAX_FILENAME,
			nullptr,
			0,
			nullptr,
			0) != UNZ_OK)
		{
			CCLOG("can not read file info");
			unzClose(zipfile);
			return false;
		}

		const string fullPath = _resourceDir + "/" + dir;
		if (createDepthDir(fullPath) == true)
		{
			// Open current file.
			if (unzOpenCurrentFile(zipfile) != UNZ_OK)
			{
				CCLOG("can not open file %s", fileName);
				unzClose(zipfile);
				return false;
			}
			string fullName = fullPath + "/" + fileName;
			// Create a file to store current file.
			FILE *out = fopen(fullName.c_str(), "wb");
			if (!out)
			{
				CCLOG("can not open destination file %s", fullName.c_str());
				unzCloseCurrentFile(zipfile);
				unzClose(zipfile);
				return false;
			}

			// Write current file content to destinate file.
			int error = UNZ_OK;
			do
			{
				error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
				if (error < 0)
				{
					CCLOG("can not read zip file %s, error code is %d", fileName, error);
					unzCloseCurrentFile(zipfile);
					unzClose(zipfile);
					return false;
				}

				if (error > 0)
				{
					fwrite(readBuffer, error, 1, out);
				}
			} while (error > 0);

			fclose(out);
		}

		unzCloseCurrentFile(zipfile);

		// Goto next entry listed in the zip file.
		if ((i + 1) < global_info.number_entry)
		{
			if (unzGoToNextFile(zipfile) != UNZ_OK)
			{
				CCLOG("can not read next file");
				unzClose(zipfile);
				return false;
			}
		}
	}

	CCLOG("end uncompressing");
	unzClose(zipfile);

	return true;
}


bool DownManager::createDir(const string& dir)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)

	mode_t processMask = umask(0);
	int ret = mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	umask(processMask);
	if (ret != 0 && (errno != EEXIST))
	{
		return false;
	}
	return true;
#else
	if ((GetFileAttributesA(dir.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		BOOL ret = CreateDirectoryA(dir.c_str(), nullptr);
		if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
		{
			return false;
		}
		return true;
	}
	return true;
#endif
}

bool DownManager::createDepthDir(const string& dir)
{
	string dirstr = string(dir.c_str());
	if (dirstr[dirstr.size() - 1] != '/')
	{
		dirstr += "/";
	}
	
	for (int i = 0; i < dirstr.size(); ++i)
	{
		if (dirstr[i] == '/')
		{
			dirstr[i] = '\0';
			if (dirstr == "")
			{
				dirstr[i] = '/';
				continue;
			}
			else
			{
				bool res = createDir(dirstr);
				dirstr[i] = '/';
				if (res == false) return false;
			}
		}
	}
	return true;
}

int DownManager::getDownIndex()
{
	return _downindex;
}

int DownManager::getMaxDownNum()
{
	return _maxDownNum;
}




