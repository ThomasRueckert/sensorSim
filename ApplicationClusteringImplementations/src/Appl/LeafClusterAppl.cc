//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <LeafClusterAppl.h>
#include <FindModule.h>
#include <WakeUpPacket_m.h>
#include <GenericPacket_m.h>
#include <BatteryStatsInfo_m.h>
#include <ApplPkt_m.h>
#include <SimpleBatteryStatsInfo.h>
#include <string.h>
#include <SimpleSensorData.h>

Define_Module(LeafClusterAppl);

#define error -9999
#define emptyTime -1

#define ALL 0
#define TEMPERATURE 1
#define PRESSURE 2
#define HUMIDITY 3
#define LIGHT 4

LeafClusterAppl::LeafClusterAppl() {

}

LeafClusterAppl::~LeafClusterAppl() {
}

void LeafClusterAppl::initialize(int stage) {
    CustomMatrixApplication::initialize(stage);
    if (stage == 1) {
        battery = FindModule<SimpleBattery*>::findSubModule(findHost());
        processor = FindModule<Processor*>::findSubModule(findHost());
        memory = FindModule<Memory*>::findSubModule(findHost());

        hasTemperatureSensor = processor->hasTemperatureSensor;
        hasHumiditySensor = processor->hasHumiditySensor;
        hasPressureSensor = processor->hasPressureSensor;
        hasLightSensor = processor->hasLightSensor;

        clusterApp->sleepTimeout = 10000;
        clusterApp->wakeupSleepEnterSleep();
        findHost()->getDisplayString().setTagArg("i2", 0, "status/red");

        readMemorySelfmessage = new cMessage();
        readMemorySelfmessage->setName("readMemorySelfmessage");

//        double volt = battery->getVoltage();
//        double rel = battery->estimateResidualRelative();
//        double abs = battery->estimateResidualAbs();
    }
}

void LeafClusterAppl::handleMessage(cMessage* msg) {

    if (msg->isSelfMessage() && (msg == readMemorySelfmessage || 0 == strcmp(msg->getName(), readMemorySelfmessage->getName()))) {
        int storageCounter = memory->storageDataSets;
        if (storageCounter < 1) {
            SimpleSensorData* ssd = new SimpleSensorData("invalid memory state", -1);
            ApplPkt* aPkt = new ApplPkt;
            aPkt->getParList().add(ssd);
            aPkt->setSrcAddr(clusterApp->myNodeId);
            aPkt->setDestAddr(LAddress::L3BROADCAST);
            aPkt->setName("measuredValue");
            send(aPkt/*, 0.3  + 0.1 * roomId*/, dataOut);
        } else {
            storage* dataStorage = memory->readAllAndClear();
            for (int i = 0; i < storageCounter; i++) {
                if (dataStorage[i].value != error
                    && dataStorage[i].type != ""
                ) {
                    SimpleSensorData* ssd = new SimpleSensorData(dataStorage[i].type.c_str(), dataStorage[i].value);
                    ApplPkt* aPkt = new ApplPkt;
                    aPkt->getParList().add(ssd);
                    aPkt->setSrcAddr(clusterApp->myNodeId);
                    aPkt->setDestAddr(LAddress::L3BROADCAST);
                    aPkt->setName("measuredValue");
                    send(aPkt/*, 0.3  + 0.1 * roomId*/, dataOut);
                }
            }
        }

        delete msg;
        return;
    }

    char bubblestr[16];
    double energy = clusterApp->mySimpleBattery->estimateResidualRelative() * 100;
    if (clusterApp->nodeIsDown)
    {
        delete msg;
        return;
    }
    if (energy<5 && !clusterApp->nodeIsDown)
    {
        //kill all timer
        clusterApp->clusterApplicationCancelTimers();
        if (delayTimer->isScheduled())
            cancelEvent(delayTimer);

        //kill all app  //Workaround
        clusterApp->applicationLedSwitch(4,0);
        //disable recv
        clusterApp->nodeIsDown = true;
        clusterApp->myPhyLayerBattery->setRadioState(MiximRadio::POWERDOWN);
        sprintf(bubblestr," OFF ");
        clusterApp->myBaseHost->getDisplayString().setTagArg("t", 0, bubblestr);
        clusterApp->myBaseHost->getDisplayString().setTagArg("b", 3, "gray");

        delete msg;
        return;

    }

    clusterApp->clusterApplicationUpdateTickCounter(simTime().inUnit(-3));

    //ev<< "Battery State: " << m << endl;
    ev<< "In MatrixApplication::handleMessage" << endl;
    //HostState::setstate(HostState::S)

    int stop = msg->getArrivalGateId() * 100;
    sprintf(bubblestr," %-.2f %% ", energy);
    clusterApp->myBaseHost->getDisplayString().setTagArg("t", 0, bubblestr);
//    if (clusterApp->myNodeId == 3 )
//    {
//        stop = msg->isSelfMessage();
//        stop = 0;
//        GenericPacket* m = dynamic_cast<GenericPacket*>(msg);
//
//    }
    if (msg == clusterApp->sleepTimer)
    {
        clusterApp->wakeupSleepEnterSleep();
        findHost()->getDisplayString().setTagArg("i2", 0, "status/red");
    }
    else if (msg == clusterApp->sysTimer)
    {
        clusterApp->clusterApplicationTimerEvent(msg->par("timerId"), msg->par("timerValue"));
        //delete msg;
    }
    else if (msg == delayTimer)
    {
        matrixEvent();
        ev << "  processing application timer." << endl;
        if (!delayTimer->isScheduled())
        {
            scheduleAt(simTime() + INITIAL_DELAY + uniform(0, 0.001), delayTimer);
        }
    }
    else if ((msg->getArrivalGateId() == dataIn) || (msg->isSelfMessage()==1))
    {
        clusterApp->wakeupSleepUpdateTimer();
//         // we received a data message from someone else !
        WakeUpPacket* w =  dynamic_cast<WakeUpPacket*>(msg);
        if (w!=0)
        {
            findHost()->getDisplayString().setTagArg("i2", 0, "status/green");
            if (clusterApp->isInSleepMode) clusterApp->wakeupSleepLeaveSleep();
        }
        GenericPacket* m = dynamic_cast<GenericPacket*>(msg);
        if (m!=0)
        {
            if (((m->getSrcId() != clusterApp->myNodeId) || (m->getDstId() != clusterApp->myNodeId)) && (msg->isSelfMessage()==1))
            {

            }
            else
            {
                EV<< "I (" << clusterApp->myNodeId << ") received a message from node "  << m->getSrcId() << "." << endl;

        //        if (debug)
        //            ev<< "I (" << nodeAddr << ") received a message from node "
        //            << m->getSrcId() << " of size " << m->getBitLength() << "." << endl;
                //getParentModule()->bubble("Packet arrived!");

                clusterApp->rxPacketWork.genericPacket.ttl = m->getTtl();
                clusterApp->rxPacketWork.genericPacket.packetType = m->getPacketType();
                clusterApp->rxPacketWork.genericPacket.subType = m->getSubType();
                clusterApp->rxPacketWork.genericPacket.payloadsize = m->getPayloadsize();
                clusterApp->rxPacketWork.genericPacket.dstId = m->getDstId();
                clusterApp->rxPacketWork.genericPacket.srcId = m->getSrcId();
                for (int i = 0; i < clusterApp->rxPacketWork.genericPacket.payloadsize; i++)
                {
                    clusterApp->rxPacketWork.genericPacket.data[i] = m->getData(i);
                }
                //rxPacketWork.rxRssi = m->

                clusterApp->packetsProcessIncommingPacket(&clusterApp->rxPacketWork);

                //double rel = battery->estimateResidualRelative();

                //TODO create packet and send my battery state to my father
//                BatteryStatsInfo *bsMsg = new BatteryStatsInfo();
//                bsMsg->setDestination();
//                bsMsg->setSource();
//                bsMsg->setResidualRelative(rel);

                //TODO only when correct event is sent start the measuring

                SimpleBatteryStatsInfo* sbfi = new SimpleBatteryStatsInfo("estimateResidualRelative", battery->estimateResidualRelative());
                ApplPkt* aPkt = new ApplPkt;
                aPkt->getParList().add(sbfi);
                aPkt->setSrcAddr(clusterApp->myNodeId);
                aPkt->setDestAddr(LAddress::L3BROADCAST);
                aPkt->setName("estimateResidualRelative");
                sendDelayed(aPkt, 0.05 * roomId, dataOut);

            }
        }
        ApplPkt* aPkt = dynamic_cast<ApplPkt*>(msg);
        if (aPkt) {
            if (strcmp(aPkt->getName(), "measuredValue") == 0) {
                EV << "measuredValue" << endl;
            }
            if (strcmp(aPkt->getName(), "Complete Sensor Data") == 0) {
                EV << "Complete Sensor Data" << endl;
            }
            const char* name = msg->getName();
            std::string nameString = name;
            //measure
            std::string nameBeginning = nameString.substr(0,7);
            if (strcmp(nameBeginning.c_str(), "measure") == 0) {
                std::string nameEnding = nameString.substr(8);
                if (strcmp(nameEnding.c_str(), "temperature") == 0) {
                    processor->startSensingUnit(TEMPERATURE);
                } else if (strcmp(nameEnding.c_str(), "pressure") == 0) {
                    processor->startSensingUnit(PRESSURE);
                } else if (strcmp(nameEnding.c_str(), "humidity") == 0) {
                    processor->startSensingUnit(HUMIDITY);
                } else if (strcmp(nameEnding.c_str(), "light") == 0) {
                    processor->startSensingUnit(LIGHT);
                }
            }

            scheduleAt(simTime() + 0.001, readMemorySelfmessage->dup());
        }
        delete msg;
    }
    else if (msg->getArrivalGateId() == ctrlIn)
    {

        delete msg;
    }
    else
    {
        delete msg;
    }
}

void LeafClusterAppl::sendBatteryStatus(int target)
{


    PACKET_EVENT* eventPacketP = (PACKET_EVENT*) &(clusterApp->txPacketPrepare.genericPacket);
    //sprintf(bubblestr,"Dicing: %i",i);
    //getParentModule()->bubble(bubblestr);
    //myBaseModule->getParentModule()->bubble(



    eventPacketP->srcId = clusterApp->myNodeId;
    eventPacketP->dstId = target;
    eventPacketP->ttl = DEFAULT_TTL;
    eventPacketP->packetType = PACKET_TYPE_EVENT;
    eventPacketP->payloadsize = sizeof(PACKET_EVENT) - HEADERSIZE;
    //eventPacketP->event = nextDice;
    eventPacketP->timestamp = 01234;
    eventPacketP->random = rand() & 0xFFFF;

    clusterApp->networkSendPacket((GENERIC_PACKET*) eventPacketP);
    clusterApp->wakeupSleepUpdateTimer();
    //nextDice = 0;
    //networkSendPacketSim((GENERIC_PACKET*) eventPacketP,send,dataOut);

//    if (i % 2 == 0)
//        clusterApp->myBaseHost->getDisplayString().setTagArg("b", 3, "yellow");
//    else
//        clusterApp->myBaseHost->getDisplayString().setTagArg("b", 3, "red");

}
