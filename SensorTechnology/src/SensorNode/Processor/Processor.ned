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

package sensortechnology.src.SensorNode.Processor;

//
// implementation of an processor, it is able to switch between different power modes and controles the other
// modules inside the sensor node
//
simple Processor
{
    parameters:
        int numGates = default(0);
        @display("i=device/cpu");
        
        //to add new modes you must also make changes inside the class Processor:
    	//extend the enum 'MODES'
    	//register the new account inside initialize(int)
    	//extend switchProcessorMode(MODES)
        
        int numModes = 3;
        
        //NORMAL mode
        double currentConsumptionNormal;
    	double energyConsumptionNormal;
    	//POWER_SAVING mode
        double currentConsumptionPowerSaving = default(currentConsumptionNormal);
    	double energyConsumptionPowerSaving  = default(energyConsumptionNormal);
    	//HIGH_PERFORMANCE mode
        double currentConsumptionHighPerformance  = default(currentConsumptionNormal);
    	double energyConsumptionHighPerformance  = default(energyConsumptionNormal);
	gates:
	    //dynamically created gates (once for every sensor on the node):

	    //inout connectToMemory;
	    //in fromTransducerToNodeProcessor;
}
