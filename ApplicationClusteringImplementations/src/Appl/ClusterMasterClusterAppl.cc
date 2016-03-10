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
#include <SimpleBatteryStatsInfo.h>
#include <LeafClusterAppl.h>
#include <NetwControlInfo.h>
#include <ApplPkt_m.h>
#include <carray.h>

Define_Module(ClusterMasterClusterAppl);

ClusterMasterClusterAppl::ClusterMasterClusterAppl() {
    counterSensorNodeAnswers = 0;
    numChildNodes = 0;
    hasTemperatureSensor = false;
    hasHumiditySensor = false;
    hasPressureSensor = false;
    hasLightSensor = false;
    sensorSum = 0;
}

ClusterMasterClusterAppl::~ClusterMasterClusterAppl() {
}

void ClusterMasterClusterAppl::initialize(int stage) {
    CustomMatrixApplication::initialize(stage);
    if (stage == 1) {

        NetwLayer = FindModule<ClusterApplWiseRoute*>::findSubModule(findHost());
        childNodes = NetwLayer->getChildNodes(NetwLayer->getMyNetworkAddress());

        roomNumber = par("roomNumber");
        if (roomNumber == -1) {
            opp_error("No roomNumber was defined for this Cluster Masters Applayer. Every ClusterMasterClusterAppl must define a room number");
        }

        int roomId = 0;
        do {
            if (childNodes->value != -1) {

                std::stringstream ss;
                ss << "Node" << childNodes->value;
                cModule* node = findModuleWherever(ss.str().c_str(), findHost()->getParentModule());

                SensorNode* sNode = dynamic_cast<SensorNode*>(node);

                if (sNode != NULL) {
                    LeafClusterAppl* appl = FindModule<LeafClusterAppl*>::findSubModule(sNode);
                    if (appl == NULL) {
                        opp_error("All Child nodes of ClusterMaster must be Leaf Nodes.");
                    }

                    appl->roomNumber = roomNumber;
                    appl->roomId = roomId;
                    roomId++;

                    SensorTypeInformation* sti = new SensorTypeInformation;
                    sti->nodeNetwAddr = childNodes->value;
                    sti->nodeObject = sNode;

                    sti->hasTemperatureSensor = sNode->par("hasTemperatureSensor");
                    if (sti->hasTemperatureSensor && !hasTemperatureSensor) {
                        hasTemperatureSensor = true;
                        sensorSum++;
                    }
                    sti->hasHumiditySensor = sNode->par("hasHumiditySensor");
                    if (sti->hasHumiditySensor && !hasHumiditySensor) {
                        hasHumiditySensor = true;
                        sensorSum++;
                    }
                    sti->hasPressureSensor = sNode->par("hasPressureSensor");
                    if (sti->hasPressureSensor && !hasPressureSensor) {
                        hasPressureSensor = true;
                        sensorSum++;
                    }
                    sti->hasLightSensor = sNode->par("hasLightSensor");
                    if (sti->hasLightSensor && !hasLightSensor) {
                        hasLightSensor = true;
                        sensorSum++;
                    }
                    numChildNodes ++;
                    SensorTypeInformationVector.push_back(*sti);
                }

            }
            childNodes = childNodes->next;
        } while (childNodes != NULL);

        clusterApp->sleepTimeout = 10000;
        clusterApp->wakeupSleepEnterSleep();
        findHost()->getDisplayString().setTagArg("i2", 0, "status/red");

        InitMeasuringEvent = new cMessage();
        InitMeasuringEvent->setName("InitMeasuringEvent");

        sensorValues = *(new cArray);
    }
}

void ClusterMasterClusterAppl::handleMessage(cMessage* msg) {
    //todo get battery status of all my leafs -> this must be done per message

    if (msg == InitMeasuringEvent
            || strcmp(InitMeasuringEvent->getName(), msg->getName()) == 0 ) {

        int highestTemperatureBatteryId = -1;
        int highestPressureBatteryId = -1;
        int highestLightBatteryId = -1;
        int highestHumidityBatteryId = -1;

        double highestTemperatureBatteryValue = 1;
        double highestPressureBatteryValue = 1;
        double highestLightBatteryValue = 1;
        double highestHumidityBatteryValue = 1;

        for (int i = 0; i < numChildNodes; i++) {
            if (SensorTypeInformationVector.at(i).hasTemperatureSensor) {
                if (SensorTypeInformationVector.at(i).residualRelative < highestTemperatureBatteryValue) {
                    highestTemperatureBatteryValue = SensorTypeInformationVector.at(i).residualRelative;
                    highestTemperatureBatteryId = SensorTypeInformationVector.at(i).nodeNetwAddr;
                }
            }
            if (SensorTypeInformationVector.at(i).hasPressureSensor) {
                if (SensorTypeInformationVector.at(i).residualRelative < highestPressureBatteryValue) {
                    highestPressureBatteryValue = SensorTypeInformationVector.at(i).residualRelative;
                    highestPressureBatteryId = SensorTypeInformationVector.at(i).nodeNetwAddr;
                }
            }
            if (SensorTypeInformationVector.at(i).hasLightSensor) {
                if (SensorTypeInformationVector.at(i).residualRelative < highestLightBatteryValue) {
                    highestLightBatteryValue = SensorTypeInformationVector.at(i).residualRelative;
                    highestLightBatteryId = SensorTypeInformationVector.at(i).nodeNetwAddr;
                }
            }
            if (SensorTypeInformationVector.at(i).hasHumiditySensor) {
                if (SensorTypeInformationVector.at(i).residualRelative < highestHumidityBatteryValue) {
                    highestHumidityBatteryValue = SensorTypeInformationVector.at(i).residualRelative;
                    highestHumidityBatteryId = SensorTypeInformationVector.at(i).nodeNetwAddr;
                }
            }
        }

        if (highestTemperatureBatteryId > -1) {
            ApplPkt* aPkt = new ApplPkt();
            aPkt->setName("measure temperature");
            aPkt->setDestAddr(highestTemperatureBatteryId);
            NetwControlInfo::setControlInfo(aPkt, highestTemperatureBatteryId);
            send(aPkt, dataOut);
        }
        if (highestPressureBatteryId > -1) {
            ApplPkt* aPkt = new ApplPkt();
            aPkt->setName("measure pressure");
            aPkt->setDestAddr(highestPressureBatteryId);
            NetwControlInfo::setControlInfo(aPkt, highestPressureBatteryId);
            sendDelayed(aPkt, 0.05, dataOut);
        }
        if (highestLightBatteryId > -1) {
            ApplPkt* aPkt = new ApplPkt();
            aPkt->setName("measure light");
            aPkt->setDestAddr(highestPressureBatteryId);
            NetwControlInfo::setControlInfo(aPkt, highestPressureBatteryId);
            sendDelayed(aPkt, 0.1, dataOut);
        }
        if (highestHumidityBatteryId > -1) {
            ApplPkt* aPkt = new ApplPkt();
            aPkt->setName("measure humidity");
            aPkt->setDestAddr(highestPressureBatteryId);
            NetwControlInfo::setControlInfo(aPkt, highestPressureBatteryId);
            sendDelayed(aPkt, 0.15, dataOut);
        }

        return;
    }

    if (strcmp(msg->getName(), "estimateResidualRelative") == 0) {
        EV << "Received message not to be forwarded" << endl;
        ApplPkt* Apkt = dynamic_cast<ApplPkt*>(msg);
        if (Apkt != NULL) {
            int srcId = Apkt->getSrcAddr();
            SensorTypeInformation* sti = findNodeById(srcId);
            if (sti != NULL) {
                SimpleBatteryStatsInfo* battStats = dynamic_cast<SimpleBatteryStatsInfo*>(Apkt->getParList().get(0));
                if (battStats != NULL) {
                    sti->residualRelative = battStats->residualRelative;
                }
            }
            incrementCounterSensorNodeAnswers();
        }
        return;
    }

    if (strcmp(msg->getName(), "measuredValue") == 0) {

        ApplPkt* Apkt = dynamic_cast<ApplPkt*>(msg);
        SimpleSensorData* ssd;
        if (Apkt != NULL) {
            //int srcId = Apkt->getSrcAddr();

            //int size = Apkt->getParList().size();

            cObject* parZero = Apkt->getParList().get(0);
            ssd = dynamic_cast<SimpleSensorData*>(parZero);

        } else {

            ssd = new SimpleSensorData("faulty package", -1);

        }

        sensorValues.add(ssd);
        if (sensorValues.size() == sensorSum) {
            cMessage* nMsg = new cMessage;
            nMsg->getParList() = sensorValues;
            sensorValues = *(new cArray);

            ApplPkt* aPkt = new ApplPkt;
            aPkt->getParList() = sensorValues;
            aPkt->setSrcAddr(clusterApp->myNodeId);
            aPkt->setDestAddr(0);
            aPkt->setName("Complete Sensor Data");
            send(aPkt/*, 0.3  + 0.1 * roomId*/, dataOut);

        }

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

ClusterMasterClusterAppl::SensorTypeInformation* ClusterMasterClusterAppl::findNodeById(int nodeNetwAddr) {
    int size = SensorTypeInformationVector.size();
    for (int i = 0; i < size; i++) {
        if (SensorTypeInformationVector.at(i).nodeNetwAddr == nodeNetwAddr) {
            return &SensorTypeInformationVector.at(i);
        }
    }
    return NULL;
}

void ClusterMasterClusterAppl::incrementCounterSensorNodeAnswers() {
    counterSensorNodeAnswers++;
    if (counterSensorNodeAnswers == numChildNodes) {
        scheduleAt(simTime() + 0.0001, InitMeasuringEvent);
        counterSensorNodeAnswers = 0;
    }
}
