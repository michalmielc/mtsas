# Struktura aplikacji

## Struktura projektu

project/
├── src/
│   ├── main.cpp
│   ├── sensors.cpp
│   ├── measurements.cpp
│   ├── processing.cpp
│   ├── statistics.cpp
│   ├── limit_detections.cpp
│   └── output.cpp
│
├── include/
│   ├── sensors.h
│   ├── measurements.h
│   ├── processing.h
│   ├── statistics.h
│   ├── limit_detections.h
│   └── output.h
│
├── data/
│   ├── sensors.txt
│   └── measurements.txt
│
├── output/
│   ├── report.txt
│   ├── processed.txt
│   └── aggregated.txt
│
|── CMakeLists.txt
└── README.md


## Opis modułów

### main
Start aplikacji aplikacji. Obsługę argumentów
programu oraz uruchamianie kolejnych etapów przetwarzania.

### sensors
Wczytanie i walidację konfiguracji czujników
z pliku `sensors.txt`.

### measurements
Wczytanie danych z `measurements.txt`,
utworzenie macierzy z wczytanymi pomiarami.

### processing
Przetwarzanie danych pomiarowych :
- kalibrację pomiarów,
- kontrolę kompletności,
- filtrację.

### statistics
Odpowiada za obliczenie statystyk dla każdego czujnika:
- minimum,
- maksimum,
- średniej,
- odchylenia standardowego,
- liczba próbek ważnych i braków
- % kompletności danych.

### limitDetections
Odpowiada za wykrywanie przekroczeń zakresów dopuszczalnych
dla poszczególnych czujników.

### output
Odpowiada za utworzenie  plików wynikowych:
- `report.txt`,
- `processed.txt`,
- `aggregated.txt`.

### data
Dane czujników i pomiarów.


# SCHEMAT

1. Wczytanie danych.					  
- 1.1 wczytanie danych z pliku sensors.txt.
      uwtorzenie tablicy struktur i wczytanie do niej danych z pliku:
	  Sensors tableSensors[sensorsCount]
		Sensors {
			//pola
			int id;
	    	string name;
		    string unit;
			double a,b;
			double min, max;}
						
					
- 1.2 wczytanie danych z  measurements.txt.
	    uwtorzenie dwóch macierzy z wynikami:
		  double tableMeasurmentsAndSensorsId [sensorsCount][assayCount]
		  oraz z wartościami bool
		  bool tableMeasurmentsAndSensorsId [sensorsCount][assayCount]
		wczytanie do nich danych z pliku measurements.txt			
		
        Utworzenie tablicy tzw join nr wiersza macierzy z plikiem konfiguracyjnym 
                            
        int tableJoinAssaysWithSensorsId [assayCount]
        czyli np  dla pomiarów:
                            
        1  pomiar1 pomair2 ...
        5  pomiar1 pomair2 ...
                        
        tableJoinAssaysWithSensorsId[0] = 1
        tableJoinAssaysWithSensorsId[1] = 5
						
	utworzenie funkcji wyszukującej findRowInMatrixMeasuremets(int id) i zwracającej nr wiersza

2. Kalibracja
   Przeliczenie odczytów i zapis w tablicy:
   double tableCalibration [sensorsCount][assayCount]

3. Kontrola kompletności
   utworzenie nowej tablicy 			    
   bool tableSensorsIsReliable[sensorsCount] 
   i sprawdzenie czy czujnik jest wiarygodny w oparciu o próg kompletności TRUE/FALSE

4. Filtracja
 - CHCIAŁBYM PRZEDYSKUTOWAĆ SZCZEGÓŁY
5. Obliczenie statystyk

6. Detekcja przekroczen

7. Uwotrzenie raportów

8. Testy
					  