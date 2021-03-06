//
// Generated file, do not edit! Created by opp_msgc 4.3 from GenericPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include "ce-clusterApplication.h"
#include "ce-application.h"
#include "ce-data.h"
//#include "MiXiMDefs.h"
//#include "BaseModule.h"
#include <PhyLayerBattery.h>
#include <SimpleBattery.h>
#include <WakeupPhyUtils.h>

/****************************************************************************
 * WakeUp Sleep
 ****************************************************************************/
void MYCLASS wakeupSleepInit(void)
{
    if (sleepTimer->isScheduled())
    {
        myBaseModule->cancelEvent(sleepTimer);
    }
    myBaseModule->scheduleAt(simTime() + ((sleepTimeout) * 0.001) + uniform(0, 0.001), sleepTimer);


}

void MYCLASS wakeupSleepUpdateTimer(void)
{

    if (sleepTimer->isScheduled())
    {
        myBaseModule->cancelEvent(sleepTimer);
    }
    myBaseModule->scheduleAt(simTime() + ((sleepTimeout) * 0.001) + uniform(0, 0.001), sleepTimer);


    /*
    clusterApplicationUpdateTimer(
            TIMER_ID_WAKEUP_SLEEP_TIMER,
            TIMER_TYPE_OFFSET,
            sleepTimeout
    );
    */
}

void MYCLASS wakeupSleepEnterSleep(void)
{
    EV << "----------> Entering Sleep Mode" << endl;
    if (sleepTimer->isScheduled())
    {
        myBaseModule->cancelEvent(sleepTimer);
    }
    myBaseHost->getDisplayString().setTagArg("b", 3, "white");
    isInSleepMode = true;
    otherNodesInSleepMode = true;
/*
    clusterApplicationUpdateTimer(
            TIMER_ID_WAKEUP_SLEEP_TIMER,
            TIMER_TYPE_DELETE,
            0
    );
    */
    //TODO
    myPhyLayerBattery->setRadioState(WakeupMiximRadio::SLEEP);

}

void MYCLASS wakeupSleepLeaveSleep(void)
{
    EV << "----------> Leaving Sleep Mode" << endl;
    if (sleepTimer->isScheduled())
    {
        myBaseModule->cancelEvent(sleepTimer);
    }
    myBaseModule->scheduleAt(simTime() + (( sleepTimeout) * 0.001) + uniform(0, 0.001), sleepTimer);



    //myPhyLayerBattery->setRadioState(0);
    int radioState = myPhyLayerBattery->getRadioState();
    if (radioState == WakeupMiximRadio::SLEEP) {
        myPhyLayerBattery->setRadioState(WakeupMiximRadio::RX);
        myBaseHost->getDisplayString().setTagArg("b", 3, "yellow");
        isInSleepMode = true;
        wakeupSleepUpdateTimer();
    }
}

