//***************************************************************************
// * file:        Nic802154_TI_CC2420.ned
// *
// * author:      Jerome Rousselot, Marc Loebbers
// *
// * copyright:   (C) 2008-2010 CSEM SA, Neuchatel, Switzerland.
// *		  	  (C) 2004 Telecommunication Networks Group (TKN) at
// *              Technische Universitaet Berlin, Germany.
// *
// *              This program is free software; you can redistribute it
// *              and/or modify it under the terms of the GNU General Public
// *              License as published by the Free Software Foundation; either
// *              version 2 of the License, or (at your option) any later
// *              version.
// *              For further information see file COPYING
// *              in the top level directory
// *
// * Funding: This work was partially financed by the European Commission under the  
// * Framework 6 IST Project "Wirelessly Accessible Sensor Populations"  
// * (WASP) under contract IST-034963.
// **************************************************************************/

package applicationclusteringimplementations;

import org.mixim.modules.nic.WirelessNicBattery;
import org.mixim.modules.nic.IWirelessNicUpperCtrl;

import org.mixim.base.phyLayer.IWirelessPhy;
import org.mixim.base.modules.IWirelessMac;

import wakeuprecv.WakeupPhyLayerBattery;
import org.mixim.modules.phy.PhyLayerBattery;

import applicationclusteringimplementations.MacLayer.CSMA802154HostStateHandled;

//
// This NIC implements a Texas Instruments CC 2420 802.15.4 network interface card
// using the CSMA protocol as specified in IEEE 802.15.4-2006.
//
//Note: To be able to use this Nic in your simulation you have to copy the file 
//"Nic802154_TI_CC2420_Decider.xml" from "modules/nic/" to your simulation directory.
// @author Jerome Rousselot
//
module Wakeup_Nic802154_TI_CC2420A like IWirelessNicUpperCtrl
{
    parameters:
        string connectionManagerName = default("");   //name of the ConnectionManager module
        //string phyType = default("org.mixim.modules.phy.PhyLayerBattery");
        //string macType = default("CSMA802154HostStateHandled");
        
        double sleepCurrent @unit(mA);
        double rxCurrent @unit(mA);
        double decodingCurrentDelta @unit(mA);
        double txCurrent @unit(mA);
        double setupRxCurrent @unit(mA);
        double setupTxCurrent @unit(mA);
        double rxTxCurrent @unit(mA);
        double txRxCurrent @unit(mA);
                
        // power consumption from boards (at 3.3V)
        double setupWakeupCurrent @unit(mA) = 0.1mA; // 0.021 µA
//        double wakeupCurrent @unit(mA) = 0.1mA; // 0.021 µA
        double wakeupCurrent @unit(mA) = 100mA; // 0.021 µA
//        sleepCurrent         = 0.000021mA; // 0.021 µA
        sleepCurrent         = 21mA; // 0.021 µA
        rxCurrent            = 18.8 mA;
        decodingCurrentDelta = 0 mA;
        txCurrent            = 17.4 mA;
        setupRxCurrent       = 0.6391mA; // 0.002109 W = (ESetupPower+ESetupXtal+ETxCalibrate)/TSetupTx
        setupTxCurrent       = 0.6845mA; // 0.002259 W = (ESetupPower+ESetupXtal+ERxCalibrate)/TSetupRx
        rxTxCurrent          = 18.8 mA; // Upper bound
        txRxCurrent          = 18.8 mA; // idem

        phy.decider = xmldoc("Nic802154_TI_CC2420_Decider.xml");
        //phy.publishRSSIAlways = false;
        phy.headerLength = 48 bit; // ieee 802.15.4                
        phy.thermalNoise = default(-110 dBm);
        // From TI CC1100 datasheet rev. C
        phy.timeSleepToRX = 0.001792 s;
        phy.timeSleepToTX = 0.001792 s;
        phy.timeRXToTX = 0.000192 s;
        phy.timeTXToRX = 0.000192 s;
        phy.timeRXToSleep = 0 s;
        phy.timeTXToSleep = 0 s;

        mac.rxSetupTime = 0.001792 s;
        mac.txPower = default(1 mW);
        
    gates:
        input upperLayerIn; // to upper layers
        output upperLayerOut; // from upper layers
        output upperControlOut; // control information 
        input upperControlIn; // control information 
        input radioIn; // radioIn gate for sendDirect
    
    submodules:
        mac: CSMA802154HostStateHandled {
            @display("p=52,51;i=block/layer");
            @class(CSMA802154HostStateHandled);
        }
        phy: WakeupPhyLayerBattery {
            @display("p=52,125;i=block/process_s");
        }
    connections:
        mac.upperLayerOut --> { @display("ls=black;m=m,25,50,25,0"); } --> upperLayerOut;
        mac.upperLayerIn <-- { @display("ls=black;m=m,15,50,15,0"); } <-- upperLayerIn;
        mac.upperControlOut --> { @display("ls=red;m=m,75,50,75,0"); } --> upperControlOut;
        mac.upperControlIn <-- { @display("ls=red;m=m,85,0,85,0"); } <-- upperControlIn;

        phy.upperLayerOut --> { @display("ls=black;m=m,25,50,25,0"); } --> mac.lowerLayerIn;
        phy.upperLayerIn <-- { @display("ls=black;m=m,15,50,15,0"); } <-- mac.lowerLayerOut;
        phy.upperControlOut --> { @display("ls=red;m=m,75,50,75,0"); } --> mac.lowerControlIn;
        phy.upperControlIn <-- { @display("ls=red;m=m,85,0,85,0"); } <-- mac.lowerControlOut;

        radioIn --> phy.radioIn;
}

