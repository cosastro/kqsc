#include<windows.h>
#include "../h/net.h"

//-----------------
//事件句柄回调函数
//-----------------

HINSTANCE main_hinstance;

HDC		first_mdc;
HDC		second_mdc;
HDC		ui_mdc;

LRESULT CALLBACK Windowproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{			
	case WM_CREATE:
		{   
			//ui_mdc = CreateCompatibleDC(NULL);					//建立一个与当DC兼容的DC(相当于创建一个画架）
			//first_mdc = CreateCompatibleDC(NULL);
			//second_md c =CreateCompatibleDC(NULL);

			net_init(hwnd);
			SetTimer(hwnd, 1, 1, NULL);		//时钟每1毫秒 触发一次

			return(0);
		}break;
	case WM_TIMER:
		{	
			sever_accept();
			return(0);
		}break;
	case WM_DESTROY:
		{
			KillTimer(hwnd,1);
			PostQuitMessage(0);
			return(0);
		}break;
	}
	return(DefWindowProc(hwnd,msg,wparam,lparam));
}

//-------------
//程序入口
//-------------
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{
	MSG msg;
	HWND hwnd;

	WNDCLASSEX winclass;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = NULL;
	winclass.lpfnWndProc = Windowproc;                              //事件句柄
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;                                //应用程序句柄
	winclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);               //图标
	winclass.hCursor = LoadCursor(NULL,IDC_ARROW);                 //光标
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);  //窗口背景色
	winclass.lpszMenuName = NULL;                                  //菜单
	winclass.lpszClassName = "test";
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	main_hinstance = hinstance;									//将程序句柄传给其它函数用

	if(!RegisterClassEx(&winclass))
		return(0);

	if(!(hwnd=CreateWindowEx(NULL,"test",NULL,/*WS_OVERLAPPEDWINDOW*/NULL,0,0,320,240,
		NULL,NULL,hinstance,NULL)))
		return(0);

	ShowWindow(hwnd,ncmdshow);
	UpdateWindow(hwnd);

	while(TRUE)
	{
		//检测消息
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{ 
			//是否退出程序
			if (msg.message == WM_QUIT)
				break;

			//消息转换
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return(msg.wParam);

}//主函数结束