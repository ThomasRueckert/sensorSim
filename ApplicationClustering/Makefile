#
# OMNeT++/OMNEST Makefile for libApplicationClustering
#
# This file was generated with the command:
#  opp_makemake -f --deep --make-lib -O out -Xincludes1 -I../MiXiM/src/base/modules -I../MiXiM/src/inet_stub/networklayer/common -I../MiXiM/src -I../MiXiM/src/modules/utility -I../MiXiM/src/modules/power/battery -I../MiXiM/src/base/utils -I../MiXiM/src/modules/phy -I../MiXiM/src/inet_stub/mobility/models -I../MiXiM/src/base -I../MiXiM/src/base/phyLayer -I../MiXiM/src/inet_stub/mobility -I../MiXiM/src/modules/analogueModel -I../MiXiM/src/inet_stub/util -I../MiXiM/src/modules/messages -I../MiXiM/src/inet_stub/linklayer/contract -I../MiXiM/src/base/connectionManager -I../MiXiM/src/inet_stub/base -I../WakeUpRecv -I../MiXiM/src/base/messages -I../MiXiM/src/modules -L../MiXiM/out/$$\(CONFIGNAME\)/src -L../SensorTechnology/out/$$\(CONFIGNAME\)/src -L./out/$$\(CONFIGNAME\) -lmixim -lSensorTechnology -lApplicationClustering -DMIXIM_INET=1 -KMIXIM_PROJ=../MiXiM -KSENSORTECHNOLOGY_PROJ=../SensorTechnology -KWAKEUPRECV_PROJ=../WakeUpRecv -KAPPLICATIONCLUSTERING_PROJ=.
#

# Name of target to be created (-o option)
TARGET = libApplicationClustering$(A_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../MiXiM/src/base/modules \
    -I../MiXiM/src/inet_stub/networklayer/common \
    -I../MiXiM/src \
    -I../MiXiM/src/modules/utility \
    -I../MiXiM/src/modules/power/battery \
    -I../MiXiM/src/base/utils \
    -I../MiXiM/src/modules/phy \
    -I../MiXiM/src/inet_stub/mobility/models \
    -I../MiXiM/src/base \
    -I../MiXiM/src/base/phyLayer \
    -I../MiXiM/src/inet_stub/mobility \
    -I../MiXiM/src/modules/analogueModel \
    -I../MiXiM/src/inet_stub/util \
    -I../MiXiM/src/modules/messages \
    -I../MiXiM/src/inet_stub/linklayer/contract \
    -I../MiXiM/src/base/connectionManager \
    -I../MiXiM/src/inet_stub/base \
    -I../WakeUpRecv \
    -I../MiXiM/src/base/messages \
    -I../MiXiM/src/modules \
    -I. \
    -IPackets \
    -Iimages \
    -Iimages/dice \
    -Iimages/dice1 \
    -Iimages/led \
    -Iincludes \
    -Iresults

# Additional object and library files to link with
EXTRA_OBJS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/NetworkLayer2.o \
    $O/ce-wakeupSleep.o \
    $O/ce-resourceManager.o \
    $O/ce-clusterApplication.o \
    $O/MatrixApplication.o \
    $O/ce-appscheduler.o \
    $O/ce-application.o \
    $O/DiceApplication.o \
    $O/ce-network.o \
    $O/ce-coordinator.o \
    $O/ce-packets.o \
    $O/ce-appmaster.o \
    $O/ce-appmanager.o \
    $O/Packets/GenericPacket_m.o \
    $O/Packets/ApplicationPacket_m.o \
    $O/Packets/WakeUpPacket_m.o \
    $O/Packets/NetworkPacket_m.o

# Message files
MSGFILES = \
    Packets/GenericPacket.msg \
    Packets/ApplicationPacket.msg \
    Packets/WakeUpPacket.msg \
    Packets/NetworkPacket.msg

# Other makefile variables (-K)
MIXIM_PROJ=../MiXiM
SENSORTECHNOLOGY_PROJ=../SensorTechnology
WAKEUPRECV_PROJ=../WakeUpRecv
APPLICATIONCLUSTERING_PROJ=.

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

COPTS = $(CFLAGS) -DMIXIM_INET=1 $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating static library: $@
	$(Q)$(AR) $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f ApplicationClustering ApplicationClustering.exe libApplicationClustering.so libApplicationClustering.a libApplicationClustering.dll libApplicationClustering.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f Packets/*_m.cc Packets/*_m.h
	$(Q)-rm -f images/*_m.cc images/*_m.h
	$(Q)-rm -f images/dice/*_m.cc images/dice/*_m.h
	$(Q)-rm -f images/dice1/*_m.cc images/dice1/*_m.h
	$(Q)-rm -f images/led/*_m.cc images/led/*_m.h
	$(Q)-rm -f includes/*_m.cc includes/*_m.h
	$(Q)-rm -f results/*_m.cc results/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc Packets/*.cc images/*.cc images/dice/*.cc images/dice1/*.cc images/led/*.cc includes/*.cc results/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/DiceApplication.o: DiceApplication.cc \
	Packets/GenericPacket_m.h \
	Packets/WakeUpPacket_m.h \
	ce-appscheduler.h \
	ce-appstructs.h \
	ce-clusterApplication.h \
	ce-coordinator.h \
	ce-network.h \
	ce-resourcemanager.h \
	includes/DiceApplication.h \
	includes/ce-packetstructs.h \
	typedefs.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/WakeUpPacket_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMacLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/NetwControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayerBattery.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h
$O/MatrixApplication.o: MatrixApplication.cc \
	Packets/GenericPacket_m.h \
	Packets/WakeUpPacket_m.h \
	ce-appscheduler.h \
	ce-appstructs.h \
	ce-clusterApplication.h \
	ce-coordinator.h \
	ce-packets.h \
	ce-resourcemanager.h \
	includes/MatrixApplication.h \
	includes/ce-packetstructs.h \
	typedefs.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/WakeUpPacket_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMacLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/NetwControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayerBattery.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	$(WAKEUPRECV_PROJ)/WakeupPhyUtils.h
$O/NetworkLayer2.o: NetworkLayer2.cc \
	NetworkLayer2.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/ArpInterface.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseNetwLayer.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/NetwControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h \
	$(MIXIM_PROJ)/src/modules/messages/DummyRoutePkt_m.h
$O/ce-application.o: ce-application.cc \
	ce-application.h \
	ce-appscheduler.h \
	ce-appstructs.h \
	ce-clusterApplication.h \
	ce-coordinator.h \
	ce-data.h \
	ce-resourcemanager.h \
	includes/ce-packetstructs.h \
	typedefs.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h
$O/ce-appmanager.o: ce-appmanager.cc \
	ce-appscheduler.h \
	ce-appstructs.h \
	ce-clusterApplication.h \
	ce-coordinator.h \
	ce-data.h \
	ce-resourcemanager.h \
	includes/ce-packetstructs.h \
	typedefs.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h
$O/ce-appmaster.o: ce-appmaster.cc \
	ce-appscheduler.h \
	ce-appstructs.h \
	ce-clusterApplication.h \
	ce-coordinator.h \
	ce-data.h \
	ce-resourcemanager.h \
	includes/ce-packetstructs.h \
	typedefs.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h
$O/ce-appscheduler.o: ce-appscheduler.cc \
	ce-appscheduler.h \
	ce-appstructs.h \
	ce-clusterApplication.h \
	ce-coordinator.h \
	ce-data.h \
	ce-resourcemanager.h \
	includes/ce-packetstructs.h \
	typedefs.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h
$O/ce-clusterApplication.o: ce-clusterApplication.cc \
	ce-appscheduler.h \
	ce-appstructs.h \
	ce-clusterApplication.h \
	ce-coordinator.h \
	ce-resourcemanager.h \
	includes/ce-packetstructs.h \
	typedefs.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h
$O/ce-coordinator.o: ce-coordinator.cc \
	ce-appscheduler.h \
	ce-appstructs.h \
	ce-clusterApplication.h \
	ce-coordinator.h \
	ce-resourcemanager.h \
	includes/ce-packetstructs.h \
	typedefs.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h
$O/ce-network.o: ce-network.cc \
	Packets/GenericPacket_m.h \
	ce-appscheduler.h \
	ce-appstructs.h \
	ce-clusterApplication.h \
	ce-coordinator.h \
	ce-network.h \
	ce-resourcemanager.h \
	includes/ce-packetstructs.h \
	typedefs.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/ApplPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseNetwLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/NetwControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/utility/Packet.h
$O/ce-packets.o: ce-packets.cc \
	ce-appscheduler.h \
	ce-appstructs.h \
	ce-clusterApplication.h \
	ce-coordinator.h \
	ce-packets.h \
	ce-resourcemanager.h \
	includes/ce-packetstructs.h \
	typedefs.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h
$O/ce-resourceManager.o: ce-resourceManager.cc \
	ce-appscheduler.h \
	ce-appstructs.h \
	ce-clusterApplication.h \
	ce-coordinator.h \
	ce-resourcemanager.h \
	includes/ce-packetstructs.h \
	typedefs.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h
$O/ce-wakeupSleep.o: ce-wakeupSleep.cc \
	ce-application.h \
	ce-appscheduler.h \
	ce-appstructs.h \
	ce-clusterApplication.h \
	ce-coordinator.h \
	ce-data.h \
	ce-resourcemanager.h \
	includes/ce-packetstructs.h \
	typedefs.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayerBattery.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	$(WAKEUPRECV_PROJ)/WakeupPhyUtils.h
$O/Packets/ApplicationPacket_m.o: Packets/ApplicationPacket_m.cc \
	Packets/ApplicationPacket_m.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h
$O/Packets/GenericPacket_m.o: Packets/GenericPacket_m.cc \
	Packets/GenericPacket_m.h
$O/Packets/NetworkPacket_m.o: Packets/NetworkPacket_m.cc \
	Packets/NetworkPacket_m.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h
$O/Packets/WakeUpPacket_m.o: Packets/WakeUpPacket_m.cc \
	Packets/WakeUpPacket_m.h \
	$(MIXIM_PROJ)/src/base/messages/WakeUpPacket_m.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h

