#ifndef APPMASTER_H
#define APPMASTER_H

#include "ce-appstructs.h"
#include "ce-applications.h"
#include "hardware.h"
#include "ce-appscheduler.h"
#include "data.h"

#define EVENT_MAP_ENTRIES  10

//typedef struct EVENT_MAP_ENTRY_STRUCT
//{
//  unsigned int appId;
//  unsigned int resourcesNeed;
//  unsigned int resourcesUnique;
//  unsigned int energy;
//  unsigned char energyOption;
//  unsigned char duration;
//  unsigned int cpuLoad;
//} EVENT_MAP_ENTRY;





#define DIE_EVENT_1      0x01
#define DIE_EVENT_2      0x02
#define DIE_EVENT_3      0x03
#define DIE_EVENT_4      0x04
#define DIE_EVENT_5      0x05
#define DIE_EVENT_6      0x06
#define KEY_EVENT_1      0x07
#define KEY_EVENT_2      0x08


unsigned int appMasterReceiveEventFromNet(PACKET_APPLICATION_MASTER_EVENT* myEventPacket);
void appMasterFirstClassReceiveEventFromNet(PACKET_APPLICATION_MASTER_1ST_EVENT* myEventPacket);
void appMasterRequestMaster(unsigned int event, unsigned int destination, unsigned int response);
void appMasterReceiveRequestFromNet(PACKET_APPLICATION_MASTER_REQUEST* myEventPacket);
#endif
