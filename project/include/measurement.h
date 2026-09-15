#pragma once
#include<stdexcept>
#include <limits>



struct Measurement

{
   int rows;
   int cols;
   int interval;
   int maxId;
   static const int NOT_VALID_ATTEPT = -9999;
   
   int **values;
   bool **isValid;
    int* ptr;    


   //UWTORZENIE MACIERZY POMIAROW I WAŻNOSCI
   Measurement (int r, int c, int itv, int maxIdSensors)
   {
       validation( r,  c,  itv,  maxIdSensors);

      rows = r;
      cols = c;
      interval = itv;
      maxId = maxIdSensors;

       ptr = new int[maxId]{};

      values = new int*[maxId];
      isValid = new bool*[maxId];
      
      for (int i = 0; i < maxId; i++)
      {
         values[i] = new int[cols]{};
         isValid[i] = new bool[cols]{};
      }
      
   }

   //DESTRUKTOR
   ~Measurement(){
      
      
      for (int i = 0; i < maxId; i++)
      {
         delete [] values[i];
         delete [] isValid[i];
      }

      delete [] values;
      delete [] isValid;
      delete[] ptr;


      values = nullptr;
      isValid = nullptr;
      ptr = nullptr;
   }

   //VALIDATION
   void validation(int r, int c, int i, int maxIdSensors){
      
      if(r>std::numeric_limits<int>::max() || r <0)
      {
         throw std::invalid_argument("INAVLID VALUE OF ROWS");

      }

      if(c>std::numeric_limits<int>::max() || c <0)
      {
         throw std::invalid_argument("INAVLID VALUE OF COLS");
         
      }


      if(i>std::numeric_limits<int>::max() || i <0)
      {
         throw std::invalid_argument("INAVLID VALUE OF INTERVAL");
         
      }

      if(maxIdSensors>std::numeric_limits<int>::max() || maxIdSensors <=0)
      {
         throw std::invalid_argument("INAVLID VALUE MAX_ID_OF_SENSORS");
         
      }
   
   }

   //SPRAWDZENIE UNKALNOŚCI ID
   bool checkUniqueId(int id, int *ptr)
   {
      if(ptr[id]==0){
         ptr[id]=1;
         return true;
      }
      else {
          return false;
      }
   }

   //ZAPISANIE WYNIKU DO WIERSZA MACIERZY
   void setMeasResult(int row, int col, int value){
      
      values[row][col] = value;
      
      if(NOT_VALID_ATTEPT==value) {
         isValid[row][col]=false;
      }
      else{
         isValid[row][col]=true;
      }

   } 
   
   //WYŚWIETLENIE MACIERZY POMIARÓW
  void showMeasurementsArray();

   //WYŚWIETLENIE MACIERZY WAŻNOŚCI POMIARÓW
  void showMeasurementsValidationArray();
};

