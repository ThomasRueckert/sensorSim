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

package applicationclusteringimplementations;

import sensortechnology.src.SensorNode.SensorNode;
import inet.base.NotificationBoard;
import org.mixim.modules.application.SensorApplLayer;
import org.mixim.modules.node.WirelessNodeBatteryNetwl;
import org.mixim.modules.power.battery.SimpleBattery;

import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.Processor.*;
import sensortechnology.src.SensorNode.Memory.*;
import org.mixim.modules.node.WirelessNodeBatteryPlusTran;

import org.mixim.modules.power.battery.BatteryStats;
import org.mixim.modules.power.battery.SimpleBattery;

import org.mixim.modules.nic.IWirelessNicUpperCtrl;
import org.mixim.base.modules.IBaseArp;
import org.mixim.base.modules.IBaseApplLayer;
import org.mixim.base.modules.IBaseNetwLayer;

//
// compound module for a sensor node with wakeup receiver using the DicePhyMacHost
// this module is similar to the DicePhyMacHost (but wakeup and sensor functionality is added)
//
module Sensor_Wakeup_DicePhyMacHost
{
    parameters:
        //route tree builds the networks routing as a tree, but stored as an array
        //the position in the array refers to the id of the node and the value at
        //this position must be the father of the node inside the routing tree
        //the root node inside the tree has it's own id as father value
        //
        //for example:
        //routeTree = 2 2 2
        //builds the following tree:
        //     2
        //   /  \
        //  0   1
        //
        //@see CustomWiseRoute::convertTreeToRouteTable() for more information about how
        //the conversion is done
        string routeTree;
              
		//--------------- BEGIN SENSOR ---------------
        //these parameters are generated automatically, from parent module, or via ini-file
        int sensingIntervall = default(0s) @unit(s);
        int shiftProcessorModeNormalIntervall = default(0s) @unit(s); 
		int shiftProcessorModePowerSavingIntervall = default(0s) @unit(s);
		int shiftProcessorModeHighPerformanceIntervall = default(0s) @unit(s);
        int collectStatisticsIntervall = default(0s) @unit(s);
        int readAndClearStorageIntervall = default(0s) @unit(s);
        bool noisy = default(false);
        
        double dataBandwidth = default(0bps) @unit(bps);
        double controlBandwidth = default(0bps) @unit(bps);
        
        //set this and set it to true to generate all sensors randomly
        bool allSensorsRandom = true;
        bool hasTemperatureSensor = default(false);
        bool hasHumiditySensor = default(false);
        bool hasPressureSensor = default(false);
        bool hasLightSensor = default(false);

        int numSensors = default(0);
        int numSensorModules = 4;
        //memory, processor
        //calculate number of energie accounts from sensor 
        int numDevices = (
        		 (hasTemperatureSensor ? 1 : 1) 
            	+(hasHumiditySensor ? 1 : 0)
            	+(hasPressureSensor ? 1 : 0)
            	+(hasLightSensor ? 1 : 0)
        	) * numSensorModules //calculate number of energie accounts from sensor 
        	+ 2 //memory, processor
        	+ 2;//physical layer, sensornode
        int numHosts;
        //@class("SensorNode");
        @class(SensorNode);
        //these are used to draw the overview of the model
        bool fakeProcessor = false;
        @display("bgb=447,450;i=block/ifcard");

        batteryStats.detail = default(false);
        batteryStats.timeSeries = default(false);

        battery.nominal = default(1000 mAh);
        battery.capacity = default(battery.nominal);
        battery.voltage = default(3 V);
        battery.resolution = default(60 s);
        battery.publishDelta = default(1);
        battery.publishTime = default(battery.resolution);
        
        double normalRatio;
		double powerSavingRatio;
		double highPerformanceRatio;
		//--------------- END SENSOR ---------------
		
		//--------------- BEGIN DICE ---------------        
        //--------------- END DICE ---------------
        
        //--------------- BEGIN WAKEUP ---------------
		//--------------- END WAKEUP ---------------
    
    	//--------------- BEGIN WIRELESSNODE ---------------
    	string networkType = default("CustomWiseRoute");       //type of the network layer
        string transportType = default("");       //type of the transport layer
        string sessionType = default("");                    //type of the session layer
        string presentationType = default("");               //type of the presentation layer
        string applicationType = default("MatrixApplication");  //type of the application layer
        string mobilityType = default("StationaryMobility"); //type of the mobility module
        string arpType = default("ArpHost");                 //type of address resolution module
        //string nicType = default("Wakeup_Nic802154_TI_CC2420A");
        @node();
		//--------------- END WIRELESSNODE ---------------
		
		appl.nodeAddr = arp.offset;
		appl.nodeAddr = arp.offset;
		
	gates:
        input radioIn; // gate for sendDirect
		
    submodules:
        //--------------- BEGIN DICE ---------------
        batteryStats: BatteryStats {
            @display("p=140,240;i=block/table,#FF8040");
        }
        battery: SimpleBattery {
            @display("p=140,170;i=block/plug,#FF8000");
            numDevices = numDevices;
        }
        //--------------- END DICE ---------------
        
        //--------------- BEGIN SENSOR ---------------
        TemperatureSensor: TemperatureSensor if hasTemperatureSensor {
            @display("p=275,51");
            dataBandwidth = dataBandwidth;
            controlBandwidth = controlBandwidth;
        }
        HumiditySensor: HumiditySensor if hasHumiditySensor {
            @display("p=275,120");
            dataBandwidth = dataBandwidth;
            controlBandwidth = controlBandwidth;
        }
        PressureSensor: PressureSensor if hasPressureSensor {
            @display("p=275,190");
            dataBandwidth = dataBandwidth;
            controlBandwidth = controlBandwidth;
        }
        LightSensor: LightSensor if hasLightSensor {
            @display("p=275,260");
            dataBandwidth = dataBandwidth;
            controlBandwidth = controlBandwidth;
        }
        Memory: Memory {
            @display("p=400,51");
        }
        //Processor is created inside the C++-Class in order to create the gates to the
        //different sensors dynamically by the input
        Processor: ExampleProcessor if fakeProcessor {
            @display("p=400,159");
        }
        //--------------- END SENSOR ---------------
        		
		//--------------- BEGIN WIRELESSNODE ---------------
    	arp: <arpType> like IBaseArp {
                @display("p=140,100;i=block/network2");
        }
        mobility: <mobilityType> like inet.mobility.IMobility {
            parameters:
                @display("p=140,30;i=block/cogwheel");
        }
        nic: Wakeup_Nic802154_TI_CC2420A {
            parameters:
                @display("p=70,380;i=block/wrxtx,#008000");
        }
        // OSI network layer
        netwl: <networkType> like IBaseNetwLayer {
            parameters:
                @display("p=70,310;i=block/layer");
        }
        // OSI transport layer if defined
        tranl: <transportType> like IBaseNetwLayer if transportType != "" {
            parameters:
                @display("p=70,240;i=block/layer");
        }
        // OSI session layer if defined
        sessl: <sessionType> like IBaseNetwLayer if sessionType != "" {
            parameters:
                @display("p=70,170;i=block/layer");
        }
        // OSI presentation layer if defined
        presl: <presentationType> like IBaseNetwLayer if presentationType != "" {
            parameters:
                @display("p=70,100;i=block/layer");
        }
        appl: <applicationType> like IBaseApplLayer if applicationType != "" {
            parameters:
                @display("p=70,30;i=app");
        }
		//--------------- END WIRELESSNODE ---------------
        
    connections:
        
        nic.upperLayerOut --> netwl.lowerLayerIn;
        nic.upperLayerIn <-- netwl.lowerLayerOut;
        nic.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> netwl.lowerControlIn;
        nic.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- netwl.lowerControlOut;

        //# connections of transport, session, and presentation layer depending of the
        //# existence
        if (transportType != "") {
            //# transport layer exists, so we can connect netwl <--> tranl
            netwl.upperLayerOut --> tranl.lowerLayerIn;
            netwl.upperLayerIn <-- tranl.lowerLayerOut;
            netwl.upperControlOut --> tranl.lowerControlIn;
            netwl.upperControlIn <-- tranl.lowerControlOut;
        }
        if (sessionType != "" && transportType == "") {
            //# session layer exists but no transport layer, so we can connect netwl <--> sessl
            netwl.upperLayerOut --> sessl.lowerLayerIn;
            netwl.upperLayerIn <-- sessl.lowerLayerOut;
            netwl.upperControlOut --> sessl.lowerControlIn;
            netwl.upperControlIn <-- sessl.lowerControlOut;
        }
        if (sessionType != "" && transportType != "") {
            //# session layer and transport layer exists, so we can connect tranl <--> sessl
            tranl.upperLayerOut --> sessl.lowerLayerIn;
            tranl.upperLayerIn <-- sessl.lowerLayerOut;
            tranl.upperControlOut --> sessl.lowerControlIn;
            tranl.upperControlIn <-- sessl.lowerControlOut;
        }
        if (presentationType != "" && sessionType == "" && transportType == "") {
            netwl.upperLayerOut --> presl.lowerLayerIn;
            netwl.upperLayerIn <-- presl.lowerLayerOut;
            netwl.upperControlOut --> presl.lowerControlIn;
            netwl.upperControlIn <-- presl.lowerControlOut;
        }
        if (presentationType != "" && sessionType != "") {
            sessl.upperLayerOut --> presl.lowerLayerIn;
            sessl.upperLayerIn <-- presl.lowerLayerOut;
            sessl.upperControlOut --> presl.lowerControlIn;
            sessl.upperControlIn <-- presl.lowerControlOut;
        }
        if (presentationType != "" && sessionType == "" && transportType != "") {
            tranl.upperLayerOut --> presl.lowerLayerIn;
            tranl.upperLayerIn <-- presl.lowerLayerOut;
            tranl.upperControlOut --> presl.lowerControlIn;
            tranl.upperControlIn <-- presl.lowerControlOut;
        }
        
        //# finaly we connect the highest existing layer of transport, session, or presentation to
        //# the application layer if specified
        if (applicationType != "" && presentationType == "" && sessionType == "" && transportType == "") {
            netwl.upperLayerOut --> appl.lowerLayerIn;
            netwl.upperLayerIn <-- appl.lowerLayerOut;
            netwl.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> appl.lowerControlIn;
            netwl.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- appl.lowerControlOut;
        }
        if (applicationType != "" && presentationType == "" && sessionType == "" && transportType != "") {
            tranl.upperLayerOut --> appl.lowerLayerIn;
            tranl.upperLayerIn <-- appl.lowerLayerOut;
            tranl.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> appl.lowerControlIn;
            tranl.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- appl.lowerControlOut;
        }
        if (applicationType != "" && presentationType == "" && sessionType != "") {
            sessl.upperLayerOut --> appl.lowerLayerIn;
            sessl.upperLayerIn <-- appl.lowerLayerOut;
            sessl.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> appl.lowerControlIn;
            sessl.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- appl.lowerControlOut;
        }
        if (applicationType != "" && presentationType != "") {
            presl.upperLayerOut --> appl.lowerLayerIn;
            presl.upperLayerIn <-- appl.lowerLayerOut;
            presl.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> appl.lowerControlIn;
            presl.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- appl.lowerControlOut;
        }
        
        radioIn --> nic.radioIn;
        
        
        //just for drawing the generated connections
        if fakeProcessor {
            HumiditySensor.fromTransducerToNodeProcessor --> ned.DatarateChannel --> Processor.fromHumiditySensor;
            TemperatureSensor.fromTransducerToNodeProcessor --> ned.DatarateChannel --> Processor.fromTemperatureSensor;
            PressureSensor.fromTransducerToNodeProcessor --> ned.DatarateChannel --> Processor.fromPressureSensor;
            LightSensor.fromTransducerToNodeProcessor --> ned.DatarateChannel --> Processor.fromLightSensor;

            HumiditySensor.toSensingUnitFromNodeProcessor <-- ned.DatarateChannel <-- Processor.toHumiditySensor;
            TemperatureSensor.toSensingUnitFromNodeProcessor <-- ned.DatarateChannel <-- Processor.toTemperatureSensor;
            PressureSensor.toSensingUnitFromNodeProcessor <-- ned.DatarateChannel <-- Processor.toPressureSensor;
            LightSensor.toSensingUnitFromNodeProcessor <-- ned.DatarateChannel <-- Processor.toLightSensor;
        }
}
