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

#ifndef CUSTOMWISEROUTE_H_
#define CUSTOMWISEROUTE_H_

#include <WiseRoute.h>
#include <omnetpp.h>
#include <DummyRoutePkt_m.h>
#include "vector"
#include "ApplPkt_m.h"

#include <NoApplicationClusteringAppl.h>
#include <Szenario3Appl.h>

class CustomWiseRoute : public WiseRoute
{

public:
    CustomWiseRoute();

    //special omnet methods

    void initialize(int stage);
    void finish();
    void handleMessage(cMessage* msg);

    //methods for initialization of the routeTable

    void convertTreeToRouteTable();
    void makeEntry(int targetAddr, int nextAddr);
    void proccessChildNodes(int routeAddr, int father);

    struct AdjListElement {
        int value = -1;
        AdjListElement* next = NULL;
    };

    AdjListElement* getChildNodes(int nodeId);
    AdjListElement* findListEnd(AdjListElement*);
    void insertList(int index, int value);
    bool containsElement(AdjListElement* elem, int value);
    bool isAddrFatherOrChild(int addr);

    int* routeTree;
    AdjListElement* routeTreeAdjList;
    int numHosts;
    bool isRoot;
    bool isLeaf;
    bool active;
    const char* bcName;

protected:
    enum messagesTypes {
        UNKNOWN=0,
        DATA,
        ROUTE_FLOOD,
        SEND_ROUTE_FLOOD_TIMER,
        //added
        FORWARD_DELAYED
    };

    cArray* MessagesToBeForwarded;
    cMessage* forwardMessagesSelfMsg;
    int sendingIntervall;

    NoApplicationClusteringAppl* appl;
    Szenario3Appl* appl2;

    void sendToNeighbor(cMessage* msg, LAddress::L3Type &finalDestAddr, LAddress::L3Type &nextHopAddr, LAddress::L3Type &initialSrcAddr, LAddress::L3Type &srcAddr);
    void forward(ApplPkt* msg, LAddress::L3Type);
    void forward(cMessage* msg, LAddress::L3Type);
    std::vector<int> lastBroadcastId;

    bool stats, trace;

    int networkID;  // the network to which we belong
    int ip;  // the network to which we belong

    void handleSelfMsg(cMessage* msg);
    void handleLowerMsg(cMessage* msg);
    void handleUpperControl(cMessage *msg);
    void handleLowerControl(cMessage *msg);
    void handleUpperMsg(cMessage* msg);
    netwpkt_ptr_t encapsMsg(cPacket *appPkt);
    cPacket* decapsMsg(netwpkt_ptr_t msg);

    void handleHostState(const HostState& state);
};

#endif /* CUSTOMWISEROUTE_H_ */
