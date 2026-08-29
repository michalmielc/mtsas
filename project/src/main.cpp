#include<iostream>
#include<print>
#include<file_import.h>
#include<sensor.h>

int main() {

std::println ("WELCOME TO SENSOR ANALYSIS");

File_Import fi;

int sensorCount  = fi.sensorCount("project/data/sensors.txt");
Sensor *ptrSensors  = fi.readSensors("project/data/sensors.txt",sensorCount);

for (int i = 0; i < sensorCount; i++)
{
    std::println("{} {} {} {} {}", 
        ptrSensors[i].id,
        ptrSensors[i].name,
        ptrSensors[i].unit,
        ptrSensors[i].a,
        ptrSensors[i].b,
        ptrSensors[i].min,
        ptrSensors[i].max
    ) ;
}


return 0;
}