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

#include <MasterClusterAppl.h>
#include <FindModule.h>
#include <SimpleBattery.h>

Define_Module(MasterClusterAppl);

MasterClusterAppl::MasterClusterAppl() {
    // TODO Auto-generated constructor stub

}

MasterClusterAppl::~MasterClusterAppl() {
    // TODO Auto-generated destructor stub
}

void MasterClusterAppl::initialize(int stage) {
    if (stage == 0)
    {
        // begin by connecting the gates
        // to allow messages exchange
        dataOut = findGate("lowerLayerOut");
        dataIn = findGate("lowerLayerIn");
        ctrlOut = findGate("lowerControlOut");
        ctrlIn = findGate("lowerControlIn");

        clusterApp = new ClusterApplication(this, dataOut);
        clusterApp->myBaseHost = findHost();
        clusterApp->mySimpleBattery = FindModule<SimpleBattery*>::findSubModule(findHost());
        clusterApp->myPhyLayerBattery = FindModule<PhyLayer*>::findSubModule(findHost());
        NetwLayer = FindModule<ClusterApplWiseRoute*>::findSubModule(findHost());

        //myData = new Data(clusterApp);
        // myNetwork = new Network(myData,this,dataOut);
        //myNetwork = new Network(clusterApp);

        clusterApp->clusterApplicationUpdateTickCounter(0);

        INITIAL_DELAY = 5; // initial delay before sending first packet

        delayTimer = new cMessage("app-delay-timer");
        clusterApp->sleepTimeout = 10000;
        clusterApp->myNodeId = NetwLayer->getMyNetworkAddress();
        clusterApp->coordinatorNodeId = LAddress::L3Type(par("coordinatorNodeAddr").longValue());

        scheduleAt(simTime() + INITIAL_DELAY + uniform(0, 0.001), delayTimer); // we add a small shift to avoid systematic collisions
    }
    else  if (stage == 1)
    {
        //nextDice=0;
        clusterApp->wakeupSleepEnterSleep();
        findHost()->getDisplayString().setTagArg("i2", 0, "status/red");
    }
    if (stage == 0) {
        measureTimerIntervall = par("measureTimerIntervall").longValue();
        coordinatorNodeAddr = par("coordinatorNodeAddr").longValue();
        nextDice = GET_SENSOR_TYPES;

    } else if (stage == 1) {

    }
}

void MasterClusterAppl::handleMessage(cMessage * msg)
{

    //update tick counter
    char bubblestr[16];
    clusterApp->clusterApplicationUpdateTickCounter(simTime().inUnit(-3));

    debugEV << "In DiceApplication::handleMessage" << endl;

    if (msg == measuringTimer) {

    }
    else if (msg == clusterApp->sleepTimer)
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
        clusterApp->wakeupSleepLeaveSleep();
        findHost()->getDisplayString().setTagArg("i2", 0, "status/green");

        if (clusterApp->otherNodesInSleepMode)
        {
            clusterApp->otherNodesInSleepMode = false;
            //Send WakeUp-Packet
            debugEV << "  start wakeup" << endl;
            WakeUpPacket* wuPacketP = new WakeUpPacket();
            wuPacketP->setDestAddr(LAddress::L3BROADCAST);
            wuPacketP->setName("WakeUpReceiverPacket");
            NetwControlInfo::setControlInfo(wuPacketP, LAddress::L3BROADCAST);
            send(wuPacketP, dataOut);
            //sendDown(gPacketP);
            //wait some ms
            scheduleAt(simTime() + 0.5 + uniform(0, 0.001), delayTimer);
        }
        else
        {
            sendDiceEvent();

            //nextDice = 0;
            debugEV << "  processing application timer." << endl;
            simtime_t t = simTime() + measureTimerIntervall + uniform(0, 0.001);
            scheduleAt(simTime() + measureTimerIntervall /*+ uniform(0, 0.001)*/, delayTimer);
        }
    }
    else if (msg->getArrivalGateId() == dataIn)
    {
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

void MasterClusterAppl::sendDiceEvent(void)
{


    PACKET_EVENT* eventPacketP = (PACKET_EVENT*) &(clusterApp->txPacketPrepare.genericPacket);
    //sprintf(bubblestr,"Dicing: %i",i);
    //getParentModule()->bubble(bubblestr);
    //myBaseModule->getParentModule()->bubble(


    eventPacketP->srcId = clusterApp->myNodeId;
    eventPacketP->dstId = LAddress::L3BROADCAST;
    eventPacketP->ttl = DEFAULT_TTL;
    eventPacketP->packetType = PACKET_TYPE_EVENT;
    eventPacketP->payloadsize = sizeof(PACKET_EVENT) - HEADERSIZE;
    eventPacketP->event = nextDice;
    eventPacketP->timestamp = 01234;
    eventPacketP->random = rand() & 0xFFFF;

    clusterApp->networkSendPacket((GENERIC_PACKET*) eventPacketP);
    clusterApp->wakeupSleepUpdateTimer();
    nextDice = 0;
    //networkSendPacketSim((GENERIC_PACKET*) eventPacketP,send,dataOut);

//    if (i % 2 == 0)
//        clusterApp->myBaseHost->getDisplayString().setTagArg("b", 3, "yellow");
//    else
//        clusterApp->myBaseHost->getDisplayString().setTagArg("b", 3, "red");

}
