////#include "..\shared\Device.h"
////#include "Server_.h"
//#include <stdio.h>
//#include <thread>
//#pragma once;
//
//class PackageAntena : Device
//{
//public:
//	PackageAntena(unsigned short port, unsigned short opcode, unsigned short returnOpCode, int type) :Device(port, opcode, returnOpCode, type) {
//		this->returnOpCode = returnOpCode;
//		std::thread t1(&PackageAntena::getMessage, this);
//		t1.detach();
//	}
//	Socket socket;
//	unsigned short returnOpCode;
//	void getMessage() {
//		int port;
//		if (this->Type == RECEIVER)
//			port = ANTENA_RECEIVER;
//		else
//			port = ANTENA_TRANSMITTER;
//	}
//	//Device::getMessage(port);
//	//while (1)
//	//{
//	//	char* message;
//	//	if (this->Type == RECEIVER)
//	//		message = socket.recvfrom(ANTENA_RECEIVER);
//	//	else
//	//		message = socket.recvfrom(ANTENA_TRANSMITTER);
//
//	//	//בדיקה שלא הודעת דתא
//	//	ControlMessage cm = *(ControlMessage*)message;
//	//	ControlMessage* controlMessage = new ControlMessage[sizeof(Controller)];
//	//	controlMessage = &cm;
//	//	//printf("counter:: %d\n", controlMessage->header.msgCounter);
//	//	//printf("opcode:: %d\n", controlMessage->header.Opcode);
//	//	//printf("Ack:: %c\n", controlMessage->Ack);
//
//	//	if (controlMessage->header.msgCounter != (1 + this->last))
//	//		controlMessage->Ack = 0;
//	//	else
//	//		controlMessage->Ack = 1;
//	//	this->last = controlMessage->header.msgCounter;
//	//	//cout << "antena received.........!!!!!!!" <<<< "\n";
//	//	if(Type==RECEIVER)
//	//		socket.sendto(MANAGER_RECEIVER, (char*)controlMessage, "10.100.102.4");
//	//	else
//	//		socket.sendto(MANAGER_TRANSMITTER, (char*)controlMessage, "10.100.102.4");
//	//}
//
//}
//
