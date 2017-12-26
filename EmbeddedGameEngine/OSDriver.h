#pragma once

/* Define types for threads and queues. Directly taken from implementation.. */
#include "OSTypes.h"
typedef OS_THREAD_TYPE OS_TaskHandle;
typedef OS_QUEUE_TYPE OS_QueueHandle;
typedef OS_MUTEX_TYPE OS_MutexHandle;

/* Describes what we want our OS to be capable of */
class OSDriver
{
public:

	/* put the current thread to sleep */
	virtual void Sleep(int ms) = 0;

	/*
	* Thread creation and managing 
	*/

	/* create a new thread with entry function, thread name, stack, and a handle to it */
	virtual bool NewThread(void* entryFunc, const char* threadName, int stackDepth, void* startParams, int priority, OS_TaskHandle& createdTask) = 0;
	/* destroy a thread */
	virtual void DestroyThread(OS_TaskHandle taskHandle) = 0;
	/* destroy the current thread */
	virtual void DestroyCurrentThread() = 0; 

	/* 
	* Queue creation and managing 
	*/

	/* create a queue which can store *length* elements of size *element_size*. */
	virtual OS_QueueHandle CreateQueue(int length, size_t element_size) = 0;
	/* receive an element from the queue */
	virtual bool QueueReceive(OS_QueueHandle queue, void* element, int max_wait_time) = 0;
	/* send an element into the queue */
	virtual bool QueueSend(OS_QueueHandle queue, void* element, int max_wait_time) = 0;
	/* get number of waiting elements in the queue */
	virtual int QueueGetWaiting(OS_QueueHandle queue) = 0;
	/* Deallocate the queue */
	virtual void QueueDelete(OS_QueueHandle queue) = 0;

	/* 
	* Mutexes, Semaphores
	*/
	virtual OS_MutexHandle CreateNewMutex() = 0;
	//Take the semaphore. Wait at max 'maxWaitTime' milliseconds.
	virtual bool MutexLock(OS_MutexHandle mutex, int maxWaitTime) = 0;
	//Release / give the semaphore.
	virtual bool MutexUnlock(OS_MutexHandle mutex) = 0;
	//Delete this semaphore.
	virtual bool MutexDelete(OS_MutexHandle mutex) = 0;

	OSDriver();
	virtual ~OSDriver();
};

