#pragma once
#include <thread>
#include "../../shared/IDD.h"
#include "../../shared/Socket.h"
#include <stdio.h>

using namespace std;

class messageGenerator
{
public:
	/// <summary>
	/// ctor that receives from the user some data messages to send
	/// and runs two processes
	///One process that sends the messages every second
	///	And a second process that receives them and counts how many have arrived
	/// </summary>
	messageGenerator() {
		std::cout << "Enter a few seconds for the program to run\n";
		cin >> num;
		countSend = 0;
		countGet = 0;
		t1 = std::thread(&messageGenerator::Tx, this);
		t1.detach();
		t2 = std::thread(&messageGenerator::Rx, this);
		t2.detach();

	}

	int countSend;	//Amount of messages sent
	std::thread t1;
	std::thread t2;
	int countGet;//	Amount of messages received
	int num = 0;
	Socket socket;//UDP communication by socket

	//process that receives them and counts how many have arrived	
	void Rx() {
		while (1) {
			Message message = socket.recvfrom(MESSEGE_GENERATOR);
			Header h = message.header;
			//Header* header = new Header[sizeof(Controller)];
			//header = &h;
			if (h.Opcode == DATA_MSG_OPCODE) {//If this is a DATA message
				countGet++;
			}
		}
	}

	//process that sends the messages every second
	void Tx() {
		while (countSend < num) {
		cout << countSend << endl;
		DataMessage message;
		message.header.msgSync = MSG_SYNC;
		message.header.msgCounter = countSend;
		message.header.Opcode = DATA_MSG_OPCODE;
		Message msg;
		msg.dataMsg = message;
		socket.sendto(MANAGER_TRANSMITTER, (char*)&msg, "127.0.0.1");
		this_thread::sleep_for(std::chrono::seconds(1));
		countSend++;
		}
		//After the amount of messages is over, the program prints a summary and exits the program
		std::cout << "in time: " << countSend << " send " << countSend << "message and get a " << countGet << " messages\n";
		exit(0);

	}
};


