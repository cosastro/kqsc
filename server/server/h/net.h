#include<windows.h>
#include<WinSock.h>

#pragma comment (lib,"WS2_32.lib")

#define MYPORT 8889

//void SendToAll(char *str , int len);
//void SendToAllCompplete();

//sPCLIENT_DATA FindClientData( SOCKET sock);
//void AddList(sPCLIENT_DATA data);
void net_init(HWND hwnd);
void sever_accept();
//void sever_send_all_client(struct msg *msg1);
//void sever_send_one_client(char *tmp_x);
//BOOL AcceptNewClient(HWND hwnd);

