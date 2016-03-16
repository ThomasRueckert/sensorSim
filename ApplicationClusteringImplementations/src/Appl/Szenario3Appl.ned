package applicationclusteringimplementations.Appl;

import org.mixim.base.modules.IBaseApplLayer;

//
// TODO auto-generated type
//
simple Szenario3Appl extends CustomDiceApplication like IBaseApplLayer
{
    parameters:
        int sendingIntervall @unit("s");
        int wakeupIntervall @unit("s");
        
        @class(Szenario3Appl);
    gates:
}
