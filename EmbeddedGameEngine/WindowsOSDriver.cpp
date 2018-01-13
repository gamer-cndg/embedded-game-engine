#include "WindowsOSDriver.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> /* only for size_t */

/* HAL OS implementation is done with windows threads! :). */
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "pipe.h"

int WindowsOSDriver::QueueGetWaiting(OS_QueueHandle queue)
{
	return 0; //not implemented
}

void WindowsOSDriver::QueueDelete(OS_QueueHandle queue)
{
	pipe_free(queue);
}

OS_MutexHandle WindowsOSDriver::CreateNewMutex()
{
	return CreateMutex(NULL, 0, NULL);
}

bool WindowsOSDriver::MutexLock(OS_MutexHandle mutex, int maxWaitTime)
{
	DWORD ret = WaitForSingleObject(mutex, (DWORD)maxWaitTime);
	if (ret == WAIT_FAILED || ret == WAIT_TIMEOUT || ret == WAIT_ABANDONED)
		return 0;
	return 1;
}

bool WindowsOSDriver::MutexUnlock(OS_MutexHandle mutex)
{
	return ReleaseMutex(mutex);
}

bool WindowsOSDriver::MutexDelete(OS_MutexHandle mutex)
{
	return CloseHandle(mutex);
}

WindowsOSDriver::WindowsOSDriver()
{
}


WindowsOSDriver::~WindowsOSDriver()
{
}

void WindowsOSDriver::Sleep(int ms)
{
	Sleep(ms);
}

bool WindowsOSDriver::NewThread(void * entryFunc, const char * threadName, int stackDepth, void * startParams, int priority, OS_TaskHandle & createdTask)
{
	HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)entryFunc, startParams, 0, NULL);
	if (!thread)
		return false;
	createdTask = thread;
	return true; //return true
}

void WindowsOSDriver::DestroyThread(OS_TaskHandle taskHandle)
{
	if (taskHandle != NULL)
		TerminateThread(taskHandle, 0) != 0;
	else
		DestroyCurrentThread();
}

void WindowsOSDriver::DestroyCurrentThread()
{
	TerminateThread(GetCurrentThread(), 0);
}

void WindowsOSDriver::JoinThread(OS_TaskHandle taskHandle)
{
	WaitForSingleObject(taskHandle, INFINITE);
}

OS_QueueHandle WindowsOSDriver::CreateQueue(int length, size_t element_size)
{
	return pipe_new(element_size, length);
}

bool WindowsOSDriver::QueueReceive(OS_QueueHandle queue, void * element, int max_wait_time)
{
	pipe_pop((pipe_consumer_t*)queue, element, 1);
	return true;
}

bool WindowsOSDriver::QueueSend(OS_QueueHandle queue, void * element, int max_wait_time)
{
	pipe_push((pipe_producer_t*)queue, element, 1);
	return true;
}
