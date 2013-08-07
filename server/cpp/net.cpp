#include "../h/net.h"

SOCKET server_sock;

WORD wVersionRequested;
WSADATA wsaData;

void net_init(HWND hwnd)
{
	int err;
	sockaddr_in local_addr;

	//初始化win socket lib库
	wVersionRequested = MAKEWORD(2, 2);//产生一个dll的版本号
	err = WSAStartup(wVersionRequested, &wsaData);

	if(err != 0)
	{
		MessageBox(NULL, "init winsock DLL failed", "wrong", MB_OK);
		return;
	}

	//创建套接字
	server_sock = socket(AF_INET, SOCK_STREAM, 0);

	if(server_sock == INVALID_SOCKET)
	{
		MessageBox(NULL, "Create socket failed", "wrong", MB_OK);
		return;
	}

	//初始化地址信息
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(MYPORT); //16位转化方法 把本地主机的字节顺序转化为网络字节顺序
	local_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //32位转化方法 把一个长整型转化为网络字节的顺序
	memset(&local_addr.sin_zero, 0, 0/*sizeof(local_addr.sin_zero)*/);

	//绑定
	if(bind(server_sock, (sockaddr*)&local_addr, sizeof(sockaddr)))
	{
		MessageBox(NULL, "Bind failed", "wrong", MB_OK);
		return;
	}

	//监听
	if(listen(server_sock, 100) == SOCKET_ERROR)
	{
		MessageBox(NULL, "Listen failed", "wrong", MB_OK);
		return;
	}
}

//192.168.0.103
void sever_accept()
{
	SOCKET newSocket; //用户从服务器端向客户端发送数据

	newSocket = accept(server_sock, NULL, NULL); //用户处理客户端连接请求

	if(send(newSocket, "hello,world!\n", 14, 0) == SOCKET_ERROR)
	{
		MessageBox(NULL, "send failed", "wrong", MB_OK);
		return;
	}
	else
		exit(0);

}