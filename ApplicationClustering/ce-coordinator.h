#ifndef CE_COORDINATOR_H
#define CE_COORDINATOR_H

#define NODE_ENTRIES 20


#define COORDINATOR_APP_ENTRIES  20
#define EVENT_TO_APP_ENTRIES  8
//#define EVENT_MAP_ENTRIES  20

#define DIE_EVENT_1      0x01
#define DIE_EVENT_2      0x02
#define DIE_EVENT_3      0x03
#define DIE_EVENT_4      0x04
#define DIE_EVENT_5      0x05
#define DIE_EVENT_6      0x06

#define KEY_EVENT_1      0x07
#define KEY_EVENT_2      0x08

#define COORDINATOR_REQUEST_TIMEOUT 200
#define COORDINATOR_UPDATE_TIMEOUT  1000
#define COORDINATOR_ALIVE_TIMEOUT  60000


#define COORDINATOR_STATE_IDLE      0x01
#define COORDINATOR_STATE_REQUEST   0x02
#define COORDINATOR_STATE_UPDATE    0x04
#define COORDINATOR_STATE_ALIVE     0x08
#define COORDINATOR_STATE_DUMMY_3   0x10
#define COORDINATOR_STATE_DUMMY_4   0x20
#define COORDINATOR_STATE_DUMMY_5   0x40
#define COORDINATOR_STATE_DUMMY_6   0x80

extern unsigned short coordinatorNodeId;


typedef struct COORDINATOR_APP_ENTRY_STRUCT
{
  unsigned short globalAppId;
  unsigned short status;
  unsigned int masterId;
  unsigned int masterIdAlt;
  unsigned short event;
  unsigned short reference;
  unsigned short globalAppGroup;
  unsigned short dummy; //byte filler
  unsigned long timestamp;
  unsigned long timeout;    //TODO: redundant to timestamp ?
} COORDINATOR_APP_ENTRY;


typedef struct EVENT_TO_APP_ENTRY_STRUCT
{
  unsigned int eventId;
  unsigned int appId;
  unsigned int dummyA;
  unsigned int dummyB;
} EVENT_TO_APP_ENTRY;

typedef struct EVENT_MAP_ENTRY_STRUCT
{
  unsigned int appId;
  unsigned int resourcesNeed;
  unsigned int resourcesUnique;
  unsigned int energy;
  unsigned char energyOption;
  unsigned char duration;
  unsigned int cpuLoad;
} EVENT_MAP_ENTRY;

enum APP_STATES
{
    IS_EMPTY = 0x1000,
    APPLICATION_RUN,
    REQUEST_EVENT,
    REQUEST_APP,
    REQUEST_APP_TRANSMIT,
    REQUEST_DONE,
    APPLICATION_RUN_FORGET
};

//void coordinatorInit(void);
//void coordinatorManager(void);
//void coordinatorReceiveEvent(PACKET_EVENT* myEventPacketP);
//void coordinatorReceiveResponse(PACKET_APPLICATION_REQUEST* myPacket);
#endif
