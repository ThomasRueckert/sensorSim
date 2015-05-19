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

#include <Memory.h>

#define error -9999
#define emptyTime -1

Memory::Memory() : empty({"", error, emptyTime}) {
    const storage emptyStorage = {"", error, emptyTime};
    storageDataSets = 0;
    //empty = emptyStorage;
}

Memory::~Memory() {
    delete[] measureDataStorage;
    measureDataStorage = NULL;
}

void Memory::initialize(int stage)
{
    BatteryAccess::initialize(stage);

    storageSize = par("storageSize");

    const storage emptyStorage = {"", error, emptyTime};
    measureDataStorage = new storage[storageSize];
    for (int i = 0; i < storageSize; i++) {
        measureDataStorage[i] = empty;
    }
}

void Memory::handleMessage(cMessage *msg)
{
    EV << "<Memory>" << endl;
    const char* name = msg->getName();
    std::string nameString = name;
    if (nameString == "readAllAndClear") {

        say("Clearing Storage");
        EV << "storage before cleaning:" << endl;
        printStorage();
        cMessage* returnMessage = new cMessage("storageContent");
        int count = storageDataSets;
        storage* returnData = readAllAndClear();
        for (int i = 0; i < count; i++) {
            SimpleSensorData* data = new SimpleSensorData(
                    returnData[i].type.c_str(),
                    returnData[i].value,
                    returnData[i].timeCreated
                    );
            returnMessage->getParList().add(data);
        }
        send(returnMessage, "connectToProcessor$o");

        say("Cleaning done");
        EV << "storage after cleaning:" << endl;
        printStorage();

    } else {

        SimpleSensorData* data = (SimpleSensorData*) msg->getParList().remove(name);
        int value = data->sensorData;

        std::stringstream ss; ss << "Memory: Got type: " << name << " with value:" << value << endl;
        say(ss.str());
        if (readEntry(nameString).value == error) {
            createEntry(nameString, value);
            EV << "New storage entry created." << endl;
        } else if (storageDataSets < storageSize) {
            createEntry(nameString, value);
            EV << "New storage entry created." << endl;
        } else {
            updateEntry(nameString, value);
            EV << "Storage entry updated." << endl;
        }
        printStorage();
    }
    delete(msg);
    draw();
    EV << "</Memory>" << endl;
}

storage* Memory::readAllAndClear()
{
    storage *returnDataSet = new storage[storageDataSets];
    int counter = 0;
    int pos = 0;
    for (int i = 0; (i < storageSize && storageDataSets > 0); i++) {
        if (measureDataStorage[i].value != error) {
            returnDataSet[counter] = measureDataStorage[i];
            counter++;
            deleteEntry(i);
        }
    }
    return returnDataSet;
}

void Memory::createEntry(std::string type, int value)
{
    int emptyId = -1;
    for (int i = 0; i < storageSize; i++) {
        if (measureDataStorage[i].type == "") {
            emptyId = i;
            break;
        }
    }
    if (emptyId == -1) {
        return;
    }
    measureDataStorage[emptyId].type = type;
    measureDataStorage[emptyId].value = value;
    measureDataStorage[emptyId].timeCreated = simTime();

    storageDataSets++;
}

storage Memory::readEntry(std::string type)
{
    int id = getIdByType(type);
    if (id == -1) {
        return empty;
    }
    return measureDataStorage[id];
}

storage Memory::readEntry(int id)
{
    return measureDataStorage[id];
}

void Memory::updateEntry(std::string type, int value)
{
    int id = getIdByType(type);
    if (id == -1) {
        return createEntry(type, value);
    }
    measureDataStorage[id].value = value;
    measureDataStorage[id].timeCreated = simTime();
}

void Memory::deleteEntry(std::string type)
{
    int id = getIdByType(type);
    if (id < storageSize && id >= 0) {
        measureDataStorage[id] = {"", error, emptyTime};
        storageDataSets--;
    }
}

void Memory::deleteEntry(int id)
{
    if (id < storageSize && id >= 0) {
        measureDataStorage[id] = {"", error, emptyTime};
        storageDataSets--;
    }
}

int Memory::getIdByType(std::string type)
{
    int id = -1;
    for (int i = 0; i < storageSize; i++) {
        if (measureDataStorage[i].type == type) {
            id = i;
            break;
        }
    }
    return id;
}

void Memory::printStorage()
{
    for (int i = 0; i < storageSize; i++)
    {
        EV << i << ": " << measureDataStorage[i].type
                << ", " << measureDataStorage[i].value
                << ", " << measureDataStorage[i].timeCreated.str()
                << endl;
    }
}
