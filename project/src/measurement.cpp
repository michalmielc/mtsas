#include "measurement.h"
#include <iostream>

  void Measurement::showMeasurementsArray(){

    for (int i = 0; i < maxId; i++)
    {
        for (int j = 0; j < cols; j++)
        {
             std::cout << values[i][j] << "\t";
        }  

        std::cout << "\n";
    }
}


  void Measurement::showMeasurementsValidationArray(){


    for (int i = 0; i < maxId; i++)
    {
        for (int j = 0; j < cols; j++)
        {
             std::cout << std::boolalpha << isValid[i][j] << "\t";
        }  
        
        std::cout << "\n";
    }
}