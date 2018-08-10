#ifndef SAVEDATA_H
#define SAVEDATA_H

#include "Horse.h"

class SaveData
{
private:
	Horse* allHorses[22];
	Horse* youngHorse;			//Horse being raised in growth mode
	Horse* matureHorse[7];		//Adult horses
	Horse* farmHorse[12];		//Retired horses living in the farm
	Horse* breedingHorse[2];	//Horses that are currently breeding. M is 0, F is 1
	byte cash[8][4];			//Cash is stored in 4 bytes
	byte playerName[20];		//Name of player 1AF0
	//byte items[8][3];			//Currently activated items for races
	//Horse* Foal[x];			//Foals available to be chosen from growth mode

public:
	//Constructors
	SaveData();
	SaveData(fstream&);

	//Function prototypes
	void overwriteData(fstream&);		//Save customized data
	void maxAllHorse();					//Give all horses the best genes
	void maxAllCash();					//Give cash to all race horses
	void printCash(int i);				//Converts cash bytes into a readable form
	void printAllData();				//Prints out all available information
	void printShortList();				//Print out a list with just the horse's name
	void writeIndividualHorse(int i);	//Save a horse's data to file
};//End class SaveData

#endif
