PCJSaveTool: main.o Horse.o SaveData.o
	g++ -o PCJSaveTool main.o Horse.o SaveData.o 
main.o: main.cpp SaveData.o
	g++ -c main.cpp
SaveData.o: SaveData.cpp SaveData.h Horse.o
	g++ -c SaveData.cpp
Horse.o: Horse.cpp Horse.h
	g++ -c Horse.cpp