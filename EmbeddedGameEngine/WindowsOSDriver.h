#pragma once

#include "OSDriver.h"

class WindowsOSDriver : public OSDriver
{
public:

	void Sleep(int ms);
	bool NewThread(void* entryFunc, const char* threadName, int stackDepth, void* startParams, int priority, OS_TaskHandle& createdTask);
	void DestroyThread(OS_TaskHandle taskHandle);
	void DestroyCurrentThread();
	void JoinThread(OS_TaskHandle taskHandle);
	OS_QueueHandle CreateQueue(int length, size_t element_size);
	bool QueueReceive(OS_QueueHandle queue, void* element, int max_wait_time);
	bool QueueSend(OS_QueueHandle queue, void* element, int max_wait_time);
	int QueueGetWaiting(OS_QueueHandle queue);
	void QueueDelete(OS_QueueHandle queue);
	OS_MutexHandle CreateNewMutex();
	bool MutexLock(OS_MutexHandle mutex, int maxWaitTime);
	bool MutexUnlock(OS_MutexHandle mutex);
	bool MutexDelete(OS_MutexHandle mutex);

	WindowsOSDriver();
	~WindowsOSDriver();
};

