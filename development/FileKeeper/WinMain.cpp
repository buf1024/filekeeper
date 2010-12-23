// FileKeeper.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "resource.h"
#include "Util/SingletonInst.h"
#include "FileKeeper.h"


using namespace lgc;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

    SingletonInst single;
    //An instance has already exists
    if (!single)
    {
        return 0;
    }

	MSG msg;
	HACCEL hAccelTable;


	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FILEKEEPER));


    //Simple initialize, not consider more
    FileKeeper fileKeeper;
    if (fileKeeper.Init())
    {
        fileKeeper.Run();
    }
    else
    {
        //FileKeeper Initializ Fail.
        return -1;
    }
    

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}
