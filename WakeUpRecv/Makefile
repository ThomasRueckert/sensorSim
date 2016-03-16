#
# OMNeT++/OMNEST Makefile for libWakeUpRecv
#
# This file was generated with the command:
#  opp_makemake -f --deep --make-so -O out -I../MiXiM/src/modules/messages -I../MiXiM/src/base/phyLayer -I../MiXiM/src -I../MiXiM/src/modules/utility -I../MiXiM/src/modules/analogueModel -I../MiXiM/src/base -I../MiXiM/src/inet_stub/mobility -I../MiXiM/src/base/utils -I../MiXiM/src/base/modules -I../MiXiM/src/modules -I../MiXiM/src/modules/phy -I../MiXiM/src/inet_stub/base -I../ApplicationClustering/Packets -I../MiXiM/src/inet_stub/util -I../MiXiM/src/modules/power/battery -I../MiXiM/src/inet_stub/linklayer/contract -I../MiXiM/src/base/messages -I../MiXiM/src/base/connectionManager -I../MiXiM/src/inet_stub/mobility/models -I../MiXiM/src/inet_stub/networklayer/common -L../ApplicationClustering/out/$$\(CONFIGNAME\) -L../MiXiM/out/$$\(CONFIGNAME\)/src -L../SensorTechnology/out/$$\(CONFIGNAME\)/src -lApplicationClustering -lmixim -lSensorTechnology -DMIXIM_INET=1 -KAPPLICATIONCLUSTERING_PROJ=../ApplicationClustering -KMIXIM_PROJ=../MiXiM -KSENSORTECHNOLOGY_PROJ=../SensorTechnology -KWAKEUPRECV_PROJ=.
#

# Name of target to be created (-o option)
TARGET = libWakeUpRecv$(SHARED_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../MiXiM/src/modules/messages \
    -I../MiXiM/src/base/phyLayer \
    -I../MiXiM/src \
    -I../MiXiM/src/modules/utility \
    -I../MiXiM/src/modules/analogueModel \
    -I../MiXiM/src/base \
    -I../MiXiM/src/inet_stub/mobility \
    -I../MiXiM/src/base/utils \
    -I../MiXiM/src/base/modules \
    -I../MiXiM/src/modules \
    -I../MiXiM/src/modules/phy \
    -I../MiXiM/src/inet_stub/base \
    -I../ApplicationClustering/Packets \
    -I../MiXiM/src/inet_stub/util \
    -I../MiXiM/src/modules/power/battery \
    -I../MiXiM/src/inet_stub/linklayer/contract \
    -I../MiXiM/src/base/messages \
    -I../MiXiM/src/base/connectionManager \
    -I../MiXiM/src/inet_stub/mobility/models \
    -I../MiXiM/src/inet_stub/networklayer/common \
    -I. \
    -Iresults

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../ApplicationClustering/out/$(CONFIGNAME) -L../MiXiM/out/$(CONFIGNAME)/src -L../SensorTechnology/out/$(CONFIGNAME)/src  -lApplicationClustering -lmixim -lSensorTechnology
LIBS += -Wl,-rpath,`abspath ../ApplicationClustering/out/$(CONFIGNAME)` -Wl,-rpath,`abspath ../MiXiM/out/$(CONFIGNAME)/src` -Wl,-rpath,`abspath ../SensorTechnology/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = $O/WakeupPhyLayerBattery.o $O/WakeupBaseDecider.o $O/WakeupPhyUtils.o $O/MyTestApplication.o

# Message files
MSGFILES =

# Other makefile variables (-K)
APPLICATIONCLUSTERING_PROJ=../ApplicationClustering
MIXIM_PROJ=../MiXiM
SENSORTECHNOLOGY_PROJ=../SensorTechnology
WAKEUPRECV_PROJ=.

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
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppenvir$D $(KERNEL_LIBS) $(SYS_LIBS)

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
	@echo Creating shared library: $@
	$(Q)$(SHLIB_LD) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS) $(LDFLAGS)
	$(Q)$(SHLIB_POSTPROCESS) $O/$(TARGET)

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
	$(Q)-rm -f WakeUpRecv WakeUpRecv.exe libWakeUpRecv.so libWakeUpRecv.a libWakeUpRecv.dll libWakeUpRecv.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f results/*_m.cc results/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc results/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/MyTestApplication.o: MyTestApplication.cc \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/GenericPacket_m.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/ApplPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/NetwPkt_m.h \
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
	$(MIXIM_PROJ)/src/modules/messages/WiseRoutePkt_m.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	MyTestApplication.h \
	WakeupPhyLayerBattery.h \
	WakeupPhyUtils.h
$O/WakeupBaseDecider.o: WakeupBaseDecider.cc \
	$(APPLICATIONCLUSTERING_PROJ)/Packets/WakeUpPacket_m.h \
	$(MIXIM_PROJ)/src/base/messages/ChannelSenseRequest_m.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/messages/WakeUpPacket_m.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BaseDecider.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Decider.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyToMacControlInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	$(MIXIM_PROJ)/src/modules/phy/Decider802154Narrow.h \
	WakeupBaseDecider.h
$O/WakeupPhyLayerBattery.o: WakeupPhyLayerBattery.cc \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/ChannelSenseRequest_m.h \
	$(MIXIM_PROJ)/src/base/messages/MacPkt_m.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMMacPkt.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BaseDecider.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Decider.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyControlInfo.h \
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
	$(MIXIM_PROJ)/src/modules/phy/Decider80211Battery.h \
	$(MIXIM_PROJ)/src/modules/phy/Decider80211MultiChannel.h \
	$(MIXIM_PROJ)/src/modules/phy/Decider802154Narrow.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/phy/SNRThresholdDecider.h \
	WakeupBaseDecider.h \
	WakeupPhyLayerBattery.h \
	WakeupPhyUtils.h
$O/WakeupPhyUtils.o: WakeupPhyUtils.cc \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	WakeupPhyUtils.h

