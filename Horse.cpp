#include "Horse.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//										CONSTRUCTORS										//
//////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------
// Default constructor for class Horse
Horse::Horse()
{
	speed = 20;
	stamina = 20;
	wins = 0;
	races = 0;
	peak1 = 1;
	peak2 = 1;


	for (int i = 0; i < 32; i++)
		name[i] = 0;
}//end default constructor Horse::Horse()

//--------------------------------------------------------------------------------------------
// Constructor for class Horse. Initialize its stats as defined by the parameters
Horse::Horse(byte spd, byte stmna, byte w, byte r, byte p1, byte p2, byte n[])
{
	setSpeed(spd);
	setStamina(stmna);
	setWins(w);
	setRaces(r);
	setPeak1(p1);
	setPeak2(p2);

	for (int i = 0; i < 32; i++)
		name[i] = n[i];
}//end constructor Horse::Horse(byte, byte, byte, byte, byte, byte, byte[])

//--------------------------------------------------------------------------------------------
// Initialize a horse by accessing the game save and locating it through an offset
Horse::Horse(unsigned short int address, fstream& saveFileData)
{
	//Go to offset where speed is stored and retrieve it
	saveFileData.seekg(address + 0x1A);
	saveFileData.get(speed);

	//Go to offset where stamina is stored and retrieve it
	saveFileData.seekg(address + 0x1C);
	saveFileData.get(stamina);

	//Go to offset where wins are stored and retrieve it
	saveFileData.seekg(address + 0x2C);
	saveFileData.get(wins);

	//Go to offset where races are stored and retrieve it
	saveFileData.seekg(address + 0x2D);
	saveFileData.get(races);

	//Go to offset where 1st peak time is stored and retrieve it
	saveFileData.seekg(address + 0x4A);
	saveFileData.get(peak1);

	//Go to offset where 2nd peak time is stored and retrieve it
	saveFileData.seekg(address + 0x4B);
	saveFileData.get(peak2);

	//Go to offsets where name bytes are stored and retrieve it
	for (int i = 0; i < 32; i++)
	{
		saveFileData.seekg(address + 0x56 + i);
		saveFileData.get(name[i]);
	}//end loop for (int i = 0; i < 32; i++)

}//end function Horse::Horse(unsigned short int address, fstream& saveFileData)

//////////////////////////////////////////////////////////////////////////////////////////////
//									FUNCTION DEFINITIONS									//
//////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------
// Prints the name of the horse
void Horse::printName()
{
	//If name is not initialize, leave function
	if (name[0] == 0)
	{
		cout << "N/A";
		return;
	}//end conditional if (name[0] == 0)

	for (int i = 0; i < 32; i += 2)
	{//TODO: This only works for ASCII characters
	 //Bytes may have leftover junk, so we will stop once we hit an empty byte
		if (name[i] == 0)
			break;
		cout << name[i];
	}//end loop for (int i = 0; i < 32; i += 2)

}//end function void Horse::printName()

//--------------------------------------------------------------------------------------------
// Print data about this horse
void Horse::printData()
{
	cout << "     ";
	//If name is uninitialize, do not display its information
	if (name[0] == 0)
	{
		cout << "Horse does not exist.\n";
		return;
	}//end conditional 	if (name[0] == 0)

	printName();
	cout << endl;

	/*
	if (0 == 0) cout << "| Male ";
	else cout << "| Female ";

	cout << "| Temperament: ";
	switch (1)
	{
	case 0:
		cout << "Best ";
		break;
	case 1:
		cout << "Good ";
		break;
	case 2:
		cout << "Bad ";
		break;
	default:
		cout << "Worst ";
	}

	cout << "| " << "getCharacteristic(byte) " << " | " << "getSkill(byte)" << " | " << "getSkill(byte)" << " |\n";
	*/

	cout << "     | Speed " << ((unsigned char)speed & 0xFF) <<
	" | Stamina " << ((unsigned char)stamina & 0xFF) <<
	" | Wins: " << ((unsigned char)wins & 0xFF) << "/" << ((unsigned char)races & 0xFF) <<
	" | Peak " << ((unsigned char)peak1 & 0xFF) << "-" << ((unsigned char)peak2 & 0xFF) << " |\n";
}//void Horse::printData()

//--------------------------------------------------------------------------------------------
// Writes the horse's data to the save file by locating the byte offset
void Horse::writeData(unsigned short int address, fstream& saveFileData)
{
	//Find offset for speed and write over it
	saveFileData.seekp(address + 0x1A);
	saveFileData.write(&speed, 1);

	//Find offset for stamina and write over it
	saveFileData.seekp(address + 0x1C);
	saveFileData.write(&stamina, 1);

	//Find offset for wins and write over it
	saveFileData.seekp(address + 0x2C);
	saveFileData.write(&wins, 1);

	//Find offset for races and write over it
	saveFileData.seekp(address + 0x2D);
	saveFileData.write(&races, 1);

	//Find offset for 1st peak time and write over it
	saveFileData.seekp(address + 0x4A);
	saveFileData.write(&peak1, 1);

	//Find offset for 2nd peak time and write over it
	saveFileData.seekp(address + 0x4B);
	saveFileData.write(&peak2, 1);

	//Find offsets for name and write over it
	for (int i = 0; i < 32; i++)
	{
		saveFileData.seekp(address + 0x56 + i);
		saveFileData.write(&name[i], 1);
	}//end loop for (int i = 0; i < 32; i++)

}//end function void Horse::writeData(unsigned short int address, fstream& saveFileData)

//--------------------------------------------------------------------------------------------
// Raise speed to 255, stamina to 255, and wins equal to races for this horse
void Horse::maxStats()
{
	speed = 0xFF;	//255
	stamina = 0xFF;	//255
	wins = races;
}//end function void Horse::maxStats()

//////////////////////////////////////////////////////////////////////////////////////////////
//										MUTATOR FUNCTIONS									//
//////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------
// Mutator function to set horse's speed
void Horse::setSpeed(byte spd)
{
	if (((unsigned int)spd & 0xFF) < 0 || ((unsigned int)spd & 0xFF) > 255)
	{
		cout << "Data must be within [0,255]\n";
		cout << "Setting speed to 50\n";
		speed = 50;
		return;
	}//end conditional if
	speed = spd;
}//end mutator function void Horse::setSpeed(byte spd)

 //--------------------------------------------------------------------------------------------
 // Mutator function to set horse's stamina
void Horse::setStamina(byte stmna)
{
	if (((unsigned int)stmna & 0xFF) < 0 || ((unsigned int)stmna & 0xFF) > 255)
	{
		cout << "Data must be within [0,255]\n";
		cout << "Setting stamina to 50\n";
		stamina = 50;
		return;
	}//end conditional if

	stamina = stmna;
}//end mutator function void Horse::setStamina(byte stmna)

 //--------------------------------------------------------------------------------------------
 // Mutator function to set amount of races won
void Horse::setWins(byte w)
{
	if (((unsigned int)w & 0xFF) < 0 || ((unsigned int)w & 0xFF) > 255 || ((unsigned int)w & 0xFF) > races)
	{
		cout << "Data must be within [0,255] and not greater than races\n";
		cout << "Setting wins to 0\n";
		wins = 0;
		return;
	}//end conditional if
	wins = w;
}//end mutator function void Horse::setWins(byte w)

 //--------------------------------------------------------------------------------------------
 // Mutator function to set amount of races participated
void Horse::setRaces(byte r)
{
	if (((unsigned int)r & 0xFF) < 0 || ((unsigned int)r & 0xFF) > 255 || ((unsigned int)r & 0xFF) < wins)
	{
		cout << "Data must be within [0,255] and not lesser than wins\n";
		cout << "Setting races to " << ((int)wins & 0xFF) << endl;
		races = wins;
		return;
	}//end conditional if
	races = r;
}//end mutator function void Horse::setRaces(byte r)

//--------------------------------------------------------------------------------------------
// Mutator function to set first peak time
void Horse::setPeak1(byte p1)
{
	if (p1 < 2 || p1 > 6 || p1 > peak2)
	{
		cout << "1st peak time must be within [2,6] and not greater than 2nd peak time\n";
		cout << "Setting first peak time to 2\n";
		peak1 = 2;
		return;
	}//end conditional if
	peak1 = p1;
}//end mutator function void Horse::setPeak1(byte p1)

//--------------------------------------------------------------------------------------------
// Mutator function to set second peak time
void Horse::setPeak2(byte p2)
{
	if (p2 < 2 || p2 > 6 || p2 < peak1)
	{
		cout << "2nd peak time must be within [2,6] and not lesser than 1st peak time\n";
		cout << "Setting second peak time to 6\n";
		peak2 = 6;
		return;
	}//end conditional if
	peak2 = p2;
}//end mutator function void Horse::setPeak2(byte p2)

//////////////////////////////////////////////////////////////////////////////////////////////
//										ACCESSOR FUNCTIONS									//
//////////////////////////////////////////////////////////////////////////////////////////////

byte Horse::getSpeed() { return speed; }
byte Horse::getStamina() { return stamina; }
byte Horse::getWins() { return wins; }
byte Horse::getRaces() { return races; }
byte Horse::getPeak1() { return peak1; }
byte Horse::getPeak2() { return peak2; }
