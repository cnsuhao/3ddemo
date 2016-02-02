#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

//#define XXTEA_RES

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
#ifdef XXTEA_RES
	char path[1024 * 10];
	GetModuleFileNameA(hInstance, path, sizeof(path));
	std::string dir = path;
	for (int i = 0; i < 1; ++i)
	{
		dir = dir.substr(0, dir.rfind("\\"));
	}
	dir += "\\Resources.encode";
	SetCurrentDirectoryA(dir.c_str());
#else
	char path[1024 * 10];
	GetModuleFileNameA(hInstance, path, sizeof(path));
	std::string dir = path;
	for (int i = 0; i < 3; ++i)
	{
		dir = dir.substr(0, dir.rfind("\\"));
	}
	dir += "\\Resources";
	SetCurrentDirectoryA(dir.c_str());
#endif
    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
