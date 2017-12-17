#pragma once

enum class SubsystemType { GFX, Sound, Scripts };

/* This is the messaging bus. 
* It defines messages and interfaces for 
* sending and receiving data over it.
* We need the operating system's queues for that
*/
#include "OSDriver.h"
#include "GlobalSystems.h"
#include <array>
#include <map>

struct MessageBusMsg {
	int cmd;
	void* pData;
};

template <SubsystemType E> class MessageBusReceiver {
public:
	virtual void ProcessMessage(MessageBusMsg msg) = 0;

	void Init() {
		OS->CreateQueue(10, sizeof(MessageBusMsg));
	}
	
	MessageBusReceiver() {}
	~MessageBusReceiver() {}
private:
	OS_QueueHandle queue;
};

class MessageBus
{
public:
	void RegisterQueue(SubsystemType sys, OS_QueueHandle queue);
	void SendBusMessage(SubsystemType sys, MessageBusMsg message, bool waitForAnswer = false);


	MessageBus();
	~MessageBus();
private:
	std::map<SubsystemType, OS_QueueHandle> queues;
};

