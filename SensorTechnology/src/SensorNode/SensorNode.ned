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

package sensortechnology.src.SensorNode;
import sensortechnology.src.SensorNode.Sensor.*;
import sensortechnology.src.SensorNode.Processor.*;
import sensortechnology.src.SensorNode.Memory.*;
import org.mixim.modules.node.WirelessNodeBatteryPlusTran;

//
// Sensor Node which can combine the different types of sensors (or have non of them) and
// a battery, memory, processor and radio module 
//
module SensorNode extends WirelessNodeBatteryPlusTran like SensorNodeInterface
{
    parameters:
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
        bool hasTemperatureSensor = default(false);
        bool hasHumiditySensor = default(false);
        bool hasPressureSensor = default(false);
        bool hasLightSensor = default(false);
        int numSensors = default(0);
        int numSensorModules = 4;
        //memory, processor
        //calculate number of energie accounts from sensor 
        int numDevices = (
        		 (hasTemperatureSensor ? 1 : 0) 
            	+(hasHumiditySensor ? 1 : 0)
            	+(hasPressureSensor ? 1 : 0)
            	+(hasLightSensor ? 1 : 0)
        	) * numSensorModules //calculate number of energie accounts from sensor 
        	+ 2 + 1; //memory, processor
    	battery.numDevices = numDevices;
        int numHosts;
        //@class("SensorNode");
        @class(SensorNode);
        //these are used to draw the overview of the model
        bool fakeProcessor = false;
        @display("bgb=447,450;i=block/ifcard");

        //custom parameters
        transportType = default("Aggregation");
        nicType = "CustomNic802154";  //CustomNic for wakeup receiver states
        arpType = default("org.mixim.modules.netw.ArpHost");

        batteryStats.detail = default(false);
        batteryStats.timeSeries = default(false);

        battery.nominal = default(1000 mAh);
        battery.capacity = default(battery.nominal);
        battery.voltage = default(3 V);
        battery.resolution = default(60 s);
        battery.publishDelta = default(1);
        battery.publishTime = default(battery.resolution);
        
        double normalRatio = default(1);
		double powerSavingRatio = default(1);
		double highPerformanceRatio = default(1);

    submodules:
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
    connections:
        //these connections will never be created, they only exist to draw the models design
        //
        //the real connections between processor and sensor are created dynamically because 
        //only the gates needed are created in order to avoid unused (not connected) gates
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
