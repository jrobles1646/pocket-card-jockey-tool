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
	for (int i = 0; i < 6; i++)
		matureHorse[i] = new Horse();

	//Get dummy horse
	dummyHorse = new Horse();

	//Get foals
	for (int i = 0; i < 5; i++)
		foal[i] = new Horse();

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

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
			items[i][j] = 0;

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
	allHorses[7] = dummyHorse;
	allHorses[8] = foal[0];
	allHorses[9] = foal[1];
	allHorses[10] = foal[2];
	allHorses[11] = foal[3];
	allHorses[12] = foal[4];
	allHorses[13] = farmHorse[0];
	allHorses[14] = farmHorse[1];
	allHorses[15] = farmHorse[2];
	allHorses[16] = farmHorse[3];
	allHorses[17] = farmHorse[4];
	allHorses[18] = farmHorse[5];
	allHorses[19] = farmHorse[6];
	allHorses[20] = farmHorse[7];
	allHorses[21] = farmHorse[8];
	allHorses[22] = farmHorse[9];
	allHorses[23] = farmHorse[10];
	allHorses[24] = farmHorse[11];
	allHorses[25] = breedingHorse[0];
	allHorses[26] = breedingHorse[1];
}//end default constructor SaveData::SaveData()

//--------------------------------------------------------------------------------------------
// Constructor to extract data from game data save
SaveData::SaveData(fstream& saveFileData)
{
	//Get growth mode horse
	youngHorse = new Horse(HorseIndex[0], saveFileData);

	//Get mature horses
	for (int i = 1; i < 7; i++)
		matureHorse[i - 1] = new Horse(HorseIndex[i], saveFileData);

	//Get dummy horse
	dummyHorse = new Horse(HorseIndex[7], saveFileData);

	//Get foals
	for (int i = 8; i < 13; i++)
		foal[i - 8] = new Horse(HorseIndex[i], saveFileData);

	//Get retired horses
	for (int i = 13; i < 25; i++)
		farmHorse[i - 13] = new Horse(HorseIndex[i], saveFileData);

	//Get breeding horses
	for (int i = 25; i < HORSE_MAX; i++)
		breedingHorse[i - 25] = new Horse(HorseIndex[i], saveFileData);

	//Set reward money from 8 horses
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
		{
			saveFileData.seekg(HorseIndex[i] + 0x188 + j);
			saveFileData.get(cash[i][j]);
		}//end loop for (int j = 0; j < 4; j++)

	//Set item inventory
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
		{
			saveFileData.seekg(HorseIndex[i] + 0x19A + j);
			saveFileData.get(items[i][j]);
		}//end loop for (int j = 0; j < 4; j++)q

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
	allHorses[7] = dummyHorse;
	allHorses[8] = foal[0];
	allHorses[9] = foal[1];
	allHorses[10] = foal[2];
	allHorses[11] = foal[3];
	allHorses[12] = foal[4];
	allHorses[13] = farmHorse[0];
	allHorses[14] = farmHorse[1];
	allHorses[15] = farmHorse[2];
	allHorses[16] = farmHorse[3];
	allHorses[17] = farmHorse[4];
	allHorses[18] = farmHorse[5];
	allHorses[19] = farmHorse[6];
	allHorses[20] = farmHorse[7];
	allHorses[21] = farmHorse[8];
	allHorses[22] = farmHorse[9];
	allHorses[23] = farmHorse[10];
	allHorses[24] = farmHorse[11];
	allHorses[25] = breedingHorse[0];
	allHorses[26] = breedingHorse[1];
}//end constructor SaveData::SaveData(fstream& saveFileData)

//--------------------------------------------------------------------------------------------
// Destructor for class SaveData
SaveData::~SaveData()
{
	for (int i = 0; i < HORSE_MAX; i++)
		delete allHorses[i];

	delete youngHorse;

	for (int i = 0; i < 6; i++)
		delete matureHorse[i];
	
	delete dummyHorse;

	for (int i = 0; i < 5; i++)
		delete foal[i];

	for (int i = 0; i < 12; i++)
		delete farmHorse[i];

	delete breedingHorse[0];
	delete breedingHorse[1];
}//end destructor SaveData::~SaveData()

//////////////////////////////////////////////////////////////////////////////////////////////
//									FUNCTION DEFINITIONS									//
//////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------
// Gathers data from this datatype and writes them into the game save data
void SaveData::overwriteData(fstream& saveFileData)
{
	//Loop through horses and overwrite individually
	for (int i = 0; i < HORSE_MAX; i++)
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
}//end member function void SaveData::overwriteData(fstream& saveFileData)

//--------------------------------------------------------------------------------------------
// Maximize stats of all horses. Speed = 255, stamina = 255, and wins = races
void SaveData::maxAllHorse()
{
	//Loop through all horses individually and max their stats
	for (int i = 0; i < HORSE_MAX; i++)
		allHorses[i]->maxStats();

	//Setting your young horse's stats will cause it to reset when it levels up,
	// so the program will change it to 70
	youngHorse->setSpeed(70);
	youngHorse->setStamina(70);

	for (int i = 8; i < 13; i++)
	{
		allHorses[i]->setSpeed(70);
		allHorses[i]->setStamina(70);
	}//end loop for (int i = 8; i < 13; i++)

}//end member function void SaveData::maxAllHorse()

//--------------------------------------------------------------------------------------------
// Maximize all cash prizes for all race horses
void SaveData::maxAllCash()
{
	//Set reward money
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 4; j++)
			cash[i][j] = (byte)0xFF;

}//end member function void SaveData::maxAllCash()

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
	printItemInventory(0);
	youngHorse->printData();
	cout << endl;

	//Output info for matured horses
	for (int i = 1; i < 7; i++)
	{
		cout << "  (#" << i + 1 << ") Mature Horse " << i << ":\n";
		cout << "     Reward Money: ";  printCash(i);
		printItemInventory(i);
		allHorses[i]->printData();
		cout << endl;
	}//end loop for (int i = 1; i < 8; i++)

	//Output info for dummy horse
	cout << "  (#8) Dummy Horse:\n";
	dummyHorse->printData();
	cout << endl;

	//Output info for foals
	for (int i = 8; i < 13; i++)
	{
		cout << "  (#" << i + 1 << ") Foal " << i - 7 << ":\n";
		allHorses[i]->printData();
		cout << endl;
	}//end loop for (int i = 8; i < 13; i++)

	//Output info for farm horses
	for (int i = 13; i < 25; i++)
	{
		cout << "  (#" << i + 1 << ") Retired Horse " << i - 12 << ":\n";
		//farmHorse[i-8]->printData();
		allHorses[i]->printData();
		cout << endl;
	}//end loop for (int i = 8; i < 20; i++)

	cout << "  (#26) Male Breeding Horse:\n";
	breedingHorse[0]->printData();
	cout << endl;

	cout << "  (#27) Female Breeding Horse:\n";
	breedingHorse[1]->printData();
	cout << endl;
	
	cout << ">====================== END OF LIST ======================<\n\n";
}//end member functionvoid SaveData::printAllData()

//--------------------------------------------------------------------------------------------
// Prints a list of names of all horses
void SaveData::printShortList()
{
	for (int i = 0; i < HORSE_MAX; i += 2)
	{
		cout << right << setfill(' ') << setw(SPACING + 1) << (i + 1) << ") " << left << setw(20) << allHorses[i]->nameToString();
		cout << (i + 2) << ") " << allHorses[i + 1]->nameToString();
		cout << endl;
	}//end loop void SaveData::printShortList()
}//end member function void SaveData::printShortList()

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
}//end member function void SaveData::printCash(int i)

//--------------------------------------------------------------------------------------------
// Gets input from from user and changes an individual horse's stats through mutator
// functions from class Horse defined in Horse.cpp
void SaveData::writeIndividualHorse(int i)
{
	unsigned short int userInput;
	cout << "=> Editing " << allHorses[i]->nameToString(); cout << " <=\n";

	cout << "   Set its appearance (current "
		 << ((int)allHorses[i]->getAppearance() & 0xFF) << "):\n";
	allHorses[i]->displayAppearanceList();
	cout << "=>";
	cin >> userInput;
	allHorses[i]->setAppearance((byte)userInput & 0xFF);

	cout << "   Set its characteristic (current "
		 << ((int)allHorses[i]->getCharacteristic() & 0xFF) << "):\n";
	allHorses[i]->displayCharacterList();
	cout << "=>";
	cin >> userInput;
	allHorses[i]->setCharacteristic((byte)userInput & 0xFF);

	cout << "   Adjust the racing style (current "
		 << ((int)allHorses[i]->getStyle() & 0xFF) << "):\n";
	allHorses[i]->displayStyleList();
	cout << "=>";
	cin >> userInput;
	allHorses[i]->setStyle((byte)userInput & 0xFF);

	cout << "   Adjust its temperament (current "
		 << ((int)allHorses[i]->getTemperament() & 0xFF) << "):\n";
	allHorses[i]->displayTemperList();
	cout << "=>";
	cin >> userInput;
	allHorses[i]->setTemperament((byte)userInput & 0xFF);

	cout << endl;

	cout << "   How many more babies can it have [0-255]? (Current "
		 << ((int)allHorses[i]->getFertility() & 0xFF) << "): ";
	cin >> userInput;
	allHorses[i]->setFertility((byte)userInput & 0xFF);

	cout << "   Adjust speed from 0-255 (current "
		 << ((int)allHorses[i]->getSpeed() & 0xFF) << "): ";
	cin >> userInput;
	allHorses[i]->setSpeed((unsigned char)userInput);

	cout << "   Adust stamina from 0-255 (current "
		 << ((int)allHorses[i]->getStamina() & 0xFF) << "): ";
	cin >> userInput;
	allHorses[i]->setStamina((byte)userInput & 0xFF);

	cout << "   Adjust amount of races participated (current "
		 << ((int)allHorses[i]->getRaces() & 0xFF) << "): ";
	cin >> userInput;
	allHorses[i]->setRaces((byte)userInput & 0xFF);

	cout << "   Adjust amount of races won (current "
		 << ((int)allHorses[i]->getWins() & 0xFF) << "): ";
	cin >> userInput;
	allHorses[i]->setWins((byte)userInput & 0xFF);

	cout << "   Adjust 1st peak time (current "
		 << ((int)allHorses[i]->getPeak1() & 0xFF) << "): ";
	cin >> userInput;
	allHorses[i]->setPeak1((byte)userInput & 0xFF);

	cout << "   Adjust 2nd peak time (current "
		 << ((int)allHorses[i]->getPeak2() & 0xFF) << "): ";
	cin >> userInput;
	allHorses[i]->setPeak2((byte)userInput & 0xFF);

	cout << endl;
	cout <<  "==>Data has been set. You can see your changes with option '1) View your horses'\n ";
}//end member function void SaveData::writeIndividualHorse(int i)

string SaveData::itemToString(byte i)
{
	switch (i)
	{
	case 0:
		return "No Item";
	case 1:
		return "(unknown)";
	case 2:
		return "Tiny Carrot";
	case 3:
		return "Lucky Gloves";
	case 4:
		return "Time Crop";
	case 5:
		return "(unkown)";
	case 6:
		return "Joker Crop";
	case 7:
		return "Sharp Sight";
	case 8:
		return "Reset Gloves";
	case 9:
		return "Future Goggles";
	case 0xA:
		return "(unknown)";
	case 0xB:
		return "Hazard Goggles";

	case 0xC:
		return "(unknown)";
	case 0xD:
		return "(unknown)";
	case 0xE:
		return "(unknown)";

	case 0xF:
		return "Quick Gloves";
	case 0x10:
		return "Stamina Carrot";
	case 0x11:
		return "Stamina Carrot Z";
	default:
		return "No Item";
	}//end switch (i)
}//end member function string SaveData::itemToString(byte i)

//--------------------------------------------------------------------------------------------
// 
void SaveData::displayItemList()
{
	cout << "0) No item" << "\t" << "1) (unknown)" << "\t" << "2) Tiny Carrot" << endl;
	cout << "3) Lucky Gloves" << "\t" << "4) Time Crop" << "\t" << "5) (unknown)" << endl;
	cout << "6) Joker Crop" << "\t" << "7) Sharp Sight" << "\t" << "8) Reset Gloves" << endl;
	cout << "9) Future Goggles" << "\t" << "10) (unknown)" << "\t" << "11) Hazard Goggles" << endl;
	cout << "12) (unknown)" << "\t" << "13) (unknown)" << "\t" << "14) (unknown)" << endl;
	cout << "15) Quick Gloves" << "\t" << "16) Stamina Carrot" << "\t" << "17) Stamina Carrot Z" << endl;

}//end member function void SaveData::displayItemList()

//--------------------------------------------------------------------------------------------
// 
void SaveData::printItemInventory(int i)
{
	if (items[i][3] == (byte)0)
	{
		cout << "     No items\n";
		return;
	}


	cout << "     " << ((unsigned int)items[i][3] & 0xFF) << " items: ";
	for (int j = 0; byte(j) < items[i][3]; j++)
		cout << itemToString(items[i][j]) << "\t";
	cout << endl;
}//end member function void SaveData::printItemInventory()

//--------------------------------------------------------------------------------------------
// 
void SaveData::editItems()
{//TEMPORARY FUNCTION
	//Set item inventory
	for (int i = 0; i < 8; i++)
	{
		items[i][0] = (byte)0x6;	//lucky gloves
		items[i][1] = (byte)0x3;	//joker crop
		items[i][2] = (byte)0x11;	//stamina carrot z
		items[i][3] = (byte)0x3;	//inventory amount = 3
	}//end loop	for (int i = 0; i < 8; i++)
}//end member function void SaveData::editItems()