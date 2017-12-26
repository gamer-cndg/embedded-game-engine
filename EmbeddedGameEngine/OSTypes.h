#pragma once

#include "Config.h"

#if ENGINE_OS == OS_WINDOWS
#include <Windows.h>
#include "pipe.h"

//Data types 
#define OS_THREAD_TYPE HANDLE
#define OS_QUEUE_TYPE pipe_t*
#define OS_MUTEX_TYPE HANDLE

//Thread-specific types
#define THREAD_RET_TYPE DWORD WINAPI
#define THREAD_RET_STATEMENT return 0

#elif ENGINE_OS == OS_LINUX
#include <pthread.h>
#include "PThreadQueue.h"
#include "MessageBusMessage.h"

#define OS_THREAD_TYPE pthread_t
#define OS_QUEUE_TYPE PThreadQueue<MessageBusMsg>*
#define OS_MUTEX_TYPE pthread_mutex_t*
#define THREAD_RET_TYPE void*
#define THREAD_RET_STATEMENT return NULL

#elif ENGINE_OS == OS_ESP32

#else
#error "No OS for game engine selected!!"

#endif

