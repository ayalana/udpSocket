//For Data messages
#define DATA_MSG_OPCODE 0xD001 
//For Control Messages
#define MANAGER_TO_AMPLIFIER_CONTROL_MSG_OPCODE  0xA002
#define AMPLIFIER_TO_MANAGER_CONTROL_MSG_OPCODE  0xA003
#define MANAGER_TO_MODEM_CONTROL_MSG_OPCODE 0xA004
#define MODEM_TO_MANAGER_CONTROL_MSG_OPCODE 0xA005
#define MANAGER_TO_ANTENNA_CONTROL_MSG_OPCODE 0xA006
#define ANTENNA_TO_MANAGER_CONTROL_MSG_OPCODE 0xA007
#define MSG_SYNC 0xAA55
#define ANTENA_TRANSMITTER 8856
#define AMPLIFIER_TRANSMITTER 8877
#define MODEM_TRANSMITTER 8888
#define MANAGER_TRANSMITTER 8852
#define ANTENA_RECEIVER 8866
#define MODEM_RECEIVER 8833
#define MANAGER_RECEIVER 8895
#define MESSEGE_GENERATOR 6666

#define AMPLIFIER 10
#define ANTENA 20
#define MODEM 30

#define TRANSMITTER 1
#define RECEIVER 2
//#define IP "10.100.102.4"

#pragma once

typedef struct {
    unsigned short msgSync;
    unsigned short Opcode;
    unsigned int msgCounter;
} Header;

typedef struct {
    Header header;
    char Ack; //This is the body message
}ControlMessage;

typedef struct {
    Header header;
    //There is no  body in data message
}DataMessage;

typedef struct {
    int port;
    unsigned short Opcode;
}Controller;


typedef struct {
    unsigned short Opcode;
    //unsigned short Opcode;
    unsigned int time;//like the count
}TimeController;

typedef union {
    Header header;
    ControlMessage ctrlMsg;
    DataMessage dataMsg;
} Message;
