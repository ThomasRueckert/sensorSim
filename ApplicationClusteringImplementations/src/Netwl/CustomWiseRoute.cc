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

#include <CustomWiseRoute.h>

#include <limits>
#include <algorithm>
#include <cassert>
#include <MyTestApplication.h>
#include <FindModule.h>
#include <NoApplicationClusteringAppl.h>

#include "NetwControlInfo.h"
#include "MacToNetwControlInfo.h"
#include "ArpInterface.h"
#include "WiseRoutePkt_m.h"
#include "SimTracer.h"
#include "SensorNode.h"
#include "exception"
#include "GenericPacket_m.h"
#include "WakeUpPacket_m.h"
#include <string>

#include "exception"

using std::make_pair;

Define_Module(CustomWiseRoute);

CustomWiseRoute::CustomWiseRoute() : WiseRoute()
        , bcName("LAddress::L3BROADCAST")
        , stats(false)
        , trace(false)
        , networkID(-1)
        , ip(-1)
{
    MessagesToBeForwarded = new cArray;
    forwardMessagesSelfMsg = NULL;
    sendingIntervall = 0;
}

void CustomWiseRoute::initialize(int stage) {
    WiseRoute::initialize(stage);
    if (stage == 0) {

        isRoot = false;
        isLeaf = false;
        active = true;

        trace = par("trace");
        networkID = par("networkID");

        forwardMessagesSelfMsg = new cMessage;
        forwardMessagesSelfMsg->setKind(FORWARD_DELAYED);
        NoApplicationClusteringAppl* appl = FindModule<NoApplicationClusteringAppl*>::findSubModule(findHost());
        if (appl != NULL) {
            sendingIntervall = appl->par("sendingIntervall");
        }
        if (appl != NULL) {
            //scheduleAt(simTime() + sendingIntervall + 5 + (myNetwAddr*0.1), forwardMessagesSelfMsg);
        }
    }
    if (stage == 1) {

        SensorNode* node = (SensorNode*) this->getParentModule();
        const char *vstr = node->par("routeTree").stringValue();
        std::vector<std::string> v = cStringTokenizer(vstr).asVector();
        int max = v.size();
        numHosts = max;

        routeTree = new int[max];
        routeTreeAdjList = new AdjListElement[max];

        for (int i = 0; i < max; i++) {
            //routeTree[i] = std::stoi(v.at(i));
            routeTree[i] = atoi( v[i].c_str() );
            routeTreeAdjList->value = -1;
            //EV << routeTree[i] << endl;
        }

        for (int child = 0; child < max; child++) {
            int father = routeTree[child];
            if (child != father) {
                insertList(father, child);
            }

        }

        convertTreeToRouteTable();

        //output routing tables
        EV << "Routing table for " << myNetwAddr << endl;
        for (int i = 0; i < numHosts; i++) {
            EV << "target: " << i << ", next: " << getRoute(i) << endl;
        }

    }
}

void CustomWiseRoute::handleMessage(cMessage* msg)
{
    EV << "Wiseroute received Message: " << msg->getName() << endl;

    if (msg->isSelfMessage()) {
        handleSelfMsg(msg);
    } else if(msg->getArrivalGateId()==upperLayerIn) {
        recordPacket(PassedMessage::INCOMING,PassedMessage::UPPER_DATA,msg);
        handleUpperMsg(msg);
    } else if(msg->getArrivalGateId()==upperControlIn) {
        recordPacket(PassedMessage::INCOMING,PassedMessage::UPPER_CONTROL,msg);
        handleUpperControl(msg);
    } else if(msg->getArrivalGateId()==lowerControlIn){
        recordPacket(PassedMessage::INCOMING,PassedMessage::LOWER_CONTROL,msg);
        handleLowerControl(msg);
    } else if(msg->getArrivalGateId()==lowerLayerIn) {
        recordPacket(PassedMessage::INCOMING,PassedMessage::LOWER_DATA,msg);
        handleLowerMsg(msg);
    }
    else if(msg->getArrivalGateId()==-1) {
        /* Classes extending this class may not use all the gates, f.e.
         * BaseApplLayer has no upper gates. In this case all upper gate-
         * handles are initialized to -1. When getArrivalGateId() equals -1,
         * it would be wrong to forward the message to one of these gates,
         * as they actually don't exist, so raise an error instead.
         */
        opp_error("No self message and no gateID?? Check configuration.");
    } else {
        /* msg->getArrivalGateId() should be valid, but it isn't recognized
         * here. This could signal the case that this class is extended
         * with extra gates, but handleMessage() isn't overridden to
         * check for the new gate(s).
         */
        opp_error("Unknown gateID?? Check configuration or override handleMessage().");
    }
}

/**
 * check if a given value (node id) is element of the given list
 * => check if the given node id is a child of the node's list
 */
bool CustomWiseRoute::containsElement(AdjListElement* elem, int value) {
    if (value == elem->value) {
        return true;
    }
    if (elem->next == NULL) {
        return false;
    }
    return containsElement(elem->next, value);
}

/**
 * when creating or updating the adjazenz list use this function to insert new elements
 *
 * @var int index is the position in the array routeTreeAdjList to insert
 * @var int value is the the id of the child node (of the father with id index) to be inserted
 */
void CustomWiseRoute::insertList(int index, int value) {
    AdjListElement* last = findListEnd(&routeTreeAdjList[index]);
    if (last->value != -1) {
        AdjListElement* newLast = new AdjListElement;
        last->next = newLast;
        last = newLast;
    }
    last->value = value;
}

/**
 * find the last element of a given list (AdjListElement)
 */
CustomWiseRoute::AdjListElement* CustomWiseRoute::findListEnd(AdjListElement* elem) {
    if (elem->next == NULL) {
        return elem;
    }
    return findListEnd(elem->next);
}

/**
 * add entry to the routeTable
 *
 * @var int targetAddr is the target node to be routed
 * @var int nextAddr is the next hop to be done to reach the target
 */
void CustomWiseRoute::makeEntry(int targetAddr, int nextAddr) {
    WiseRoute::tRouteTableEntry newEntry;
    newEntry.nextHop = nextAddr;
    routeTable.insert(make_pair(targetAddr, newEntry));
}

/**
 * check if the given address belongs to a node which is either my father node or one of my child nodes
 */
bool CustomWiseRoute::isAddrFatherOrChild(int addr) {
    if (isLeaf) {

    } else {
        AdjListElement* childs = getChildNodes(myNetwAddr);
        do {
            if (childs->value == addr) {
                return true;
            }

            childs = childs->next;
        } while (childs != NULL);
    }
    if (isRoot) {

    } else {
        int fatherAddress = routeTree[myNetwAddr];
        if (fatherAddress == addr) {
            return true;
        }
    }
    return false;
}

/**
 * convert the general routing tree into the node specific routing table
 */
void CustomWiseRoute::convertTreeToRouteTable() {
    //routeTree;
    //routeTable;
    //myNetwAddr;
    NoApplicationClusteringAppl* appl = FindModule<NoApplicationClusteringAppl*>::findSubModule(findHost());
    if (appl != NULL) {
        appl->myNetworkAddr = myNetwAddr;
    }

    //list of childs of the node i are inside routeTreeAdjList[i]
    int fatherAddr = routeTree[myNetwAddr];

    if (routeTreeAdjList[myNetwAddr].value == -1) {
        //no children
        //this means all other nodes can be accessed through the father
        isLeaf = true;
        if (appl != NULL) {
            appl->iAmLeafNode = true;
        }
    } else {
        //proccess the children
        AdjListElement* currentElement = &routeTreeAdjList[myNetwAddr];

        do {
            int child = currentElement->value;
            makeEntry(child, child);

            proccessChildNodes(child, child);
            currentElement = currentElement->next;
        } while (currentElement != NULL);
    }

    if (myNetwAddr == fatherAddr) {
        //no father -> root
        isRoot = true;
    } else {
        //process all nodes that aren't children
        for (int i = 0; i < numHosts; i++) {
            if (i == myNetwAddr) {
                makeEntry(i, i);
                continue;
            }
            if (!containsElement(&routeTreeAdjList[myNetwAddr], i)) {
                makeEntry(i, routeTree[myNetwAddr]);
            }
        }
    }

}

/**
 * for a given child (routeAddr) the nodes of the entire subtree must be accessed through
 * this given child node
 */
void CustomWiseRoute::proccessChildNodes(int routeAddr, int father) {
    AdjListElement* currentElement = &routeTreeAdjList[routeAddr];

    do {
        int child = currentElement->value;

        if (child == -1) {
            break;
        }

        makeEntry(child, father);

        //recursive
        proccessChildNodes(child, father);

        currentElement = currentElement->next;
    } while (currentElement != NULL);
}

CustomWiseRoute::AdjListElement* CustomWiseRoute::getChildNodes(int nodeId) {
    return &routeTreeAdjList[nodeId];
}

void CustomWiseRoute::finish() {

    WiseRoute::finish();
}

void CustomWiseRoute::handleSelfMsg(cMessage* msg)
{
    if (msg->getKind() == SEND_ROUTE_FLOOD_TIMER) {
        // Send route flood packet and restart the timer
        WiseRoutePkt* pkt = new WiseRoutePkt("route-flood", ROUTE_FLOOD);
        pkt->setByteLength(headerLength);
        pkt->setInitialSrcAddr(myNetwAddr);
        pkt->setFinalDestAddr(LAddress::L3BROADCAST);
        pkt->setSrcAddr(myNetwAddr);
        pkt->setDestAddr(LAddress::L3BROADCAST);
        pkt->setNbHops(0);
        floodTable.insert(make_pair(myNetwAddr, floodSeqNumber));
        pkt->setSeqNum(floodSeqNumber);
        floodSeqNumber++;
        pkt->setIsFlood(1);
        setDownControlInfo(pkt, LAddress::L2BROADCAST);
        sendDown(pkt);
        nbFloodsSent++;
        nbRouteFloodsSent++;
        scheduleAt(simTime() + routeFloodsInterval + uniform(0, 1), routeFloodTimer);
    } else if (msg->getKind() == FORWARD_DELAYED) {

        int index = atoi(msg->getName());
        if (MessagesToBeForwarded->exist(index)) {
            cMessage* forwardMessage = check_and_cast<cMessage*>(MessagesToBeForwarded->remove(index));

            if (forwardMessage != NULL) {

                WiseRoutePkt* pkt = check_and_cast<WiseRoutePkt*>(forwardMessage);

                //pkt->setFinalDestAddr(LAddress::L3BROADCAST);
                WiseRoutePkt* copyPkt = pkt->dup();
                //sendUp(decapsMsg(pkt));

                //forward broadcast
                LAddress::L3Type finalDestAddr = copyPkt->getFinalDestAddr();
                LAddress::L3Type initialSrcAddr = copyPkt->getInitialSrcAddr();
                LAddress::L3Type destAddr = copyPkt->getDestAddr();
                LAddress::L3Type srcAddr = copyPkt->getSrcAddr();

                EV << "-------------------- I am NODE " << myNetwAddr << ". FORWARDING" << " message." << endl;

                //pkt->setFinalDestAddr();
                NetwControlInfo::setControlInfo(copyPkt, finalDestAddr);
                forward(copyPkt, -2);
            }
        }
    }
    else {
        EV << "WiseRoute - handleSelfMessage: got unexpected message of kind " << msg->getKind() << endl;
        delete msg;
    }
}

//from NetworkLayer2

/**
 * handle messages in different ways (and restore final destination)
 * -> if only i should receive -> get the final destination (is it my own address? -> appl layer)
 * -> if it was meant to be a broadcast -> set the l3 bc address
 */
void CustomWiseRoute::handleLowerMsg(cMessage* msg) {

    if (active) {

        if (strcmp(msg->getName(), "WakeUpReceiverPacket") == 0) {

            WiseRoutePkt* pkt = check_and_cast<WiseRoutePkt*>(msg);
            WiseRoutePkt* copyPkt = pkt->dup();

            //pkt->setFinalDestAddr(LAddress::L3BROADCAST);

            sendUp(decapsMsg(pkt));

            //forward broadcast
            LAddress::L3Type finalDestAddr = copyPkt->getFinalDestAddr();
            LAddress::L3Type initialSrcAddr = copyPkt->getInitialSrcAddr();
            LAddress::L3Type destAddr = copyPkt->getDestAddr();
            LAddress::L3Type srcAddr = copyPkt->getSrcAddr();

            WakeUpPacket* wuPkt = new WakeUpPacket;
            wuPkt->setDestAddr(LAddress::L3BROADCAST);
            wuPkt->setSrcAddr(srcAddr);
            wuPkt->setName("WakeUpReceiverPacket");
            NetwControlInfo::setControlInfo(wuPkt, LAddress::L3BROADCAST);

            if (LAddress::isL3Broadcast(finalDestAddr)) {
                //pkt->setFinalDestAddr();
                //NetwControlInfo::setControlInfo(copyPkt, LAddress::L3BROADCAST);

                EV << "-------------------- I am NODE " << myNetwAddr << ". FORWARDING WakeUpReceiverPacket." << endl;

                forward(wuPkt, srcAddr);
            }

        } else if (strcmp(msg->getName(), "sensor data") == 0) {
            //only store the message
            //it will be forwarded later (triggered by self message forwardMessagesSelfMsg)
            WiseRoutePkt* pkt = check_and_cast<WiseRoutePkt*>(msg);
            LAddress::L3Type finalDestAddr = pkt->getFinalDestAddr();
            if (myNetwAddr == finalDestAddr) {
                sendUp(decapsMsg(pkt));
                EV << "-------------------- I am NODE " << myNetwAddr << ". GOT FORWARDED MESSAGES AND I AM FINAL RECEIVER." << endl;
            } else {
                int index = MessagesToBeForwarded->add(msg);
                NoApplicationClusteringAppl* appl = FindModule<NoApplicationClusteringAppl*>::findSubModule(findHost());
                if (appl != NULL) {
                    cMessage* forwardMsgEvent = new cMessage;
                    forwardMsgEvent->setKind(FORWARD_DELAYED);

                    std::stringstream strs;
                    strs << index;
                    std::string temp_str = strs.str();
                    char const* char_type = temp_str.c_str();

                    forwardMsgEvent->setName(char_type);

                    scheduleAt(simTime() + 0.5, forwardMsgEvent);
                }
                EV << "-------------------- I am NODE " << myNetwAddr << ". GOT MESSAGE TO BE FORWARDED LATER. WAITING FOR MORE MESSAGES FIRST." << endl;
            }
        } else {
            WiseRoutePkt* pkt = check_and_cast<WiseRoutePkt*>(msg);

            //pkt->setFinalDestAddr(LAddress::L3BROADCAST);
            WiseRoutePkt* copyPkt = pkt->dup();
            sendUp(decapsMsg(pkt));

            //forward broadcast
            LAddress::L3Type finalDestAddr = copyPkt->getFinalDestAddr();
            LAddress::L3Type initialSrcAddr = copyPkt->getInitialSrcAddr();
            LAddress::L3Type destAddr = copyPkt->getDestAddr();
            LAddress::L3Type srcAddr = copyPkt->getSrcAddr();

            if (LAddress::isL3Broadcast(finalDestAddr)) {
                //pkt->setFinalDestAddr();
                NetwControlInfo::setControlInfo(copyPkt, LAddress::L3BROADCAST);

                EV << "-------------------- I am NODE " << myNetwAddr << ". FORWARDING" << " message." << endl;

                forward(copyPkt, srcAddr);
            }
        }



    } else {
        delete msg;
    }
}

void CustomWiseRoute::handleUpperControl(cMessage *msg) {
    delete msg;
}


void CustomWiseRoute::handleLowerControl(cMessage *msg) {
    if (active) {
        sendControlUp(msg);
    } else {
        delete msg;
    }
}

/**
 * check if target address is broadcast -> send one message to each child and father node (done)
 * transform any other target address (final destination -> next hop)
 */
void CustomWiseRoute::handleUpperMsg(cMessage* msg) {
    if (active) {

        forward(msg, -2);

    } else {
        delete msg;
    }
}

void CustomWiseRoute::forward(ApplPkt* msg, LAddress::L3Type srcAddr) {
    EV << "Wrong package, not forwarding" << endl;
}

void CustomWiseRoute::forward(cMessage* msg, LAddress::L3Type srcAddr) {

    /**
     * transform destination address?
     * handle broadcast
     */

    EV << "I am NODE " << myNetwAddr<< "-------------------- I am NODE ---------" << endl;

    if (msg->getName() == NULL || msg->getName() == "" || msg->getName()[0] == '\0') {
        EV << "          received msg without name. Renaming it to 'unnamed packet'." << endl;
        msg->setName("unnamed packet");
    } else {
        EV << "          received msg with name: " << msg->getName() << endl;
    }


    //sendDown(encapsMsg(check_and_cast<cPacket*>(msg)));

    LAddress::L3Type finalDestAddr;
    LAddress::L3Type nextHopAddr;
    LAddress::L3Type initialSrc;
    cObject*         cInfo = msg->removeControlInfo();
    lastBroadcastId.push_back(msg->getId());
    LAddress::L3Type L3myNetwAddr = myNetwAddr;

        if ( cInfo == NULL ) {
            EV << "WiseRoute warning: Application layer did not specifiy a destination L3 address\n"
               << "\tusing broadcast address instead\n";
            finalDestAddr = LAddress::L3BROADCAST;
        }
        else {
            EV <<"WiseRoute: CInfo removed, netw addr="<< NetwControlInfo::getAddressFromControlInfo( cInfo ) <<endl;
            finalDestAddr = NetwControlInfo::getAddressFromControlInfo( cInfo );
            delete cInfo;
        }

    if (LAddress::isL3Broadcast(finalDestAddr) || srcAddr >= 0) {
        //nextHopAddr = LAddress::L3BROADCAST;
        //

        if (srcAddr != -2) {
            if (strcmp(msg->getName(), "WakeUpReceiverPacket") == 0) {
                WakeUpPacket* wpkt = check_and_cast<WakeUpPacket*>(msg);
                initialSrc = wpkt->getSrcAddr();
            } else {
                WiseRoutePkt* wpkt = check_and_cast<WiseRoutePkt*>(msg);
                initialSrc = wpkt->getInitialSrcAddr();
            }
        } else {
            initialSrc = L3myNetwAddr;
        }

        //SEND TO CHILDREN AND FATHER

        //child list
        AdjListElement* childs = getChildNodes(myNetwAddr);

        //father (from array)
        int fatherAddress = routeTree[myNetwAddr];

        //send to all direct children
        std::vector<int> children;
        do {
            if (childs->value != -1) {

                children.push_back(childs->value);
                cMessage* newMsg = msg->dup();

                //NetwControlInfo::setControlInfo(newMsg, LAddress::L3BROADCAST);
                lastBroadcastId.push_back(msg->getId());

                nextHopAddr = childs->value;
                sendToNeighbor(newMsg, finalDestAddr, nextHopAddr, initialSrc, srcAddr);

            }

            childs = childs->next;

        } while (childs != NULL);

        //send to father
        nextHopAddr = fatherAddress;

        if (fatherAddress == myNetwAddr) {
            delete msg;
            return;
        }

        sendToNeighbor(msg, finalDestAddr, nextHopAddr, initialSrc, srcAddr);

    } else {
        nextHopAddr = getRoute(finalDestAddr, true);
        if (srcAddr == -2) {
            initialSrc = myNetwAddr;
        }
        sendToNeighbor(msg, finalDestAddr, nextHopAddr, initialSrc, srcAddr);
    }
}

void CustomWiseRoute::sendToNeighbor(cMessage* msg, LAddress::L3Type &finalDestAddr, LAddress::L3Type &nextHopAddr, LAddress::L3Type &initialSrcAddr, LAddress::L3Type &srcAddr) {

    //außer BC
    if (!LAddress::isL3Broadcast(nextHopAddr) && nextHopAddr == srcAddr) {
        delete msg;
        return;
    }

    EV << "Nexthop  :" << nextHopAddr << "-------------------- I am NODE ---------" << endl;

    LAddress::L2Type nextHopMacAddr;
    const char *name;
    if (strcmp(msg->getName(), "") == 0) {
        name = bcName;
    } else {
        name = msg->getName();
    }
    WiseRoutePkt* pkt = new WiseRoutePkt(name, DATA);
    pkt->setByteLength(headerLength);
    pkt->setFinalDestAddr(finalDestAddr);
    pkt->setInitialSrcAddr(initialSrcAddr);
    pkt->setSrcAddr(myNetwAddr);
    pkt->setDestAddr(nextHopAddr);
    pkt->setNbHops(0);
    pkt->setIsFlood(0);
    nbPureUnicastSent++;
    nextHopMacAddr = arp->getMacAddr(nextHopAddr);
    setDownControlInfo(pkt, nextHopMacAddr);
    assert(static_cast<cPacket*>(msg));
    pkt->encapsulate(static_cast<cPacket*>(msg));
    cArray *parlist = msg->getParList().dup();

    int i = 0;
    while (parlist->exist(i)) {
        pkt->getParList().add(parlist->get(i));
        i++;
    }

    sendDown(pkt);
    nbDataPacketsSent++;
}

CustomWiseRoute::netwpkt_ptr_t CustomWiseRoute::encapsMsg(cPacket *appPkt) {
    if (active) {
        LAddress::L2Type macAddr;
        LAddress::L3Type netwAddr;


        debugEV <<"in encaps...\n";
        DummyRoutePkt *pkt = new DummyRoutePkt(appPkt->getName(), appPkt->getKind());
        pkt->setBitLength(headerLength);

        cObject* cInfo = appPkt->removeControlInfo();

        if(cInfo == NULL){
          EV << "warning: Application layer did not specifiy a destination L3 address\n"
           << "\tusing broadcast address instead\n";
          netwAddr = LAddress::L3BROADCAST;
        } else {
          //debugEV <<"CInfo removed, netw addr="<< NetwControlInfo::getAddressFromControlInfo( cInfo ) << endl;
          netwAddr = NetwControlInfo::getAddressFromControlInfo( cInfo );
          delete cInfo;
        }

        pkt->setNetworkID(networkID);
        pkt->setSrcAddr(myNetwAddr);
        pkt->setDestAddr(netwAddr);
        //debugEV << " netw "<< myNetwAddr << " sending packet" <<endl;
        if(LAddress::isL3Broadcast(netwAddr)) {
    //        debugEV << "sendDown: nHop=L3BROADCAST -> message has to be broadcasted"
    //           << " -> set destMac=L2BROADCAST\n";
            macAddr = LAddress::L2BROADCAST;
        }
        else{
            macAddr = arp->getMacAddr(netwAddr);



        }

        setDownControlInfo(pkt, macAddr);

        //encapsulate the application packet
        pkt->encapsulate(appPkt);
        debugEV <<" pkt encapsulated\n";
        return pkt;
    } else {
        delete appPkt;
    }
}

cPacket* CustomWiseRoute::decapsMsg(netwpkt_ptr_t msg) {
    if (active) {
        cPacket *m = msg->decapsulate();
        setUpControlInfo(m, msg->getSrcAddr());
            // delete the netw packet
        delete msg;
        return m;
    } else {
        delete msg;
    }
}

void CustomWiseRoute::handleHostState(const HostState& state) {
    if(notAffectedByHostState)
        return;

    if(state.get() != HostState::ACTIVE) {
        active = false;
    } else {
        active = true;
    }
}
