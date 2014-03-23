// testThreadsLock.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <process.h>

CRITICAL_SECTION section1;
CRITICAL_SECTION section2;

unsigned int __stdcall   ThreadProc1(void * parame);
unsigned int __stdcall   ThreadProc2(void * parame);

int _tmain(int argc, _TCHAR* argv[])
{
    InitializeCriticalSection(&section1);
    InitializeCriticalSection(&section2);

    unsigned threadID1; 
    HANDLE  thread1 = (HANDLE)_beginthreadex(NULL, 0, &ThreadProc1, 0, CREATE_SUSPENDED, &threadID1);
    ResumeThread(thread1);

    unsigned threadID2; 
    HANDLE  thread2 = (HANDLE)_beginthreadex(NULL, 0, &ThreadProc2, 0, 0, &threadID2);

    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    DeleteCriticalSection(&section2);
    DeleteCriticalSection(&section1);

    getchar();
	return 0;
}

unsigned int __stdcall   ThreadProc1(void * parame)
{
    EnterCriticalSection(&section1);
    Sleep(1000*2);
    EnterCriticalSection(&section2);

    LeaveCriticalSection(&section2);
    LeaveCriticalSection(&section1);
    return 0;
}

unsigned int __stdcall   ThreadProc2(void * parame)
{
    EnterCriticalSection(&section2);
    Sleep(1000*2);
    EnterCriticalSection(&section1);

    LeaveCriticalSection(&section1);
    LeaveCriticalSection(&section2);

    return 100;
}

