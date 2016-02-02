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

#ifndef __DownManager__
#define __DownManager__

#include <string>

#include <mutex>

#include "2d/CCNode.h"
#include "extensions/ExtensionMacros.h"
#include "extensions/ExtensionExport.h"
#include "PackageData.h"



class DownManager : public Node
{
public:

	typedef std::function<void(int)> ErrorCallback;
	typedef std::function<void(int)> StateCallback;
	typedef std::function<void(int)> ProgressCallback;
	typedef std::function<void(int)> SuccessCallback;

    enum class ErrorCode
    {
		// 创建文件失败
        CREATE_FILE,
		// 网络失败
        NETWORK,
		// 没有版本更新
        NO_NEW_VERSION,
		// 解压失败
        UNCOMPRESS,
    };
	enum class StateCode
	{
		// 正常
		NORMAL,
		// 下载
		DOWNLOADER,
		// 解压
		UNCOMPRESS,
		// 完成
		SUCCESS,
	};
	enum class SuccessCode
	{
		// 没有更新
		NONEWVERSION,
		// 更新成功
		UPDATESUCCESS,
	};
    
	DownManager();

	virtual ~DownManager();

	CREATE_FUNC(DownManager);
	// 状态变化回调
	void setStateCallback(const StateCallback& func);
    // 错误回调
	void setErrorCallback(const ErrorCallback& func);
	// 下载进度回调
	void setProgressCallback(const ProgressCallback& func);
	// 成功回调
	void setSuccessCallback(const SuccessCallback& func);
	// 更新
	void update();
	// 获取当前下载索引
	int getDownIndex();
	// 获取最大下载数目
	int getMaxDownNum();
	// 创建目录
	static bool createDir(const string& dir);
	// 创建多级目录
	static bool createDepthDir(const string& dir);
private:
	// 检查更新
	bool checkUpdate();
	// 加载版本配置
	void loadConfig();
	// 下载解压
	void downloadAndUncompress();
	// 下载
	bool downLoad(const string& url,const string& name);
	// 解压
	bool uncompress(const string& name, const string& dir);
	
	friend int downManagerProgressFunc(void *, double, double, double, double);
private:
	// 回调
	ErrorCallback		_ErrorCallback;
	StateCallback		_StateCallback;
	ProgressCallback	_ProgressCallback;
	SuccessCallback		_SuccessCallback;
	// 本地包信息
	PackageData			_localPackageData;
	// 网络包信息
	PackageData			_newPackageData;
	// 比较返回文件列表
	vector<PackageInfo>	_difPackageData;
	// 当前状态
	StateCode			_stateCode;
	// 下载地址
	string				_downUrl;
	// 本地版本
	string				_version;
	// url
	void *				_curl;
	// 超时事件
	int					_connectionTimeout;
	// 正在下载索引
	int					_downindex;
	// 总数
	int					_maxDownNum;
	// 下载目录
	string				_downDir;
	// 资源根目录
	string				_resourceDir;
	// 新版文件列表
	string				_gameDataPlist;
};

#endif /* defined(__AssetsManager__) */
