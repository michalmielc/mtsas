#pragma once
struct Measurement

{
   int rows;
   int cols;
   int interval;
   int maxId;
   const int NOT_VALID_ATTEPT = -9999;
   
   int **values;
   bool **isValid;

   //UWTORZENIE MACIERZY POMIAROW I WAŻNOSCI
   Measurement (int r, int c, int i, int maxIdSensors)
   {
     
      rows = r;
      cols = c;
      interval = i;
      maxId = maxIdSensors;

      values = new int*[maxId];
      isValid = new bool*[maxId];
      
      for (int i = 0; i < maxId; i++)
      {
         values[i] = new int[cols]{};
         isValid[i] = new bool[cols]{};
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

