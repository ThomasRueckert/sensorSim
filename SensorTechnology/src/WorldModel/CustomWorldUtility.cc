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

#include <CustomWorldUtility.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <Coord.h>
using namespace std;

#define xmlHumidity 0
#define xmlPressure 1
#define xmlTemperature 2
#define xmlLight 3

#define folderPath "data/"
#define humidityPath "data/humidity.xml"
#define pressurePath "data/pressure.xml"
#define temperaturePath "data/temperature.xml"
#define lightPath "data/light.xml"

CustomWorldUtility::CustomWorldUtility() : BaseWorldUtility()
{
    createFiles();
    this->sizeX = 0;
    this->sizeY = 0;
    this->sizeZ = 0;

    this->temperatureArray = 0;
    this->pressureArray = 0;
    this->humidityArray = 0;
    this->lightArray = 0;

    numSent = 0;
    numReceived = 0;

    Coord *c = new Coord();
    c->x = 1;
    c->y = 2;
    c->z = 3;
}

void CustomWorldUtility::createFiles()
{
    ifstream ifile(humidityPath);
    if (!ifile.good()) {
        std::ofstream outfile (humidityPath);
        outfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><humidiy></humidiy>" << std::endl;
        outfile.close();
    } else {
    }
    ifile.close();

    ifstream ifile2(temperaturePath);
    if (!ifile2.good()) {
        std::ofstream outfile (temperaturePath);
        outfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><temperature></temperature>" << std::endl;
        outfile.close();
    } else {
    }
    ifile2.close();

    ifstream ifile3(lightPath);
    if (!ifile3.good()) {
        std::ofstream outfile (lightPath);
        outfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><light></light>" << std::endl;
        outfile.close();
    } else {
    }
    ifile3.close();

    ifstream ifile4(pressurePath);
    if (!ifile4.good()) {
        std::ofstream outfile (pressurePath);
        outfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><pressure></pressure>" << std::endl;
        outfile.close();
    } else {
    }
    ifile4.close();
}

CustomWorldUtility::~CustomWorldUtility()
{
    this->destroySensorData(temperatureArray);
    this->destroySensorData(pressureArray);
    this->destroySensorData(lightArray);
    this->destroySensorData(humidityArray);
}

void CustomWorldUtility::initialize(int stage)
{
    BaseWorldUtility::initialize(stage);
    if (stage == 0) {
        noisy = par("noisy");
        ev << "Initializing World Model" << endl;

        this->sizeX = (int)par("playgroundSizeX").longValue()/par("dataGranularity").longValue();
        this->sizeY = (int)par("playgroundSizeY").longValue()/par("dataGranularity").longValue();
        this->sizeZ = (int)par("playgroundSizeZ").longValue()/par("dataGranularity").longValue();

        if (par("createData")) {
            EV << "Generating New Environment Data" << endl;
            this->generateEnvironmentData();
        } else {

            //if any of the 4 xml files doesn't exists new environment data will be created
            bool filesExist = true;
            ifstream ifile(par("xmlTemperature"));
            if (!ifile) {
                filesExist = false;
            }
            ifile.close();
            if (filesExist) {
                ifstream ifile(par("xmlPressure"));
                if (!ifile) {
                    filesExist = false;
                }
                ifile.close();
            }
            if (filesExist) {
                ifstream ifile(par("xmlHumidity"));
                if (!ifile) {
                    filesExist = false;
                }
                ifile.close();
            }
            if (filesExist) {
                ifstream ifile(par("xmlLight"));
                if (!ifile) {
                    filesExist = false;
                }
                ifile.close();
            }
            if (!filesExist) {
                EV << "Generating New Environment Data due to missing files" << endl;
                this->generateEnvironmentData();
            }
        }

        this->setTemperature();
        this->setPressure();
        this->setHumidity();
        this->setLight();
    } else if (stage == 1) {

    }
}

ExtendedMessage* CustomWorldUtility::generateMessage(const char* msgname)
{
    // Produce source and destination addresses.
    int src = getIndex();   // our module index
    int n = size();      // module vector size
    int dest = 1;//intuniform(0,n-2);
    if (dest==src) {
        throw new exception;
    }

    // Create message object and set source and destination field.
    ExtendedMessage *msg = new ExtendedMessage(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

void CustomWorldUtility::setValue(int*** &parameter, int*** &data)
{
    parameter = new int**[this->sizeX];
    for (int i = 0; i < this->sizeX; i++) {
        parameter[i] = new int*[this->sizeY];
        for (int j = 0; j < this->sizeY; j++) {
            parameter[i][j] = new int[this->sizeZ];
            for (int k = 0; k < this->sizeZ; k++) {
                parameter[i][j][k] = data[i][j][k];
            }
        }
    }
    delete[] data;
}

void CustomWorldUtility::setTemperature()
{
    int*** data = readXML(xmlTemperature);
    setValue(this->temperatureArray, data);
}

void CustomWorldUtility::setPressure()
{
    int*** data = readXML(xmlPressure);
    setValue(this->pressureArray, data);
}

void CustomWorldUtility::setHumidity()
{
    int*** data = readXML(xmlHumidity);
    setValue(this->humidityArray, data);
}

void CustomWorldUtility::setLight()
{
    int*** data = readXML(xmlLight);
    setValue(this->lightArray, data);
}

int*** CustomWorldUtility::readXML(int fileName)
{
    // get the xml from the parameter, return type cXMLElement
    cXMLElement *rootE;
    if (fileName == xmlPressure) {
        rootE = par("xmlPressure").xmlValue();
    } else if (fileName == xmlTemperature) {
        rootE = par("xmlTemperature").xmlValue();
    } else if (fileName == xmlHumidity) {
        rootE = par("xmlHumidity").xmlValue();
    } else if (fileName == xmlLight) {
        rootE = par("xmlLight").xmlValue();
    } else {
        throw new exception;
    }

    // get a vector (of type cXMLElement) with all childs of the root-tag
    cXMLElementList nListRows = rootE->getChildren();
    int amountRows = nListRows.size();

    int*** data = new int**[amountRows];
    for (int i = 0; i < amountRows; i++){
        //this is a row as cXMLElement
        cXMLElement* nListRowArray = nListRows[i];
        //this is a list of an entire row as cXMLElements
        cXMLElementList nLeafElementsList = nListRowArray->getChildren();
        int amountColumns = nLeafElementsList.size();
        data[i] = new int*[amountColumns];
        for (int j = 0; j < amountColumns; j++) {

            //this is a row as cXMLElement
            cXMLElement* nListRowArrayZ = nLeafElementsList[i];
            //this is a list of an entire row as cXMLElements
            cXMLElementList nLeafElementsListZ = nListRowArrayZ->getChildren();
            int amountColumnsZ = nLeafElementsListZ.size();
            data[i][j] = new int[amountColumnsZ];

            for (int k = 0; k < amountColumnsZ; k++) {

                int val = atoi(nLeafElementsListZ[k]->getNodeValue());
                data[i][j][k] = val;
            }
        }
    }

    return data;
}

void CustomWorldUtility::generateEnvironmentData()
{
    int size = sizeX * sizeY * sizeZ;
    string filenames[4] = {"humidity", "pressure", "temperature", "light"};

    int numberOfFiles = sizeof(filenames)/sizeof(filenames[0]);
    EV << "Starting to create files" << endl;

    for (int files = 0; files < numberOfFiles; files++) {

        ofstream myfile;

        string filename = par("basePath").stringValue();
        stringstream data;
        filename += filenames[files];
        filename += ".xml";
        char * filenameChar = new char[filename.length()];
        strcpy(filenameChar,filename.c_str());

        EV << "Creating " << filenameChar << endl;

        data << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl << "<" << filenames[files] << ">" << endl;
        int* newData;

        // Data Creation here
        if (files == xmlHumidity) {
            newData = generateHumidity(size);
        } else if (files == xmlPressure) {
            newData = generatePressure(size);
        } else if (files == xmlTemperature) {
            newData = generateTemperature(size);
        } else if (files == xmlLight) {
            newData = generateLight(size);
        }

        int counter = 0;
        for (int i = 0; i < sizeX; i++) {
            data << "<posX" << i << ">";
            for (int j = 0; j < sizeY; j++) {
                data << "<posY" << j << ">";
                for (int k = 0; k < sizeZ; k++) {
                    data << "<posZ" << k << ">" << newData[counter] << "</posZ" << k << ">";
                    counter++;
                }
                data << "</posY" << j << ">";
            }
            data << "</posX" << i << ">" << endl;
        }


        delete[] newData;

        myfile.open (filenameChar);
        data << "</" << filenames[files] << ">";
        myfile << data.str();
        myfile.close();
        delete[] filenameChar;

    }

    EV << "Done creating" << endl;

}

/**
 * generates values for the temperature on the playground
 * values will be between 10 and 30
 * unit: °C
 */
int* CustomWorldUtility::generateTemperature(int size)
{
    int* data = new int[size];
    say("Creating Data Temperature:");
    std::stringstream ss;
    for (int i = 0; i < size; i++) {
        //10 - 30
        int temp = (int)((rand() % 100)/5) + 10;
        data[i] = temp;
        ss << " " << temp;
    }
    say(ss.str().c_str());
    return data;
}

void CustomWorldUtility::say(const char * say)
{
    if (noisy) {
        ev.bubble(this, say);
    }
    EV << say << endl;
}

/**
 * generates values for the pressure on the playground
 * values will be between 995 and 1005
 * unit: hPa
 */
int* CustomWorldUtility::generatePressure(int size)
{
    int* data = new int[size];
    for (int i = 0; i < size; i++) {
        //995 - 1005
        data[i] = (int)((rand() % 100)/10) + 995;
    }
    return data;
}

/**
 * generates values for the humidity on the playground
 * values will be between 70 and 75
 * unit: %
 */
int* CustomWorldUtility::generateHumidity(int size)
{
    int* data = new int[size];
    for (int i = 0; i < size; i++) {
        //70 - 75
        data[i] = (int)((rand() % 100)/20 + 70);
    }
    return data;
}

/**
 * generates values for the light intensity on the playground
 * values will be between 10'000 and 100'000
 * unit: lx
 */
int* CustomWorldUtility::generateLight(int size)
{
    int* data = new int[size];
    for (int i = 0; i < size; i++) {
        //70 - 75
        data[i] = (int)((rand() % 100)*1000);
    }
    return data;
}


void CustomWorldUtility::updateDisplay()
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t",0,buf);
}

void CustomWorldUtility::finish()
{
    EV << "Sent:     " << numSent << endl;
    EV << "Received: " << numReceived << endl;
    EV << "Hop count, min:    " << hopCountStats.getMin() << endl;
    EV << "Hop count, max:    " << hopCountStats.getMax() << endl;
    EV << "Hop count, mean:   " << hopCountStats.getMean() << endl;
    EV << "Hop count, stddev: " << hopCountStats.getStddev() << endl;

    recordScalar("#sent", numSent);
    recordScalar("#received", numReceived);

    hopCountStats.recordAs("hop count");
}

void CustomWorldUtility::destroySensorData(int*** &arr)
{
    for (int i = 0; i < this->sizeX; i++) {
        for (int j = 0; j < this->sizeY; j++) {
            delete[] arr[i][j];
            arr[i][j] = NULL;
        }
        delete[] arr[i];
        arr[i] = NULL;
    }
    delete[] arr;
    arr = NULL;
}

int CustomWorldUtility::getValueByPosition(std::string type, Coord *position)
{
    int*** data = readXML(getEnumFromType(type));
    int dataAtPosition =
            data
                [(int)(position->x/par("dataGranularity").longValue())]
                 [(int)(position->y/par("dataGranularity").longValue())]
                  [(int)(position->z/par("dataGranularity").longValue())];
    return dataAtPosition;
}

int CustomWorldUtility::getEnumFromType(std::string type)
{
    if (type == "Humidity") return 0;
    if (type == "Pressure") return 1;
    if (type == "Temperature") return 2;
    if (type == "Light") return 3;
    throw new exception;
}
