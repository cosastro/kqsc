#include "../h/net.h"

SOCKET server_sock;

WORD wVersionRequested;
WSADATA wsaData;

void net_init(HWND hwnd)
{
	int err;
	sockaddr_in local_addr;

	//��ʼ��win socket lib��
	wVersionRequested = MAKEWORD(2, 2);//����һ��dll�İ汾��
	err = WSAStartup(wVersionRequested, &wsaData);

	if(err != 0)
	{
		MessageBox(NULL, "init winsock DLL failed", "wrong", MB_OK);
		return;
	}

	//�����׽���
	server_sock = socket(AF_INET, SOCK_STREAM, 0);

	if(server_sock == INVALID_SOCKET)
	{
		MessageBox(NULL, "Create socket failed", "wrong", MB_OK);
		return;
	}

	//��ʼ����ַ��Ϣ
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(MYPORT); //16λת������ �ѱ����������ֽ�˳��ת��Ϊ�����ֽ�˳��
	local_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //32λת������ ��һ��������ת��Ϊ�����ֽڵ�˳��
	memset(&local_addr.sin_zero, 0, 0/*sizeof(local_addr.sin_zero)*/);

	//��
	if(bind(server_sock, (sockaddr*)&local_addr, sizeof(sockaddr)))
	{
		MessageBox(NULL, "Bind failed", "wrong", MB_OK);
		return;
	}

	//����
	if(listen(server_sock, 100) == SOCKET_ERROR)
	{
		MessageBox(NULL, "Listen failed", "wrong", MB_OK);
		return;
	}
}

//192.168.0.103
void sever_accept()
{
	SOCKET newSocket; //�û��ӷ���������ͻ��˷�������

	newSocket = accept(server_sock, NULL, NULL); //�û�����ͻ�����������

	if(send(newSocket, "hello,world!\n", 14, 0) == SOCKET_ERROR)
	{
		MessageBox(NULL, "send failed", "wrong", MB_OK);
		return;
	}
	else
		exit(0);

}