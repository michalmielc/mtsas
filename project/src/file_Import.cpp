
#include "file_import.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <cmath>

int File_Import::maxSensorId(const std::string &filePath ){
    std::ifstream file(filePath);
    
    if(!file.is_open())
    {
        throw std::runtime_error("cannot open file sensors.txt");
    }

    std::string line;
    int maxId = 0;

    while(std::getline(file,line)) {

        std::size_t firstCharacter = line.find_first_not_of("\t");

        if(firstCharacter ==std::string::npos || line[firstCharacter]=='#')
        {
            continue;
        }

        std::istringstream stream (line);

        int id;

        stream >>id;

        if(id>maxId)
        {
            maxId = id;
        }

    }

    return maxId;
}

void File_Import::checkAndSplitLineSensorsFile(const std::string &line, Sensor *tableSensors ){


    std::istringstream stream(line);

    Sensor sensor {};

    //KONTROLA DANYCH CZUJNIKA
    if(!( stream >> sensor.id
        >> sensor.name
        >> sensor.unit
        >> sensor.a
        >> sensor.b
        >> sensor.min
        >> sensor.max ))
    {
        throw std::invalid_argument("INVALID SENSOR DATA");
    }

    // KONTROLA NAN I INF
    if (!std::isfinite(sensor.a) ||
        !std::isfinite(sensor.b) ||
        !std::isfinite(sensor.min) ||
        !std::isfinite(sensor.max))
    {
        throw std::invalid_argument("SENSOR VALUES MUST BE FINITE");
    }

    // KONTROLA ID CZUJNIKA
    if (sensor.id <= 0)
    {
        throw std::invalid_argument("INVALID SENSOR ID");
    }

    // KONTROLA MIN/MAX
    if (sensor.min >= sensor.max)
    {
        throw std::invalid_argument("INVALID RANGE");
    }

    // KONTROLA UNIKALNOŚCI ID
    if (tableSensors[sensor.id].id != 0)
    {
        throw std::invalid_argument("DUPLICATE SENSOR ID");
    }
tableSensors[sensor.id] = sensor;
  }

Sensor *File_Import::readSensors( const std::string &filePath, int size ){

    std::ifstream file(filePath);

    if (!file.is_open())
        {
            throw std::runtime_error("Cannot open file: " + filePath);
        }


    Sensor *tableSensors = new Sensor[size] {};
    std::string line;


    try{

        while (std::getline(file, line))
        {
            if (line.empty())
            {
                continue;
            }

            //POMINIĘCIE BIAŁYCH ZNAKÓW
            std::size_t firstCharacter = line.find_first_not_of(" \t");

            //TYLKO BIAŁE ZNAKI
            if (firstCharacter == std::string::npos ||  line[firstCharacter] == '#')
            {
                continue;
            }

            //WCZYTANIE DO TABLICY
            checkAndSplitLineSensorsFile(line,tableSensors);
        
        
        }
    }

    catch(...)
    {
        delete [] tableSensors;
        throw;
    }

    return tableSensors;
       
  }

Measurement *File_Import::readMeasurements(const std::string &filePath, int maxId) {


    std::ifstream file(filePath);

    if (!file.is_open())
        {
            throw std::runtime_error("Cannot open file: " + filePath);
        }

    // WCZYTANIE WYMIARÓW

    int rows, cols, interval;
    std::string line;    

    //file >> rows >> cols;
    //file >> interval;
    //obsługa błędu strumienia:

    if(!std::getline(file, line)) {
        throw std::invalid_argument("MISSING ROWS AND COLS");
    }

    //wartości cols rows
    std::istringstream dimValueStream(line);

    if(!(dimValueStream >> rows >>cols)) {
        throw std::invalid_argument("INVALID ROWS AND COLS");
    }

    //INTERWAŁ
    if (!std::getline(file, line))
    {
        throw std::invalid_argument("MISSING INTERVAL");
    }

    std::istringstream intervalStream(line);
    
    if (!(intervalStream >> interval))
    {
        throw std::invalid_argument("INVALID INTERVAL");
    }



    Measurement *measurements  = new Measurement(rows, cols, interval, maxId);

   try
    {
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
            if (firstCharacter == std::string::npos ||  line[firstCharacter] == '#')
            {
                continue;
            }

            //WCZYTANIE DO TABLICY

            std::istringstream stream(line);

            int id;
            stream >>id;

            if(id <= 0 || id >= maxId)
            {
                throw std::out_of_range("ID OF SENSOR IS OUT OF RANGE");
            }
        
            if(measurements->checkUniqueId(id,measurements->ptr)){

                for (int j = 0; j < cols; j++) {
                        int value;
                        
                        if(stream >> value)
                        {
                            measurements->setMeasResult(id, j, value);
                        }
                }
            }

            else {
                throw std::invalid_argument("DUPLICATED ID");
            }
        }

    }

    catch(...){
        delete measurements;
        throw;
    }
        
    return measurements;
};




