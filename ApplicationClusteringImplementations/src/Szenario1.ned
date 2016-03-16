package applicationclusteringimplementations;

import org.mixim.base.modules.BaseNetwork;

//
//some information about this szenario
//
//szenario.ini is the matching ini-file
//
//important data is:
//
////**.*.appl.sendingIntervall (s) - sending intervall time/ how long will the nodes store their measured values before sending them to the master,
////**.Node0.hasTemperatureSensor(etc) - define the sensors for each node,
////**.Memory.storageSize - define how much data every nodes memory can store (integer - if e.g. a value 1 is chosen, the memory can store only one data set),
////**.*.appl.coordinatorNodeAddr - defines the master node,
////energy consumptions,
////**.routeTree - define the routing table,
//
//routing:
//
////all nodes that are leaf nodes (defined inside routeTree) will measure (measure intervall is defined inside **.sensingIntervall),
////all other nodes won't,
////you can define one node as master (coordinatorNodeAddr),
////after a specific time (defined inside sendingIntervall) all leaf nodes will send all their measured values to the master,
////depending on the routingTree the master may not be reached in one step,
////the messages will also be send if leaf nodes aren't direct children of the master, so for example you can define one father node for every room and connect all
////room fathers to the master, the messages will then be transported via the defined connections
//
network Szenario1 extends BaseNetwork
{
    parameters:
        int numNodes; // total number of hosts in the network
        numNodes = 38;

        @display("bgi=background/roomsBigger;bgb=867,553");
        wuType = default("sensortechnology.src.WorldModel.CustomWorldUtility");
        cmType = default("org.mixim.base.connectionManager.ConnectionManager");

    submodules:
        Node0: Sensor_Wakeup_DicePhyMacHost {
            @display("p=404,282");
            //hasTemperatureSensor = true;
                    //@class(ApplicationClusteringImplementations);
        }
        Node1: Sensor_Wakeup_DicePhyMacHost {
            @display("p=404,192");
            //hasTemperatureSensor = true;
            appl.roomNumber = 0;
        }
        Node2: Sensor_Wakeup_DicePhyMacHost {
            @display("p=443,123");
            //hasTemperatureSensor = true;
        }
        Node3: Sensor_Wakeup_DicePhyMacHost {
            @display("p=365,123");
            //hasTemperatureSensor = true;
        }
        Node4: Sensor_Wakeup_DicePhyMacHost {
            @display("p=404,123");
            //hasTemperatureSensor = true;
        }
        Node5: Sensor_Wakeup_DicePhyMacHost {
            @display("p=509,282");
            //hasTemperatureSensor = true;
            appl.roomNumber = 3;
        }
        Node6: Sensor_Wakeup_DicePhyMacHost {
            @display("p=580,243");
            //hasTemperatureSensor = true;
        }
        Node7: Sensor_Wakeup_DicePhyMacHost {
            @display("p=580,282");
            //hasTemperatureSensor = true;
        }
        Node8: Sensor_Wakeup_DicePhyMacHost {
            @display("p=580,321");
            //hasTemperatureSensor = true;
        }
        Node9: Sensor_Wakeup_DicePhyMacHost {
            @display("p=404,377");
            appl.roomNumber = 2;
                        //hasTemperatureSensor = true;
        }
        Node10: Sensor_Wakeup_DicePhyMacHost {
            @display("p=345,452");
            //hasTemperatureSensor = true;
        }
        Node11: Sensor_Wakeup_DicePhyMacHost {
            @display("p=384,452");
            //hasTemperatureSensor = true;
        }
        Node12: Sensor_Wakeup_DicePhyMacHost {
            @display("p=423,452");
            //hasTemperatureSensor = true;
        }
        Node13: Sensor_Wakeup_DicePhyMacHost {
            @display("p=462,452");
            //hasTemperatureSensor = true;

        }
        Node14: Sensor_Wakeup_DicePhyMacHost {
            @display("p=294,282");
            appl.roomNumber = 1;
            //hasTemperatureSensor = true;
        }
        Node15: Sensor_Wakeup_DicePhyMacHost {
            @display("p=209,204");
            //hasTemperatureSensor = true;
        }
        Node16: Sensor_Wakeup_DicePhyMacHost {
            @display("p=209,243");
            //hasTemperatureSensor = true;
        }
        Node17: Sensor_Wakeup_DicePhyMacHost {
            @display("p=209,282");
            //hasTemperatureSensor = true;
        }
        Node18: Sensor_Wakeup_DicePhyMacHost {
            @display("p=209,321");
            //hasTemperatureSensor = true;
        }
        Node19: Sensor_Wakeup_DicePhyMacHost {
            @display("p=209,360");
            //hasTemperatureSensor = true;
        }

    connections allowunconnected:

    // all connections and gates are to be generated dynamically
}
