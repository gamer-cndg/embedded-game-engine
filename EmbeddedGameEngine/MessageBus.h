#pragma once

/* This is the messaging bus. 
* It defines messages and interfaces for 
* sending and receiving data over it.
* We need the operating system's queues for that
*/
#include "OSDriver.h"
#include "GlobalSystems.h"
#include "MessageBusMessage.h"
#include <array>
#include <map>

enum class SubsystemType { GFX, Sound, Scripts };

class MessageBus
{
public:
	void RegisterQueue(SubsystemType sys, OS_QueueHandle queue) {
		queues[sys] = queue;
	}
	void SendBusMessage(SubsystemType sys, MessageBusMsg message, bool waitForAnswer = false) {
		//TODO: check if system is aready registered..
		OS->QueueSend(queues[sys], &message, INT32_MAX);
	}

	MessageBus();
	~MessageBus();
private:
	std::map<SubsystemType, OS_QueueHandle> queues;
};


template <SubsystemType E> class MessageBusReceiver {
public:
	virtual void ProcessMessage(MessageBusMsg msg) = 0;

	void Init() {
		queue = OS->CreateQueue(10, sizeof(MessageBusMsg));
		MsgBus->RegisterQueue(E, queue);
	}

	void ProcessOne() {
		MessageBusMsg m;
		if(OS->QueueReceive(queue, &m, INT32_MAX)) {
			ProcessMessage(m);
		}
	}
	
	MessageBusReceiver() {}
	~MessageBusReceiver() { OS->QueueDelete(queue); }

	static void StartThread(void* receiver) {
		MessageBusReceiver* msgReceiver = (MessageBusReceiver) receiver;
		while(true) {
			msgReceiver->ProcessOne();
		}
	}

private:
	OS_QueueHandle queue;
};

