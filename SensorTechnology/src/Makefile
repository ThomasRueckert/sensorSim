#
# OMNeT++/OMNEST Makefile for libSensorTechnology
#
# This file was generated with the command:
#  opp_makemake -f --deep --make-so -O out -I../../MiXiM/src/base/phyLayer -I../../MiXiM/src -I../../MiXiM/src/modules/analogueModel -I../../MiXiM/src/base -I../../MiXiM/src/inet_stub/mobility -I../../MiXiM/src/base/modules -I../../MiXiM/src/inet_stub/base -I../../MiXiM/src/base/messages -I../../MiXiM/src/modules/messages -I../../MiXiM/src/modules/netw -I../../MiXiM/src/modules/utility -I../../MiXiM/src/base/utils -I../../MiXiM/src/modules -I../../MiXiM/src/modules/phy -I../../MiXiM/src/modules/power/battery -I../../MiXiM/src/inet_stub/util -I../../MiXiM/src/inet_stub/linklayer/contract -I../../MiXiM/src/base/connectionManager -I../../MiXiM/src/inet_stub/mobility/models -I../../MiXiM/src/inet_stub/networklayer/common -L../../MiXiM/out/$$\(CONFIGNAME\)/src -lmixim -DMIXIM_INET=1 -KMIXIM_PROJ=../../MiXiM
#

# Name of target to be created (-o option)
TARGET = libSensorTechnology$(SHARED_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../MiXiM/src/base/phyLayer \
    -I../../MiXiM/src \
    -I../../MiXiM/src/modules/analogueModel \
    -I../../MiXiM/src/base \
    -I../../MiXiM/src/inet_stub/mobility \
    -I../../MiXiM/src/base/modules \
    -I../../MiXiM/src/inet_stub/base \
    -I../../MiXiM/src/base/messages \
    -I../../MiXiM/src/modules/messages \
    -I../../MiXiM/src/modules/netw \
    -I../../MiXiM/src/modules/utility \
    -I../../MiXiM/src/base/utils \
    -I../../MiXiM/src/modules \
    -I../../MiXiM/src/modules/phy \
    -I../../MiXiM/src/modules/power/battery \
    -I../../MiXiM/src/inet_stub/util \
    -I../../MiXiM/src/inet_stub/linklayer/contract \
    -I../../MiXiM/src/base/connectionManager \
    -I../../MiXiM/src/inet_stub/mobility/models \
    -I../../MiXiM/src/inet_stub/networklayer/common \
    -I. \
    -IExtendedMessage \
    -ISensorNetworkInterface \
    -ISensorNode \
    -ISensorNode/Memory \
    -ISensorNode/Processor \
    -ISensorNode/Sensor \
    -ISensorNode/Sensor/SensingUnit \
    -ISensorNode/Sensor/SignalConditioner \
    -ISensorNode/Sensor/SignalConverter \
    -ISensorNode/Sensor/Transducer \
    -ISimpleSensorData \
    -IStatisticsInterface \
    -IWorldModel

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../MiXiM/out/$(CONFIGNAME)/src  -lmixim
LIBS += -Wl,-rpath,`abspath ../../MiXiM/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/SensorNode/BatteryAccess.o \
    $O/SensorNode/SensorNode.o \
    $O/SensorNode/Memory/Memory.o \
    $O/SensorNode/Processor/Processor.o \
    $O/SensorNode/Sensor/AbstractSensor.o \
    $O/SensorNode/Sensor/SensingUnit/AbstractSensingUnit.o \
    $O/SensorNode/Sensor/SignalConditioner/AbstractSignalConditioner.o \
    $O/SensorNode/Sensor/SignalConverter/AbstractSignalConverter.o \
    $O/SensorNode/Sensor/Transducer/AbstractTransducer.o \
    $O/SimpleSensorData/SimpleSensorData.o \
    $O/StatisticsInterface/StatisticsInterface.o \
    $O/WorldModel/CustomWorldUtility.o \
    $O/ExtendedMessage/ExtendedMessage_m.o

# Message files
MSGFILES = \
    ExtendedMessage/ExtendedMessage.msg

# Other makefile variables (-K)
MIXIM_PROJ=../../MiXiM

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
	$(Q)-rm -f SensorTechnology SensorTechnology.exe libSensorTechnology.so libSensorTechnology.a libSensorTechnology.dll libSensorTechnology.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f ExtendedMessage/*_m.cc ExtendedMessage/*_m.h
	$(Q)-rm -f SensorNetworkInterface/*_m.cc SensorNetworkInterface/*_m.h
	$(Q)-rm -f SensorNode/*_m.cc SensorNode/*_m.h
	$(Q)-rm -f SensorNode/Memory/*_m.cc SensorNode/Memory/*_m.h
	$(Q)-rm -f SensorNode/Processor/*_m.cc SensorNode/Processor/*_m.h
	$(Q)-rm -f SensorNode/Sensor/*_m.cc SensorNode/Sensor/*_m.h
	$(Q)-rm -f SensorNode/Sensor/SensingUnit/*_m.cc SensorNode/Sensor/SensingUnit/*_m.h
	$(Q)-rm -f SensorNode/Sensor/SignalConditioner/*_m.cc SensorNode/Sensor/SignalConditioner/*_m.h
	$(Q)-rm -f SensorNode/Sensor/SignalConverter/*_m.cc SensorNode/Sensor/SignalConverter/*_m.h
	$(Q)-rm -f SensorNode/Sensor/Transducer/*_m.cc SensorNode/Sensor/Transducer/*_m.h
	$(Q)-rm -f SimpleSensorData/*_m.cc SimpleSensorData/*_m.h
	$(Q)-rm -f StatisticsInterface/*_m.cc StatisticsInterface/*_m.h
	$(Q)-rm -f WorldModel/*_m.cc WorldModel/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc ExtendedMessage/*.cc SensorNetworkInterface/*.cc SensorNode/*.cc SensorNode/Memory/*.cc SensorNode/Processor/*.cc SensorNode/Sensor/*.cc SensorNode/Sensor/SensingUnit/*.cc SensorNode/Sensor/SignalConditioner/*.cc SensorNode/Sensor/SignalConverter/*.cc SensorNode/Sensor/Transducer/*.cc SimpleSensorData/*.cc StatisticsInterface/*.cc WorldModel/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/ExtendedMessage/ExtendedMessage_m.o: ExtendedMessage/ExtendedMessage_m.cc \
	ExtendedMessage/ExtendedMessage_m.h
$O/SensorNode/BatteryAccess.o: SensorNode/BatteryAccess.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	SensorNode/BatteryAccess.h \
	SensorNode/SensorNode.h
$O/SensorNode/SensorNode.o: SensorNode/SensorNode.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseNetwLayer.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/linklayer/contract/MACAddress.h \
	$(MIXIM_PROJ)/src/modules/netw/WiseRoute.h \
	$(MIXIM_PROJ)/src/modules/power/battery/BatteryState.h \
	$(MIXIM_PROJ)/src/modules/power/battery/DeviceEntry.h \
	$(MIXIM_PROJ)/src/modules/power/battery/SimpleBattery.h \
	ExtendedMessage/ExtendedMessage_m.h \
	SensorNode/BatteryAccess.h \
	SensorNode/Processor/Processor.h \
	SensorNode/SensorNode.h
$O/SensorNode/Memory/Memory.o: SensorNode/Memory/Memory.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	SensorNode/BatteryAccess.h \
	SensorNode/Memory/Memory.h \
	SensorNode/SensorNode.h \
	SimpleSensorData/SimpleSensorData.h
$O/SensorNode/Processor/Processor.o: SensorNode/Processor/Processor.cc \
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
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	SensorNode/BatteryAccess.h \
	SensorNode/Memory/Memory.h \
	SensorNode/Processor/Processor.h \
	SensorNode/SensorNode.h \
	SimpleSensorData/SimpleSensorData.h
$O/SensorNode/Sensor/AbstractSensor.o: SensorNode/Sensor/AbstractSensor.cc \
	SensorNode/Sensor/AbstractSensor.h
$O/SensorNode/Sensor/SensingUnit/AbstractSensingUnit.o: SensorNode/Sensor/SensingUnit/AbstractSensingUnit.cc \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
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
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/ModuleAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/IMobility.h \
	$(MIXIM_PROJ)/src/inet_stub/mobility/models/MobilityAccess.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	ExtendedMessage/ExtendedMessage_m.h \
	SensorNode/BatteryAccess.h \
	SensorNode/Sensor/SensingUnit/AbstractSensingUnit.h \
	SensorNode/SensorNode.h \
	SimpleSensorData/SimpleSensorData.h \
	StatisticsInterface/StatisticsInterface.h \
	WorldModel/CustomWorldUtility.h
$O/SensorNode/Sensor/SignalConditioner/AbstractSignalConditioner.o: SensorNode/Sensor/SignalConditioner/AbstractSignalConditioner.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	SensorNode/BatteryAccess.h \
	SensorNode/Sensor/SignalConditioner/AbstractSignalConditioner.h \
	SensorNode/SensorNode.h
$O/SensorNode/Sensor/SignalConverter/AbstractSignalConverter.o: SensorNode/Sensor/SignalConverter/AbstractSignalConverter.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	SensorNode/BatteryAccess.h \
	SensorNode/Sensor/SignalConverter/AbstractSignalConverter.h \
	SensorNode/SensorNode.h
$O/SensorNode/Sensor/Transducer/AbstractTransducer.o: SensorNode/Sensor/Transducer/AbstractTransducer.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	SensorNode/BatteryAccess.h \
	SensorNode/Sensor/Transducer/AbstractTransducer.h \
	SensorNode/SensorNode.h
$O/SimpleSensorData/SimpleSensorData.o: SimpleSensorData/SimpleSensorData.cc \
	SimpleSensorData/SimpleSensorData.h
$O/StatisticsInterface/StatisticsInterface.o: StatisticsInterface/StatisticsInterface.cc \
	ExtendedMessage/ExtendedMessage_m.h \
	StatisticsInterface/StatisticsInterface.h
$O/WorldModel/CustomWorldUtility.o: WorldModel/CustomWorldUtility.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/inet_stub/base/Coord.h \
	$(MIXIM_PROJ)/src/inet_stub/base/INETDefs.h \
	$(MIXIM_PROJ)/src/inet_stub/util/FWMath.h \
	ExtendedMessage/ExtendedMessage_m.h \
	StatisticsInterface/StatisticsInterface.h \
	WorldModel/CustomWorldUtility.h

