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

#include <Szenario3Appl.h>
#include <FindModule.h>
#include <ApplPkt_m.h>
#include <SimpleSensorData.h>
#include <NetwControlInfo.h>
#include <WakeupPhyUtils.h>
#include <SimpleBattery.h>
#include <WakeUpPacket_m.h>
#include <GenericPacket_m.h>

Define_Module(Szenario3Appl);

Szenario3Appl::Szenario3Appl() {
    iAmLeafNode = false;
    myNetworkAddr = 0;
}

Szenario3Appl::~Szenario3Appl() {
    iAmLeafNode = false;
    myNetworkAddr = 0;
}

void Szenario3Appl::initialize(int stage) {

    CustomMatrixApplication::initialize(stage);

    if (stage == 0) {
        //gates
        dataOut = findGate("lowerLayerOut");
        dataIn = findGate("lowerLayerIn");
        ctrlOut = findGate("lowerControlOut");
        ctrlIn = findGate("lowerControlIn");
        //params
        coordinatorNodeAddr = par("coordinatorNodeAddr");
        sendSensorDataToMasterIntervall = par("sendingIntervall");

        clusterApp->sleepTimeout = 1000;
    }
    if (stage == 1) {



        if (iAmLeafNode) {
            //selfmessage sendToMaster init
            sendToMaster = new cMessage("sendToMaster");
            //nodes should send one after another and not all at the same time so the receiver can receive all messages correctly
            scheduleAt(simTime() + sendSensorDataToMasterIntervall + 0.02 + (0.02 * myNetworkAddr), sendToMaster);
        }

        //memory
        memory = FindModule<Memory*>::findSubModule(findHost());

        //wakeup interval
        INITIAL_DELAY = par("wakeupIntervall");
        cancelEvent(delayTimer);
        scheduleAt(simTime() + INITIAL_DELAY, delayTimer);
    }
}

void Szenario3Appl::handleMessage(cMessage* msg) {
    if (strcmp("sensor data", msg->getName()) == 0) {
        EV << "thats it" << endl;
    }
    ApplPkt* m = dynamic_cast<ApplPkt*>(msg);
    if (m!=0)
    {
        if (myNetworkAddr == coordinatorNodeAddr) {
            EV << "============= Coordinator: Received external Message" << endl;
        } else {
            EV << "============= Non-Coordinator: Received external Message" << endl;
        }

        cArray parList = msg->getParList();

        int i = 0;
        while(msg->getParList().exist(i)) {
            cObject* tmp = parList.get(i);
            i++;
        }
        delete msg;
        return;
    }
    if (msg->isSelfMessage()) {

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
            clusterApp->myPhyLayerBattery->setRadioState(WakeupMiximRadio::POWERDOWN);
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
            return;
        }
        else if (msg == clusterApp->sysTimer)
        {
            clusterApp->clusterApplicationTimerEvent(msg->par("timerId"), msg->par("timerValue"));
            //delete msg;
            return;
        }
        else if (msg == delayTimer)
        {
            clusterApp->wakeupSleepLeaveSleep();
            findHost()->getDisplayString().setTagArg("i2", 0, "status/green");

            //matrixEvent();
            ev << "  processing application timer." << endl;
            if (!delayTimer->isScheduled())
            {
                scheduleAt(simTime() + INITIAL_DELAY + uniform(0, 0.001), delayTimer);
            }
            return;
        }
        else if ((msg->getArrivalGateId() == dataIn) || (msg->isSelfMessage()==1))
        {
            clusterApp->wakeupSleepUpdateTimer();
    //         // we received a data message from someone else !
            WakeUpPacket* w =  dynamic_cast<WakeUpPacket*>(msg);
            if (w!=0)
            {
                if (clusterApp->isInSleepMode) clusterApp->wakeupSleepLeaveSleep();
                findHost()->getDisplayString().setTagArg("i2", 0, "status/green");
                delete msg;
                return;
            }
            GenericPacket* m = dynamic_cast<GenericPacket*>(msg);
            if (m!=0)
                        {
                if (((m->getSrcId() != clusterApp->myNodeId) || (m->getDstId() != clusterApp->myNodeId)) && (msg->isSelfMessage()==1))
                {

                }
                else
                {
                    ev<< "I (" << clusterApp->myNodeId << ") received a message from node "  << m->getSrcId() << "." << endl;

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


                }
                delete msg;
                return;
            }


            if (strcmp(msg->getName(), sendToMaster->getName()) == 0) {
                //memory auslesen und leeren
                int size = memory->getDataSizeCount();
                storage* sensorData = memory->readAllAndClear();
                //sende message an den coordinator node mit messungen
                ApplPkt* dataMessage = new ApplPkt();
                LAddress::L3Type dest = coordinatorNodeAddr;
                dataMessage->setDestAddr(dest);
                NetwControlInfo::setControlInfo(dataMessage, dest);
                dataMessage->setName("sensor data");
                //cArray parList = dataMessage->getParList();

                for (int i = 0; i < size; i++) {
                    SimpleSensorData* tmp = new SimpleSensorData(sensorData[i].type.c_str(), sensorData[i].value);
                    dataMessage->getParList().add(tmp);
                }

                int i = 0;
                while (dataMessage->getParList().exist(i)) {
                    //pkt->getParList().add(parlist->get(i));
                    i++;
                }

                send(dataMessage, dataOut);
                //forward selfmessage
                scheduleAt(simTime() + sendSensorDataToMasterIntervall, sendToMaster);
            }

            return;

        }

    }
}
