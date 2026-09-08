#include  "sensor.h"
#include  <print>

void Sensor::showSensorArray(Sensor* ptrSensors, int counter){

    std::println(
    "{:<6} {:<15} {:<8} {:>10} {:>10} {:>10} {:>10}",
    "ID", "NAME", "UNIT", "A", "B", "MIN", "MAX"
);
    for (int i = 0; i < counter; i++)
    {
        std::println(
        "{:<6} {:<15} {:<8} {:>10.4f} {:>10.4f} {:>10.2f} {:>10.2f}", 
        ptrSensors[i].id,
        ptrSensors[i].name,
        ptrSensors[i].unit,
        ptrSensors[i].a,
        ptrSensors[i].b,
        ptrSensors[i].min,
        ptrSensors[i].max
        ) ;
    }
}