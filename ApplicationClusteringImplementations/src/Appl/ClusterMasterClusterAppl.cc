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

#include <ClusterMasterClusterAppl.h>
#include <FindModule.h>
#include "ModuleAccess.h"
#include <string.h>
#include <WakeUpPacket_m.h>
#include <GenericPacket_m.h>
#include <SimpleBattery.h>
#include <PhyLayerBattery.h>

Define_Module(ClusterMasterClusterAppl);

ClusterMasterClusterAppl::ClusterMasterClusterAppl() {
}

ClusterMasterClusterAppl::~ClusterMasterClusterAppl() {
}

void ClusterMasterClusterAppl::initialize(int stage) {
    CustomMatrixApplication::initialize(stage);
    if (stage == 1) {
        NetwLayer = FindModule<ClusterApplWiseRoute*>::findSubModule(findHost());
        childNodes = NetwLayer->getChildNodes(NetwLayer->getMyNetworkAddress());

        do {
            if (childNodes->value != -1) {

                std::stringstream ss;
                ss << "Node" << childNodes->value;
                cModule* node = findModuleWherever(ss.str().c_str(), findHost()->getParentModule());

                SensorNode* sNode = dynamic_cast<SensorNode*>(node);
                if (sNode != NULL) {
                    SensorTypeInformation* sti = new SensorTypeInformation;
                    sti->nodeNetwAddr = childNodes->value;
                    sti->nodeObject = sNode;

                    sti->hasTemperatureSensor = sNode->par("hasTemperatureSensor");
                    sti->hasHumiditySensor = sNode->par("hasHumiditySensor");
                    sti->hasPressureSensor = sNode->par("hasPressureSensor");
                    sti->hasLightSensor = sNode->par("hasLightSensor");
                    SensorTypeInformationVector.push_back(*sti);
                }

            }
            childNodes = childNodes->next;
        } while (childNodes != NULL);
    }
}

void ClusterMasterClusterAppl::handleMessage(cMessage* msg) {
    //todo get battery status of all my leafs -> this must be done per message

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
