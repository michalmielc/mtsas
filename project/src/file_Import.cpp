
#include "file_import.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>

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

    //KONTORLA ID CZUJNIKA
    if(sensor.id <=0 || sensor.id > std::numeric_limits<int>::max()) 
    {
        throw std::invalid_argument("INVALID SENSOR ID");
    }   

    // KONTROLA MIN MAX DOP
    if(sensor.min >= sensor.max) 
    {
        throw std::invalid_argument("INVALID RANGE");
    }   

    //KONTROLA UNIKALNOŚCI IDENTYFIKATORÓW

    if (tableSensors[sensor.id].id !=0)
    {
        throw std::invalid_argument("DUPLICATE SENSOR ID");
    }
    
    //WPROWADZENIE DANYCH DO MACIERZY
    else{
        tableSensors[sensor.id] = sensor;
    }

  }

Sensor *File_Import::readSensors( const std::string &filePath, int size ){


    Sensor *tableSensors = new Sensor[size] {};

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
        if (firstCharacter == std::string::npos ||  line[firstCharacter] == '#')
        {
            continue;
        }

        //WCZYTANIE DO TABLICY
         checkAndSplitLineSensorsFile(line,tableSensors);
    
       
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

    file >> rows >> cols;
    file >> interval;

    Measurement *measurements  = new Measurement(rows, cols, interval, maxId);


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

        if(id>maxId)
        {
            throw std::out_of_range("ID OF SENSOR IS OUT OF RANGE");
        }
       
        if(measurements->checkUniqueId(id,measurements->ptr)){

            for (int j = 0; j < cols; j++) {
                    int value;
                    stream >> value;

                    measurements->setMeasResult(id, j, value);

            }
        }
    }


        
    return measurements;
};




