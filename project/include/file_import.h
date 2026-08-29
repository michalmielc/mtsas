
#pragma once
#include<string>
#include<iostream>
#include "sensor.h"
#include <sstream>

//WCZYTANIE PLIKÓW
class File_Import
{
    public:
    //POLICZENIE WIERSZY
    int sensorCount (const std::string & filePath);

    //WCZYTANIE SENSORS.TXT
    Sensor  *readSensors( const std::string filePath, int sensorCount);

    //PODZIAŁ LINII
    bool splitLine(const std::string &line, Sensor &sensor,  Sensor const *tableSensors, int sensorCount );

    //------DO ZROBIENIA
    //WCZYTANIE MEASUREMENTS.TXT 
    void readMeasurements( const std::string filePath);
};


