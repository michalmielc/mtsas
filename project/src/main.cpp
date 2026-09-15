#include<iostream>
#include<print>
#include<file_import.h>
#include<sensor.h>
#include<measurement.h>

int main() {



    File_Import fi;
    const int MAX_ID_SENSORS = fi.maxSensorId("project/data/sensors.txt") + 1;
    Sensor *ptrSensors  = fi.readSensors("project/data/sensors.txt",MAX_ID_SENSORS);
    Measurement *ptrMeasurements = fi.readMeasurements("project/data/measurements.txt",MAX_ID_SENSORS);

    std::println ("WELCOME TO SENSOR ANALYSIS");
    std::println ("SENSORS:");
    ptrSensors->showSensorArray(ptrSensors,MAX_ID_SENSORS);

    std::println ("--------------------------");
    std::println ("MEASUREMENTS:");
    ptrMeasurements->showMeasurementsArray();
    std::println ("--------------------------");
    ptrMeasurements->showMeasurementsValidationArray();


   delete ptrMeasurements;
   
    return 0;
}