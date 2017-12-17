#pragma once

#include <Windows.h>
#include "pipe.h"

//Data types 
#define OS_THREAD_TYPE HANDLE
#define OS_QUEUE_TYPE pipe_t*
#define OS_MUTEX_TYPE HANDLE

//Thread-specific types
#define THREAD_RET_TYPE DWORD WINAPI
#define THREAD_RET_STATEMENT return 0
