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

#include <LeafClusterAppl.h>
#include <FindModule.h>


Define_Module(LeafClusterAppl);

LeafClusterAppl::LeafClusterAppl() {
    // TODO Auto-generated constructor stub

}

LeafClusterAppl::~LeafClusterAppl() {
    // TODO Auto-generated destructor stub
}

void LeafClusterAppl::initialize(int stage) {
    if (stage == 1) {
        battery = FindModule<SimpleBattery*>::findSubModule(findHost());
//        double volt = battery->getVoltage();
//        double rel = battery->estimateResidualRelative();
//        double abs = battery->estimateResidualAbs();
    }
}

void LeafClusterAppl::handleMessage(cMessage* msg) {
    if (msg) {
        double rel = battery->estimateResidualRelative();
    }
}
