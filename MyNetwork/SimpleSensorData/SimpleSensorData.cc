/*
 * SimpleSensorData.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: rutho
 */

#include <SimpleSensorData/SimpleSensorData.h>

SimpleSensorData::SimpleSensorData() {
    sensorData = 0;
    sizeX = 0;
    sizeY = 0;
}

SimpleSensorData::~SimpleSensorData() {
    for (int i = 0; i < this->sizeX; i++) {
        delete[] sensorData[i];
    }
    //delete[] sensorData;
    this->sizeX = 0;
    this->sizeY = 0;
}


SimpleSensorData::SimpleSensorData(const char *name, int** sensorData, int sizeX, int sizeY, bool namepooling) : cNamedObject(name, namepooling)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->sensorData = sensorData;
}

