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

#ifndef Szenario3Appl_H_
#define Szenario3Appl_H_

#include <omnetpp.h>
#include <BaseModule.h>
#include <Memory.h>
#include <PhyLayer.h>
#include <CustomMatrixApplication.h>

class Szenario3Appl : public CustomMatrixApplication
{
protected:
    int dataOut;
    int dataIn;
    int ctrlOut;
    int ctrlIn;
    int coordinatorNodeAddr;
    int sendSensorDataToMasterIntervall;
    Memory* memory;
    SimpleBattery* battery;
public:
    bool iAmLeafNode;
    int myNetworkAddr;

    Szenario3Appl();
    ~Szenario3Appl();

    cMessage* sendToMaster;

    void initialize(int stage);
    void handleMessage(cMessage* msg);

    void wakeupSleepInit(void);
    void wakeupSleepUpdateTimer(void);
    void wakeupSleepEnterSleep(void);
    void wakeupSleepLeaveSleep(void);
};

#endif /* Szenario3Appl_H_ */
