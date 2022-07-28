#include "..\..\shared\Device.h"
#include <thread>
#include "PackageAntena.h"
#include "PackageModem.h"
#include <list>
#include "..\shared\IDD.h"
#include <vector>
#include "..\shared\Socket.h"
#include <stdio.h>
#pragma once
#include <stdio.h>
#include <mutex>
using namespace std;
mutex mtx;// mutex for critical section


class Manager
{
	/// <summary>
	/// ctor that received a vector in which each object contains an opcode and a port
	/// and get type of program RECEIVER/TRANSMITTER
	/// and runs three processes
	///One process that sends the messages every second
	///	And a second process that receives them
	/// and a other process that check all 5 seconds if there any unreturned messages
	/// </summary>
public:
	Manager(std::vector<Controller>& controllers, int type) {
		this->controllers = controllers;
		this->count = 0;
		this->Type = type;
		std::thread t1(&Manager::sendMessageServer, this);
		t1.detach();
		std::thread t2(&Manager::getMessageClient, this);
		t2.detach();
		std::thread t3(&Manager::checklist, this);
		t3.detach();
	}
	~Manager() {
		delete &listSend;
		delete& controllers;
	}
	std::vector<TimeController> listSend = {};//Vector of the sent messages
	std::vector<Controller> controllers = {};//vector in which each object contains an opcode and a port to send them
	Socket socket;
	int Type;
	int count = 0;
	//process that receives the messsgae
	void getMessageClient() {
		while (1) {
			Message message;
			if (Type == RECEIVER)//send the port According to the type
				message = socket.recvfrom(MANAGER_RECEIVER);
			else
				message = socket.recvfrom(MANAGER_TRANSMITTER);

			Header header = message.header;

			//print the value of message
			printf("counter:: %d\n",header.msgCounter);
			printf("opcode:: %x\n", header.Opcode);
			printf("msgSync:: %x\n",header.msgSync);

			//cout << "manager received...!" << header->msgCounter << "\n";

			//check if it is message
			//and The message was sent for me by the opcod
			if (header.msgSync == (unsigned short)MSG_SYNC && validOpCode(header.Opcode))
			{
				//if it is control message
				if (header.Opcode != (unsigned short)DATA_MSG_OPCODE) {
					ControlMessage cm =message.ctrlMsg;
					printf("ack:: %d\n", cm.Ack);
					//if the message is not correct
					/*if (cm.Ack != 1)
						cout << "The message was incorrect.There must have been a problem during one of the previous messages\n";*/
					//create object  that contains opcode and time/count(it is same...)
					TimeController tm = { cm.header.Opcode,cm.header.msgCounter };
					//check if it is message that returned and erase this from the vector
					for (size_t i = 0; i < listSend.size(); i++)
					{
						if (tm.Opcode == listSend[i].Opcode && tm.time == listSend[i].time)
						{
							mtx.lock();
							listSend.erase(listSend.begin() + i);
							mtx.unlock();
						}
					}

				}
				//if it is data message
				else {
					if (this->Type == TRANSMITTER)
					{
						socket.sendto(MODEM_TRANSMITTER, (char*)&message, "10.100.102.4");
					}
					else {
						socket.sendto(MESSEGE_GENERATOR, (char*)&message, "10.100.102.4");
					}
				}
			}
			//if it is not message
			else
				cout << "The message is invalid\n";
		}
	}
	//Checking if the message is intended for me according to the opcode
	bool validOpCode(unsigned short opCode) {
		return(opCode==DATA_MSG_OPCODE|| opCode == (unsigned short)AMPLIFIER_TO_MANAGER_CONTROL_MSG_OPCODE || opCode == (unsigned short)MODEM_TO_MANAGER_CONTROL_MSG_OPCODE || opCode == (unsigned short)ANTENNA_TO_MANAGER_CONTROL_MSG_OPCODE);
	}
	//process that check all 5 seconds if there any unreturned messages
	void checklist() {
		while (1) {
			this_thread::sleep_for(std::chrono::seconds(5));
			for (size_t i = 0; i < listSend.size(); i++)
			{
				if (count > listSend[i].time + 5)
				{
					//cout << "i didnt get a answer\n";
					mtx.lock();
					listSend.erase(listSend.begin() + i);
					mtx.unlock();
				}
			}
		}
	}
	//process that sends the messages every second
	void sendMessageServer() {
		while (1) {
			for (int i = 0; i < controllers.size(); i++)
			{
				ControlMessage message;
				message.Ack = 0;
				message.header.msgSync = MSG_SYNC;
				message.header.msgCounter = count;//the count Increases by 1 with each message
				message.header.Opcode = controllers[i].Opcode;
				Message m;
				m.ctrlMsg = message;
				socket.sendto(controllers[i].port, (char*)&m, "10.100.102.4");
				TimeController tc;
				tc.Opcode = controllers[i].Opcode;
				tc.time = count;//this like count
				mtx.lock();
				listSend.push_back(tc);//enter to vector
				mtx.unlock();
			}
			this_thread::sleep_for(std::chrono::seconds(1));
			count++;
		}
	}
};

