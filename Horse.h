#ifndef HORSE_H
#define HORSE_H

//////////////////////////////////////////////////////////////////////////////////////////////
//								INCLUDED HEADERS/LIBRARIES									//
//////////////////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
//								TYPEDEFS AND GLOBAL CONSTANTS								//
//////////////////////////////////////////////////////////////////////////////////////////////
typedef char byte;

//There are a total of 22 horses in the save data, excluding newborn foals
static const int HORSE_MAX = 22;

//Array of offsets where horses are stored in memory
static unsigned short int HorseIndex[HORSE_MAX] = {
	//Growth Mode Horse
	0x10,
	//Mature Mode Horses
	0x1C0, 0x370, 0x520, 0x6D0, 0x880, 0xA30, 0xBE0,
	//Farm Horses
	0x2900, 0x2A40, 0x2B80, 0x2CC0, 0x2E00, 0x2F40,
	0x3080, 0x31C0, 0x3300, 0x3440, 0x3580, 0x36C0,
	//M, F breeders
	0x3800 , 0x3940 };

const int SPACING = 2;

//////////////////////////////////////////////////////////////////////////////////////////////
//									CLASS DEFINITIONS										//
//////////////////////////////////////////////////////////////////////////////////////////////

class Horse
{
private:
	byte speed;
	byte stamina;
	byte wins;
	byte races;
	byte peak1;
	byte peak2;
	byte name[32];	//16 characters per name
	//appearance;
	//gender;
	//characteristic;
	//style;		//0-4
	//skill1;		//About 30 skills?
	//skill2;
	//temperament; //0-4

public:
	//Constructors
	Horse();	
	Horse(byte, byte, byte, byte, byte, byte, byte[]);
	Horse(unsigned short int, fstream&);

	//Function prototypes
	void printName();
	void printData();
	void writeData(unsigned short int, fstream&);
	void maxStats();

	//Mutator function prototypes
	void setSpeed(byte);
	void setStamina(byte);
	void setWins(byte);
	void setRaces(byte);
	void setPeak1(byte);
	void setPeak2(byte);
	//void setName(byte[]);

	//Accessor function prototypes
	byte getSpeed();
	byte getStamina();
	byte getWins();
	byte getRaces();
	byte getPeak1();
	byte getPeak2();
};//end class Horse

#endif
