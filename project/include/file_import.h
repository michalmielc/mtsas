
#pragma once
#include<string>
#include<iostream>
#include "sensor.h"
#include "measurement.h"
#include <sstream>

//WCZYTANIE PLIKÓW
class File_Import
{
    public:
    //POLICZENIE WIERSZY SPRAWDZIĆ PÓŹNIEJ, CZY SIĘ PRZYDA
    //int sensorCount (const std::string & filePath);

    //MAKSYMALNY INDEKS TABLICY
    int maxSensorId(const std::string &filePath);

    //WCZYTANIE SENSORS.TXT NR WIERSZA ODPOWIADA ID CZUJNIKA
    Sensor *readSensors( const std::string filePath, int maxId);

    //SPRAWDZENIE LINII I WPISANIE DO MACIERZY SENSORÓW
    void checkAndSplitLineSensorsFile(const std::string &line,  Sensor *tableSensors );

    //WCZYTANIE MEASUREMENTS.TXT 
    Measurement *readMeasurements(const std::string filePath, int maxId);
};


