
#include "file_import.h"
#include <fstream>
#include <stdexcept>

int File_Import::sensorCount (const std::string & filePath){

     std::ifstream file(filePath);

    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }

    std::string line;
    int count = 0;

    while (std::getline(file, line))
    {
        std::size_t firstCharacter = line.find_first_not_of(" \t");

        if (firstCharacter == std::string::npos)
        {
            continue;
        }

        if (line[firstCharacter] == '#')
        {
            continue;
        }

        count++;
    }

    return count;
}

bool File_Import::splitLine(const std::string &line, Sensor &sensor,  Sensor const *tableSensors, int index ){

    std::istringstream stream(line);
    stream >> sensor.id
        >> sensor.name
        >> sensor.unit
        >> sensor.a
        >> sensor.b
        >> sensor.min
        >> sensor.max;

    //KONTORLA ID CZUJNIKA
    if(sensor.id <=0) 
    {
        throw std::invalid_argument("INVALID SENSOR ID");
    }   

    // KONTROLA MIN MAX DOP
    if(sensor.min >= sensor.max) 
    {
        throw std::invalid_argument("INVALID RANGE");
    }   

    //KONTROLA UNIKALNOŚCI IDENTYFIKATORÓW

    for (int i = 0; i < index; i++)
    {
        if(sensor.id==tableSensors[i].id)
        {
                throw std::invalid_argument("DUPLICATE SENSOR ID");
        }
    }
    

       return true;
  }

Sensor *File_Import::readSensors( const std::string filePath, int sensorCount ){

    int index = 0;

    Sensor *tableSensors = new Sensor[sensorCount];
    Sensor tempSensor;  

    std::ifstream file(filePath);

    if (!file.is_open())
        {
            throw std::runtime_error("Cannot open file: " + filePath);
        }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        //POMINIĘCIE BIAŁYCH ZNAKÓW
        std::size_t firstCharacter = line.find_first_not_of(" \t");

        //TYLKO BIAŁE ZNAKI
        if (firstCharacter == std::string::npos)
        {
            continue;
        }

        //POMINIĘCIE KOMENTARZA
        if (line[firstCharacter] == '#')
        {
            continue;
        }

       if( splitLine(line,tempSensor,tableSensors, index))
       {
        tableSensors[index] = tempSensor;
        index ++;

       }

       
    }

    return tableSensors;
       
  }


    