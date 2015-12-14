#include "WakeupPhyUtils.h"

#include "MiXiMAirFrame.h"
#include "PhyUtils.h"

using namespace std;

WakeupMiximRadio::WakeupMiximRadio(int numRadioStates,
			 bool recordStats,
			 int initialState,
			 Argument::mapped_type_cref minAtt, Argument::mapped_type_cref maxAtt,
			 int currentChannel, int nbChannels) :
//        MiximRadio::MiximRadio(numRadioStates,
//                recordStats,
//                 initialState,
//                minAtt, maxAtt,
//                currentChannel, nbChannels),
	radioStates(), radioChannels(), state(initialState), nextState(initialState),
	numRadioStates(numRadioStates),
	swTimes(NULL),
	minAtt(minAtt), maxAtt(maxAtt),
	rsam(mapStateToAtt(initialState)),
	currentChannel(currentChannel), nbChannels(nbChannels)
{
	assert(nbChannels > 0);
	assert(currentChannel > -1);
	assert(currentChannel < nbChannels);

	radioStates.setName("RadioState");
	radioStates.setEnabled(recordStats);
	radioStates.record(initialState);
	radioChannels.setName("RadioChannel");
	radioChannels.setEnabled(recordStats);
	radioChannels.record(currentChannel);

	// allocate memory for one dimension
	swTimes = new simtime_t* [numRadioStates];

	// go through the first dimension and
	for (int i = 0; i < numRadioStates; i++)
	{
		// allocate memory for the second dimension
		swTimes[i] = new simtime_t[numRadioStates];
	}

	// initialize all matrix entries to 0.0
	for (int i = 0; i < numRadioStates; i++)
	{
		for (int j = 0; j < numRadioStates; j++)
		{
			swTimes[i][j] = 0;
		}
	}
}

WakeupMiximRadio::~WakeupMiximRadio()
{
	// delete all allocated memory for the switching times matrix
	for (int i = 0; i < numRadioStates; i++)
	{
		delete[] swTimes[i];
	}

	delete[] swTimes;
	swTimes = 0;
}

simtime_t WakeupMiximRadio::switchTo(int newState, simtime_t_cref now)
{
    // state to switch to must be in a valid range, i.e. 0 <= newState < numRadioStates
	assert(0 <= newState && newState < numRadioStates);

	// state to switch to must not be SWITCHING
	assert(newState != SWITCHING);

	// return error value if newState is the same as the current state
	// if (newState == state) return -1;

	// return error value if WakeupMiximRadio is currently switching
	if (state == SWITCHING) return -1;


	/* REGULAR CASE */

	// set the nextState to the newState and the current state to SWITCHING
	nextState = newState;
	int lastState = state;
	state = SWITCHING;
	radioStates.record(state);

	// make entry to RSAM
	makeRSAMEntry(now, state);

	// return matching entry from the switch times matrix
	return swTimes[lastState][nextState];
}

void WakeupMiximRadio::setSwitchTime(int from, int to, simtime_t_cref time)
{
	// assert parameters are in valid range
	assert(time >= 0.0);
	assert(0 <= from && from < numRadioStates);
	assert(0 <= to && to < numRadioStates);

	// it shall not be possible to set times to/from SWITCHING
	assert(from != SWITCHING && to != SWITCHING);

	swTimes[from][to] = time;
	return;
}

void WakeupMiximRadio::endSwitch(simtime_t_cref now)
{
	// make sure we are currently switching
	assert(state == SWITCHING);

	// set the current state finally to the next state
	state = nextState;
	radioStates.record(state);

	// make entry to RSAM
	makeRSAMEntry(now, state);

	return;
}
