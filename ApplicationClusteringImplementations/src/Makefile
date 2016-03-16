#
# OMNeT++/OMNEST Makefile for ApplicationClusteringImplementations
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -I../../MiXiM/src/base/phyLayer -I../../MiXiM/src -I../../MiXiM/src/modules/analogueModel -I../../MiXiM/src/base -I../../MiXiM/src/inet_stub/mobility -I../../WakeUpRecv -I../../SensorTechnology/src/SensorNode/Memory -I../../MiXiM/src/base/modules -I../../MiXiM/src/inet_stub/base -I../../ApplicationClustering/Packets -I../../MiXiM/src/base/messages -I../../SensorTechnology/src/SensorNode/Processor -I../../ApplicationClustering -I../../SensorTechnology/src -I../../MiXiM/src/modules/messages -I../../MiXiM/src/modules/utility -I../../MiXiM/src/modules/netw -I../../SensorTechnology/src/SensorNode -I../../SensorTechnology/src/ExtendedMessage -I../../MiXiM/src/base/utils -I../../ApplicationClustering/includes -I../../MiXiM/src/modules -I../../MiXiM/src/modules/phy -I../../MiXiM/src/inet_stub/util -I../../MiXiM/src/modules/power/battery -I../../MiXiM/src/inet_stub/linklayer/contract -I../../MiXiM/src/base/connectionManager -I../../MiXiM/src/inet_stub/mobility/models -I../../SensorTechnology/src/SimpleSensorData -I../../MiXiM/src/inet_stub/networklayer/common -I../../MiXiM/src/modules/mac -L../../ApplicationClustering/out/$$\(CONFIGNAME\) -L../../MiXiM/out/$$\(CONFIGNAME\)/src -L../../SensorTechnology/out/$$\(CONFIGNAME\)/src -lApplicationClustering -lmixim -lSensorTechnology -DMIXIM_INET=1 -KAPPLICATIONCLUSTERING_PROJ=../../ApplicationClustering -KMIXIM_PROJ=../../MiXiM -KSENSORTECHNOLOGY_PROJ=../../SensorTechnology -KWAKEUPRECV_PROJ=../../WakeUpRecv
#

# Name of target to be created (-o option)
TARGET = ApplicationClusteringImplementations$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../MiXiM/src/base/phyLayer \
    -I../../MiXiM/src \
    -I../../MiXiM/src/modules/analogueModel \
    -I../../MiXiM/src/base \
    -I../../MiXiM/src/inet_stub/mobility \
    -I../../WakeUpRecv \
    -I../../SensorTechnology/src/SensorNode/Memory \
    -I../../MiXiM/src/base/modules \
    -I../../MiXiM/src/inet_stub/base \
    -I../../ApplicationClustering/Packets \
    -I../../MiXiM/src/base/messages \
    -I../../SensorTechnology/src/SensorNode/Processor \
    -I../../ApplicationClustering \
    -I../../SensorTechnology/src \
    -I../../MiXiM/src/modules/messages \
    -I../../MiXiM/src/modules/utility \
    -I../../MiXiM/src/modules/netw \
    -I../../SensorTechnology/src/SensorNode \
    -I../../SensorTechnology/src/ExtendedMessage \
    -I../../MiXiM/src/base/utils \
    -I../../ApplicationClustering/includes \
    -I../../MiXiM/src/modules \
    -I../../MiXiM/src/modules/phy \
    -I../../MiXiM/src/inet_stub/util \
    -I../../MiXiM/src/modules/power/battery \
    -I../../MiXiM/src/inet_stub/linklayer/contract \
    -I../../MiXiM/src/base/connectionManager \
    -I../../MiXiM/src/inet_stub/mobility/models \
    -I../../SensorTechnology/src/SimpleSensorData \
    -I../../MiXiM/src/inet_stub/networklayer/common \
    -I../../MiXiM/src/modules/mac \
    -I. \
    -IACI \
    -IAppl \
    -IBatteryStatsInfo \
    -IMacLayer \
    -INetwl \
    -Idata \
    -Iimg \
    -Iresults

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../ApplicationClustering/out/$(CONFIGNAME) -L../../MiXiM/out/$(CONFIGNAME)/src -L../../SensorTechnology/out/$(CONFIGNAME)/src  -lApplicationClustering -lmixim -lSensorTechnology
LIBS += -Wl,-rpath,`abspath ../../ApplicationClustering/out/$(CONFIGNAME)` -Wl,-rpath,`abspath ../../MiXiM/out/$(CONFIGNAME)/src` -Wl,-rpath,`abspath ../../SensorTechnology/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/ACI/ApplicationClusteringImplementations.o \
    $O/Appl/CustomDiceApplication.o \
    $O/Appl/Szenario3Appl.o \
    $O/Appl/CustomMatrixApplication.o \
    $O/Appl/ClusterMasterClusterAppl.o \
    $O/Appl/LeafClusterAppl.o \
    $O/Appl/NoApplicationClusteringAppl.o \
    $O/Appl/MasterClusterAppl.o \
    $O/Appl/AbstractClusterAppl.o \
    $O/BatteryStatsInfo/SimpleBatteryStatsInfo.o \
    $O/MacLayer/CSMA802154HostStateHandled.o \
    $O/Netwl/ClusterApplWiseRoute.o \
    $O/Netwl/CustomWiseRoute.o \
    $O/BatteryStatsInfo/BatteryStatsInfo_m.o \
    $O/BatteryStatsInfo/BatteryStatsInfoPkt_m.o

# Message files
MSGFILES = \
    BatteryStatsInfo/BatteryStatsInfo.msg \
    BatteryStatsInfo/BatteryStatsInfoPkt.msg

# Other makefile variables (-K)
APPLICATIONCLUSTERING_PROJ=../../ApplicationClustering
MIXIM_PROJ=../../MiXiM
SENSORTECHNOLOGY_PROJ=../../SensorTechnology
WAKEUPRECV_PROJ=../../WakeUpRecv

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

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

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
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

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
	$(Q)-rm -f ApplicationClusteringImplementations ApplicationClusteringImplementations.exe libApplicationClusteringImplementations.so libApplicationClusteringImplementations.a libApplicationClusteringImplementations.dll libApplicationClusteringImplementations.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f ACI/*_m.cc ACI/*_m.h
	$(Q)-rm -f Appl/*_m.cc Appl/*_m.h
	$(Q)-rm -f BatteryStatsInfo/*_m.cc BatteryStatsInfo/*_m.h
	$(Q)-rm -f MacLayer/*_m.cc MacLayer/*_m.h
	$(Q)-rm -f Netwl/*_m.cc Netwl/*_m.h
	$(Q)-rm -f data/*_m.cc data/*_m.h
	$(Q)-rm -f img/*_m.cc img/*_m.h
	$(Q)-rm -f results/*_m.cc results/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc ACI/*.cc Appl/*.cc BatteryStatsInfo/*.cc MacLayer/*.cc Netwl/*.cc data/*.cc img/*.cc results/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/ACI/ApplicationClusteringImplementations.o: ACI/ApplicationClusteringImplementations.cc \
	ACI/ApplicationClusteringImplementations.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/SensorNode.h
$O/Appl/AbstractClusterAppl.o: Appl/AbstractClusterAppl.cc \
	Appl/AbstractClusterAppl.h
$O/Appl/ClusterMasterClusterAppl.o: Appl/ClusterMasterClusterAppl.cc \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/GenericPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/WakeUpPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appscheduler.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-clusterApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-coordinator.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-resourcemanager.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/MatrixApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/ce-packetstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/typedefs.h \
	Appl/AbstractClusterAppl.h \
	Appl/ClusterMasterClusterAppl.h \
	Appl/CustomMatrixApplication.h \
	Appl/LeafClusterAppl.h \
	Appl/NoApplicationClusteringAppl.h \
	Appl/Szenario3Appl.h \
	BatteryStatsInfo/SimpleBatteryStatsInfo.h \
	Netwl/ClusterApplWiseRoute.h \
	Netwl/CustomWiseRoute.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/ApplPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/WakeUpPacket_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseNetwLayer.h \
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
	$(MIXIM_PROJ)/src/modules/messages/DummyRoutePkt_m.h \
	$(MIXIM_PROJ)/src/modules/netw/WiseRoute.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayerBattery.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/BatteryAccess.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/Memory/Memory.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/Processor/Processor.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/SensorNode.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SimpleSensorData/SimpleSensorData.h
$O/Appl/CustomDiceApplication.o: Appl/CustomDiceApplication.cc \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/GenericPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/WakeUpPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appscheduler.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-clusterApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-coordinator.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-network.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-resourcemanager.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/DiceApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/ce-packetstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/typedefs.h \
	Appl/CustomDiceApplication.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/WakeUpPacket_m.h \
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
	$(MIXIM_PROJ)/src/base/utils/NetwControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h
$O/Appl/CustomMatrixApplication.o: Appl/CustomMatrixApplication.cc \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appscheduler.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-clusterApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-coordinator.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-resourcemanager.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/MatrixApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/ce-packetstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/typedefs.h \
	Appl/CustomMatrixApplication.h \
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
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h
$O/Appl/LeafClusterAppl.o: Appl/LeafClusterAppl.cc \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/GenericPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/WakeUpPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appscheduler.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-clusterApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-coordinator.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-resourcemanager.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/MatrixApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/ce-packetstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/typedefs.h \
	Appl/AbstractClusterAppl.h \
	Appl/CustomMatrixApplication.h \
	Appl/LeafClusterAppl.h \
	BatteryStatsInfo/BatteryStatsInfo_m.h \
	BatteryStatsInfo/SimpleBatteryStatsInfo.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/ApplPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/WakeUpPacket_m.h \
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
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
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
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/BatteryAccess.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/Memory/Memory.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/Processor/Processor.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/SensorNode.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SimpleSensorData/SimpleSensorData.h
$O/Appl/MasterClusterAppl.o: Appl/MasterClusterAppl.cc \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/GenericPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/WakeUpPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appscheduler.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-clusterApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-coordinator.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-network.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-resourcemanager.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/DiceApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/MatrixApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/ce-packetstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/typedefs.h \
	Appl/AbstractClusterAppl.h \
	Appl/CustomDiceApplication.h \
	Appl/CustomMatrixApplication.h \
	Appl/MasterClusterAppl.h \
	Appl/NoApplicationClusteringAppl.h \
	Appl/Szenario3Appl.h \
	Netwl/ClusterApplWiseRoute.h \
	Netwl/CustomWiseRoute.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/ApplPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/WakeUpPacket_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseNetwLayer.h \
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
	$(MIXIM_PROJ)/src/modules/messages/DummyRoutePkt_m.h \
	$(MIXIM_PROJ)/src/modules/netw/WiseRoute.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/BatteryAccess.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/Memory/Memory.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/SensorNode.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SimpleSensorData/SimpleSensorData.h
$O/Appl/NoApplicationClusteringAppl.o: Appl/NoApplicationClusteringAppl.cc \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/GenericPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/WakeUpPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appscheduler.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-clusterApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-coordinator.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-resourcemanager.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/MatrixApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/ce-packetstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/typedefs.h \
	Appl/CustomMatrixApplication.h \
	Appl/NoApplicationClusteringAppl.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/ApplPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/WakeUpPacket_m.h \
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
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/NetwControlInfo.h \
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
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/BatteryAccess.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/Memory/Memory.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/SensorNode.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SimpleSensorData/SimpleSensorData.h \
	$(WAKEUPRECV_PROJ)/WakeupPhyUtils.h
$O/Appl/Szenario3Appl.o: Appl/Szenario3Appl.cc \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/GenericPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/WakeUpPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appscheduler.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-clusterApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-coordinator.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-resourcemanager.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/MatrixApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/ce-packetstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/typedefs.h \
	Appl/CustomMatrixApplication.h \
	Appl/Szenario3Appl.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/ApplPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/WakeUpPacket_m.h \
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
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/NetwControlInfo.h \
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
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/BatteryAccess.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/Memory/Memory.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/SensorNode.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SimpleSensorData/SimpleSensorData.h \
	$(WAKEUPRECV_PROJ)/WakeupPhyUtils.h
$O/BatteryStatsInfo/BatteryStatsInfoPkt_m.o: BatteryStatsInfo/BatteryStatsInfoPkt_m.cc \
	BatteryStatsInfo/BatteryStatsInfoPkt_m.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h
$O/BatteryStatsInfo/BatteryStatsInfo_m.o: BatteryStatsInfo/BatteryStatsInfo_m.cc \
	BatteryStatsInfo/BatteryStatsInfo_m.h
$O/BatteryStatsInfo/SimpleBatteryStatsInfo.o: BatteryStatsInfo/SimpleBatteryStatsInfo.cc \
	BatteryStatsInfo/SimpleBatteryStatsInfo.h
$O/MacLayer/CSMA802154HostStateHandled.o: MacLayer/CSMA802154HostStateHandled.cc \
	MacLayer/CSMA802154HostStateHandled.h \
	$(MIXIM_PROJ)/src/base/messages/MacPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMacLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h \
	$(MIXIM_PROJ)/src/modules/mac/CSMA802154.h \
	$(MIXIM_PROJ)/src/modules/mac/csma.h \
	$(MIXIM_PROJ)/src/modules/messages/WiseRoutePkt_m.h \
	$(MIXIM_PROJ)/src/modules/utility/DroppedPacket.h
$O/Netwl/ClusterApplWiseRoute.o: Netwl/ClusterApplWiseRoute.cc \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/GenericPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/WakeUpPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appscheduler.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-clusterApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-coordinator.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-network.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-resourcemanager.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/DiceApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/MatrixApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/ce-packetstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/typedefs.h \
	Appl/AbstractClusterAppl.h \
	Appl/ClusterMasterClusterAppl.h \
	Appl/CustomDiceApplication.h \
	Appl/CustomMatrixApplication.h \
	Appl/LeafClusterAppl.h \
	Appl/MasterClusterAppl.h \
	Appl/NoApplicationClusteringAppl.h \
	Appl/Szenario3Appl.h \
	Netwl/ClusterApplWiseRoute.h \
	Netwl/CustomWiseRoute.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/ApplPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/WakeUpPacket_m.h \
	$(MIXIM_PROJ)/src/base/modules/ArpInterface.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseNetwLayer.h \
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
	$(MIXIM_PROJ)/src/modules/messages/DummyRoutePkt_m.h \
	$(MIXIM_PROJ)/src/modules/messages/WiseRoutePkt_m.h \
	$(MIXIM_PROJ)/src/modules/netw/WiseRoute.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/BatteryAccess.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/Memory/Memory.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/Processor/Processor.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/SensorNode.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SimpleSensorData/SimpleSensorData.h
$O/Netwl/CustomWiseRoute.o: Netwl/CustomWiseRoute.cc \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/GenericPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/WakeUpPacket_m.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appscheduler.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-appstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-clusterApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-coordinator.h \
	$(APPLICATIONCLUSTERING_PROJ)/ce-resourcemanager.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/MatrixApplication.h \
	$(APPLICATIONCLUSTERING_PROJ)/includes/ce-packetstructs.h \
	$(APPLICATIONCLUSTERING_PROJ)/typedefs.h \
	Appl/CustomMatrixApplication.h \
	Appl/NoApplicationClusteringAppl.h \
	Appl/Szenario3Appl.h \
	Netwl/CustomWiseRoute.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/ApplPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/WakeUpPacket_m.h \
	$(MIXIM_PROJ)/src/base/modules/ArpInterface.h \
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
	$(MIXIM_PROJ)/src/base/utils/MacToNetwControlInfo.h \
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
	$(MIXIM_PROJ)/src/modules/messages/DummyRoutePkt_m.h \
	$(MIXIM_PROJ)/src/modules/messages/WiseRoutePkt_m.h \
	$(MIXIM_PROJ)/src/modules/netw/WiseRoute.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	$(MIXIM_PROJ)/src/modules/utility/Packet.h \
	$(MIXIM_PROJ)/src/modules/utility/SimTracer.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/BatteryAccess.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/Memory/Memory.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SensorNode/SensorNode.h \
	$(SENSORTECHNOLOGY_PROJ)/src/SimpleSensorData/SimpleSensorData.h \
	$(WAKEUPRECV_PROJ)/MyTestApplication.h \
	$(WAKEUPRECV_PROJ)/WakeupPhyLayerBattery.h

