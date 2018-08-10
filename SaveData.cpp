#include "SaveData.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//										CONSTRUCTORS										//
//////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------
// Default constructor. This should not be used
SaveData::SaveData()
{
	//Get growth mode horse
	youngHorse = new Horse();

	//Get mature horses
	for (int i = 0; i < 7; i++)
		matureHorse[i] = new Horse();

	//Get retired horses
	for (int i = 0; i < 12; i++)
		farmHorse[i] = new Horse();

	//Get breeding horses
	for (int i = 0; i < 2; i++)
		breedingHorse[i] = new Horse();

	//Set reward money
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
			cash[i][j] = 0;

	//Set player name
	for (int i = 0; i < 20; i++)
		playerName[i] = 0;

	//Set pointers for easy reference
	allHorses[0] = youngHorse;
	allHorses[1] = matureHorse[0];
	allHorses[2] = matureHorse[1];
	allHorses[3] = matureHorse[2];
	allHorses[4] = matureHorse[3];
	allHorses[5] = matureHorse[4];
	allHorses[6] = matureHorse[5];
	allHorses[7] = matureHorse[6];
	allHorses[8] = farmHorse[0];
	allHorses[9] = farmHorse[1];
	allHorses[10] = farmHorse[2];
	allHorses[11] = farmHorse[3];
	allHorses[12] = farmHorse[4];
	allHorses[13] = farmHorse[5];
	allHorses[14] = farmHorse[6];
	allHorses[15] = farmHorse[7];
	allHorses[16] = farmHorse[8];
	allHorses[17] = farmHorse[9];
	allHorses[18] = farmHorse[10];
	allHorses[19] = farmHorse[11];
	allHorses[20] = breedingHorse[0];
	allHorses[21] = breedingHorse[1];
}//end default constructor SaveData::SaveData()

//--------------------------------------------------------------------------------------------
// Constructor to extract data from game data save
SaveData::SaveData(fstream& saveFileData)
{
	//Get growth mode horse
	youngHorse = new Horse(HorseIndex[0], saveFileData);

	//Get mature horses
	for (int i = 1; i < 8; i++)
		matureHorse[i - 1] = new Horse(HorseIndex[i], saveFileData);

	//Get retired horses
	for (int i = 8; i < 20; i++)
		farmHorse[i - 8] = new Horse(HorseIndex[i], saveFileData);

	//Get breeding horses
	for (int i = 20; i < 22; i++)
		breedingHorse[i - 20] = new Horse(HorseIndex[i], saveFileData);

	//Set reward money from 8 horses
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
		{
			saveFileData.seekg(HorseIndex[i] + 0x188 + j);
			saveFileData.get(cash[i][j]);
		}//end loop for (int j = 0; j < 4; j++)

	//Get player name
	for (int i = 0; i < 20; i++)
	{
		saveFileData.seekg(0x1AF0 + i);
		saveFileData.get(playerName[i]);
	}//end loop for (int i = 0; i < 20; i++)

	//Set pointers for easier reference
	allHorses[0] = youngHorse;
	allHorses[1] = matureHorse[0];
	allHorses[2] = matureHorse[1];
	allHorses[3] = matureHorse[2];
	allHorses[4] = matureHorse[3];
	allHorses[5] = matureHorse[4];
	allHorses[6] = matureHorse[5];
	allHorses[7] = matureHorse[6];
	allHorses[8] = farmHorse[0];
	allHorses[9] = farmHorse[1];
	allHorses[10] = farmHorse[2];
	allHorses[11] = farmHorse[3];
	allHorses[12] = farmHorse[4];
	allHorses[13] = farmHorse[5];
	allHorses[14] = farmHorse[6];
	allHorses[15] = farmHorse[7];
	allHorses[16] = farmHorse[8];
	allHorses[17] = farmHorse[9];
	allHorses[18] = farmHorse[10];
	allHorses[19] = farmHorse[11];
	allHorses[20] = breedingHorse[0];
	allHorses[21] = breedingHorse[1];

}//end constructor SaveData::SaveData(fstream& saveFileData)

//////////////////////////////////////////////////////////////////////////////////////////////
//									FUNCTION DEFINITIONS									//
//////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------
// Gathers data from this datatype and writes them into the game save data
void SaveData::overwriteData(fstream& saveFileData)
{
	//Loop through horses and overwrite individually
	for (int i = 0; i < 22; i++)
		allHorses[i]->writeData(HorseIndex[i], saveFileData);

	//Set reward money to save file
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			saveFileData.seekp(HorseIndex[i] + 0x188 + j);
			saveFileData.write(&cash[i][j], 1);
		}//end loop for (int j = 0; j < 4; j++)
	}//end loop for (int i = 0; i < 8; i++)
}//end function void SaveData::overwriteData(fstream& saveFileData)

//--------------------------------------------------------------------------------------------
// Maximize stats of all horses. Speed = 255, stamina = 255, and wins = races
void SaveData::maxAllHorse()
{
	//Loop through all horses individually and max their stats
	for (int i = 0; i < 22; i++)
		allHorses[i]->maxStats();

	//Setting your Growth Mode horse with high stats causes it to reset
	// if it's too high, so we will set spd and stmna to 70
	youngHorse->setSpeed(70);
	youngHorse->setStamina(70);

}//end function void SaveData::maxAllHorse()

//--------------------------------------------------------------------------------------------
// Maximize all cash prizes for all race horses
void SaveData::maxAllCash()
{
	//Set reward money
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
			cash[i][j] = 0xFF;

}//end function void SaveData::maxAllCash()

//--------------------------------------------------------------------------------------------
// Prints out a report of the game save data stored in this data type
void SaveData::printAllData()
{
	cout << ">======================== HORSE LIST ======================<\n";
	//Print player's name
	if (playerName[0] == 0)
		cout << "No player name found. Has this save data been initialized?\n";
	else
	{
		cout << "Player Name: ";
		for (int i = 0; i < 20; i += 2)
		{//TODO: This loop only works for ASCII characters
			if (playerName[i] == 0)
				break;
			cout << playerName[i];
		}//end for (int i = 0; i < 20; i += 2)
		cout << endl;
	}//end conditional else
	cout << endl;

	cout << "  (#1) Growth Mode Horse:\n";
	cout << "     Reward Money: "; printCash(0);
	youngHorse->printData();
	cout << endl;

	//Output info for matured horses
	for (int i = 1; i < 8; i++)
	{
		cout << "  (#" << i + 1 << ") Mature Horse " << i << ":\n";
		cout << "     Reward Money: ";  printCash(i);
		//matureHorse[i-1]->printData();
		allHorses[i]->printData();
		cout << endl;
	}//end loop for (int i = 1; i < 8; i++)

	//Output info for farm horses
	for (int i = 8; i < 20; i++)
	{
		cout << "  (#" << i + 1 << ") Retired Horse " << i - 7 << ":\n";
		//farmHorse[i-8]->printData();
		allHorses[i]->printData();
		cout << endl;
	}//end loop for (int i = 8; i < 20; i++)

	cout << "  (#21) Male Breeding Horse:\n";
	breedingHorse[0]->printData();
	cout << endl;

	cout << "  (#22) Female Breeding Horse:\n";
	breedingHorse[1]->printData();
	cout << endl;
	
	cout << ">====================== END OF LIST ======================<\n\n";
}//end functionvoid SaveData::printAllData()

//--------------------------------------------------------------------------------------------
// Prints a list of names of all horses
void SaveData::printShortList()
{
	for (int i = 0; i < 22; i += 2)
	{
		cout << setw(2) << (i + 1) << ") ";
		allHorses[i]->printName();
		cout  << " | ";
		cout << (i + 2) << ") ";
		allHorses[i + 1]->printName();
		cout << endl;
	}//end loop void SaveData::printShortList()
}//end function void SaveData::printShortList()

//--------------------------------------------------------------------------------------------
// Converts cash bytes (little endian) from hexadecimal to decimal, then from raw decimal
// to money format ($xx.xx), then prints it out
void SaveData::printCash(int i)
{
	unsigned int rawVal =
		(unsigned int)
		((cash[i][3] * 16777216) +
		(cash[i][2] * 65536) +
		(cash[i][1] * 256) +
		cash[i][0]);

	cout << "$" << rawVal / 100 << "." << setfill('0') << setw(2) << rawVal % 100 << endl;
}//end function void SaveData::printCash(int i)

//--------------------------------------------------------------------------------------------
// Gets input from from user and changes an individual horse's stats through mutator
// functions from class Horse defined in Horse.cpp
void SaveData::writeIndividualHorse(int i)
{
	unsigned short int userInput;
	cout << "=> Editing "; allHorses[i]->printName(); cout << ": <=\n";

	cout << "   Adjust speed from 0-255 (current " << ((int)allHorses[i]->getSpeed() & 0xFF) << "): ";
	cin >> userInput;
	allHorses[i]->setSpeed((unsigned char)userInput);

	cout << "   Adust stamina from 0-255 (current " << ((int)allHorses[i]->getStamina() & 0xFF) << "): ";
	cin >> userInput;
	allHorses[i]->setStamina((byte)userInput & 0xFF);

	cout << "   Adjust amount of races won (current " << ((int)allHorses[i]->getWins() & 0xFF) << "): ";
	cin >> userInput;
	allHorses[i]->setWins((byte)userInput & 0xFF);

	cout << "   Adjust amount of races participated (current " << ((int)allHorses[i]->getRaces() & 0xFF) << "): ";
	cin >> userInput;
	allHorses[i]->setRaces((byte)userInput & 0xFF);

	cout << "   Adjust 1st peak time (current " << ((int)allHorses[i]->getPeak1() & 0xFF) << "): ";
	cin >> userInput;
	allHorses[i]->setPeak1((byte)userInput & 0xFF);

	cout << "   Adjust 2nd peak time (current " << ((int)allHorses[i]->getPeak2() & 0xFF) << "): ";
	cin >> userInput;
	allHorses[i]->setPeak2((byte)userInput & 0xFF);

	cout << setw(SPACING) << "Data has been set. You can see your changes with option '1) View your horses'\n ";
}//end function void SaveData::writeIndividualHorse(int i)