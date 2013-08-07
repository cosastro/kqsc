#include<windows.h>
#include "../h/net.h"

//-----------------
//�¼�����ص�����
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
			//ui_mdc = CreateCompatibleDC(NULL);					//����һ���뵱DC���ݵ�DC(�൱�ڴ���һ�����ܣ�
			//first_mdc = CreateCompatibleDC(NULL);
			//second_md c =CreateCompatibleDC(NULL);

			net_init(hwnd);
			SetTimer(hwnd, 1, 1, NULL);		//ʱ��ÿ1���� ����һ��

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
//�������
//-------------
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{
	MSG msg;
	HWND hwnd;

	WNDCLASSEX winclass;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = NULL;
	winclass.lpfnWndProc = Windowproc;                              //�¼����
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;                                //Ӧ�ó�����
	winclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);               //ͼ��
	winclass.hCursor = LoadCursor(NULL,IDC_ARROW);                 //���
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);  //���ڱ���ɫ
	winclass.lpszMenuName = NULL;                                  //�˵�
	winclass.lpszClassName = "test";
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	main_hinstance = hinstance;									//����������������������

	if(!RegisterClassEx(&winclass))
		return(0);

	if(!(hwnd=CreateWindowEx(NULL,"test",NULL,/*WS_OVERLAPPEDWINDOW*/NULL,0,0,320,240,
		NULL,NULL,hinstance,NULL)))
		return(0);

	ShowWindow(hwnd,ncmdshow);
	UpdateWindow(hwnd);

	while(TRUE)
	{
		//�����Ϣ
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{ 
			//�Ƿ��˳�����
			if (msg.message == WM_QUIT)
				break;

			//��Ϣת��
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return(msg.wParam);

}//����������