# Struktura aplikacji

## Struktura projektu

project/
├── src/
| 	├── fileImport.h
│   ├── main.cpp
│   ├── sensor.cpp
│   ├── measurement.cpp
│   ├── processing.cpp
│   ├── statistic.cpp
│   ├── limit_detection.cpp
│   └── output.cpp
│
├── include/
|   ├── fileImport.h
│   ├── sensor.h
│   ├── measurement.h
│   ├── processing.h
│   ├── statistic.h
│   ├── limit_detection.h
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
	Wczytanie odbywa się poprzez klasę file_import.		
    Uwtorzenie tablicy struktur i wczytanie do niej danych z pliku:
	  Sensors tableSensors[sensorsCount]
		Sensors {
			//pola
			int id;
	    	string name;
		    string unit;
			double a,b;
			double min, max;}

Przy czym każdy wiersz tablicy odpowiada nr czujnika.
Tablica jest wyzerowana w miejscach, gdzie nr wiersza nie odpowiada żadnemu id czujnika.

- 1.2 wczytanie danych z  measurements.txt.
Wczytanie odbywa się poprzez klasę file_import do struktury Measurement.

uwtorzenie dwóch macierzy z wynikami oraz z wartościami bool:
**values, **isValid;
		
Gdzie numer wiersza odpowiada numerowi czujnika.

--------------------------------------------------------------------------------		
PYTANIA DO KRZYSZTOFA:

 - nie robiłem walidacji a,b, min, max w sensie czy jest double np dczy ktoś nie wpisał znaku, litery etc
 - czy pomiary mogą się powtarzac dla czujnika ( więcej niż w jednym wierszu ). Nie ma o tym słowa w opisie

--------------------------------------------------------------------------------


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
					  