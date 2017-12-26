/*
 * LinuxOSDriver.cpp
 *
 *  Created on: 25-Dec-2017
 *      Author: pi
 */

#include "LinuxOSDriver.h"
/* incude os-specific stuff */
#include "time.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void LinuxOSDriver::Sleep(int ms) {
	usleep(1000 * ms);
}

bool LinuxOSDriver::NewThread(void* entryFunc, const char* threadName, int stackDepth, void* startParams, int priority, OS_TaskHandle& createdTask){
	pthread_t thread;
	int ret = pthread_create(&thread, NULL, (void* (*)(void*)) entryFunc, startParams);
	if(ret == 0) {
		createdTask = thread;
		return true;
	} else {
		return false;
	}
}

void LinuxOSDriver::DestroyThread(OS_TaskHandle taskHandle){
	pthread_cancel(taskHandle);
}

void LinuxOSDriver::DestroyCurrentThread() {
	pthread_cancel(pthread_self());
}

void LinuxOSDriver::JoinThread(OS_TaskHandle taskHandle)  {
	pthread_join(taskHandle, NULL);
}


#include "MessageBusMessage.h"
OS_QueueHandle LinuxOSDriver::CreateQueue(int length, size_t element_size) {
	//TODO: better implementation which accepts arbitrary size
	//queue elements...
	if(element_size != sizeof(MessageBusMsg)){
		throw std::exception();
		return nullptr;
	}
	OS_QueueHandle q = new PThreadQueue<MessageBusMsg>();
	return q;
}

bool LinuxOSDriver::QueueReceive(OS_QueueHandle queue, void* element, int max_wait_time) {
	MessageBusMsg m;
	m = queue->remove();
	memcpy(element, &m, sizeof(MessageBusMsg));
	return true;
}

bool LinuxOSDriver::QueueSend(OS_QueueHandle queue, void* element, int max_wait_time) {
	MessageBusMsg m;
	memcpy(&m, element,sizeof(MessageBusMsg));
	queue->add(m);
	return true;
}

int LinuxOSDriver::QueueGetWaiting(OS_QueueHandle queue) {
	return (int)queue->size();
}

void LinuxOSDriver::QueueDelete(OS_QueueHandle queue) {
	delete queue;
}

OS_MutexHandle LinuxOSDriver::CreateNewMutex() {
	pthread_mutex_t* m = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(m, NULL);
	return m;
}

bool LinuxOSDriver::MutexLock(OS_MutexHandle mutex, int maxWaitTime) {
	return pthread_mutex_lock(mutex) == 0;
}

bool LinuxOSDriver::MutexUnlock(OS_MutexHandle mutex) {
	return pthread_mutex_unlock(mutex) == 0;
}

bool LinuxOSDriver::MutexDelete(OS_MutexHandle mutex) {
	if(!mutex) return false;
	free((void*)mutex);
	return true;
}

LinuxOSDriver::LinuxOSDriver() { }

LinuxOSDriver::~LinuxOSDriver() { }

