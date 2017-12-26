/*
 * LinuxOSDriver.h
 *
 *  Created on: 25-Dec-2017
 *      Author: pi
 */

#ifndef LINUXOSDRIVER_H_
#define LINUXOSDRIVER_H_

#include "OSDriver.h"

class LinuxOSDriver: public OSDriver {
public:

	void Sleep(int ms);
	bool NewThread(void* entryFunc, const char* threadName, int stackDepth, void* startParams, int priority, OS_TaskHandle& createdTask);
	void DestroyThread(OS_TaskHandle taskHandle);
	void DestroyCurrentThread();
	OS_QueueHandle CreateQueue(int length, size_t element_size);
	bool QueueReceive(OS_QueueHandle queue, void* element, int max_wait_time);
	bool QueueSend(OS_QueueHandle queue, void* element, int max_wait_time);
	int QueueGetWaiting(OS_QueueHandle queue);
	void QueueDelete(OS_QueueHandle queue);
	OS_MutexHandle CreateNewMutex();
	bool MutexLock(OS_MutexHandle mutex, int maxWaitTime);
	bool MutexUnlock(OS_MutexHandle mutex);
	bool MutexDelete(OS_MutexHandle mutex);

	LinuxOSDriver();
	virtual ~LinuxOSDriver();
};

#endif /* LINUXOSDRIVER_H_ */
