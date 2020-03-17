/**
 * SO, 2016 - Lab #4, Semnale
 * Task #3, Windows
 *
 * Timers usage.
 */

#define _WIN32_WINNT	0x0500

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include <windows.h>

#define _SECOND		10000000
#define TIMEOUT		(-2 * _SECOND)
#define INF 100000000000

/*
 * rutina APC asociata timer-ului
 */

static VOID CALLBACK TimerAPCProc(LPVOID lpArgToCompletionRoutine,
		DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
	/* TODO: Use ctime and time to print current time. */

	time_t crtTime = time(NULL);
	UNREFERENCED_PARAMETER(lpArgToCompletionRoutine);
	UNREFERENCED_PARAMETER(dwTimerLowValue);
	UNREFERENCED_PARAMETER(dwTimerHighValue);

	printf("ctime: %s\n", ctime(&crtTime));
}

/*
 * initializeaza si configureaza timer
 */

static void InitSetTimer(void)
{
	/* TODO */
	HANDLE hTimer;
	LARGE_INTEGER dueTime;
	BOOL bRet;

	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	if (hTimer == NULL) {
		printf("CreateWritableTimer\n");
		exit(1);
	} 

	dueTime.QuadPart = TIMEOUT;

	bRet = SetWaitableTimer(hTimer, &dueTime, 2000, TimerAPCProc, NULL, FALSE);
	if (bRet == FALSE) {
		printf("SetWaitableTimer");	
	} 
}

int main(void)
{
	InitSetTimer();		/* configureaza timer la 2 secunde */

	while (1) {
		/* TODO: Wait for timer (use SleepEx function). */
		SleepEx(INF, TRUE);
	}

	return 0;
}
