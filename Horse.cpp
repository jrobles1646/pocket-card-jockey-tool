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
Horse::Horse(byte spd, byte stmna, byte w, byte r, byte p1,
			 byte p2, byte app, byte chrctr, byte fert, byte stl, byte n[])
{
	setSpeed(spd);
	setStamina(stmna);
	setWins(w);
	setRaces(r);
	setPeak1(p1);
	setPeak2(p2);
	setAppearance(app);
	setCharacteristic(chrctr);
	setFertility(fert);
	setStyle(stl);

	for (int i = 0; i < 32; i++)
		name[i] = n[i];
}//end constructor Horse::Horse(byte, byte, byte, byte, byte, byte, byte[])

//--------------------------------------------------------------------------------------------
// Initialize a horse by accessing the game save and locating it through an offset
Horse::Horse(unsigned short int address, fstream& saveFileData)
{
	//Go to offset where appearance is stored and retrieve it
	saveFileData.seekg(address + 0x18);
	saveFileData.get(appearance);

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

	//Go to offset where fertility is stored and retrieve it
	saveFileData.seekg(address + 0x2E);
	saveFileData.get(fertility);

	//Go to offset where characteristic is stored and retrieve it
	saveFileData.seekg(address + 0x2F);
	saveFileData.get(characteristic);

	//Go to offset where racing style is stored and retrieve it
	saveFileData.seekg(address + 0x3A);
	saveFileData.get(style);

	//Go to offset where temperament is stored and retrieve it
	saveFileData.seekg(address + 0x3B);
	saveFileData.get(temperament);

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
string Horse::nameToString()
{
	//If name is not initialize, leave function
	if (name[0] == 0)
		return "N/A";

	string playerName;

	for (int i = 0; i < 32; i += 2)
	{//TODO: This only works for ASCII characters
	 //Bytes may have leftover junk, so we will stop once we hit an empty byte
		if (name[i] == 0)
			break;
		playerName.push_back(name[i]);
	}//end loop for (int i = 0; i < 32; i += 2)
	return playerName;
}//end function void Horse::nameToString()

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

	cout << nameToString() << endl;

	
	cout << "     | " << appearanceToString()
		<< " | " << characteristicToString()
		<< " | " << styleToString() << " |\n";


	cout << "     | Temperament: " << temperamentToString()
		 << " | Fertility left: " << ((unsigned char)fertility & 0xFF)
		 << " |\n";

	cout << setfill(' ') << "     | Speed " << left << setw(5) << ((unsigned char)speed & 0xFF)
		 << " | Stamina " << setw(5) << ((unsigned char)stamina & 0xFF)
		 << " | Wins: " << setw(3) << ((unsigned char)wins & 0xFF)
		 << "/" << ((unsigned char)races & 0xFF)
		 << " | Peak " << ((unsigned char)peak1 & 0xFF)
		 << "-" << ((unsigned char)peak2 & 0xFF) << " |\n";
}//void Horse::printData()

//--------------------------------------------------------------------------------------------
// Writes the horse's data to the save file by locating the byte offset
void Horse::writeData(unsigned short int address, fstream& saveFileData)
{
	//Find offset for appearance and write over it
	saveFileData.seekp(address + 0x18);
	saveFileData.write(&appearance,1);

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

	//Find offset where fertility is stored and write over it
	saveFileData.seekp(address + 0x2E);
	saveFileData.write(&fertility, 1);

	//Find offset where characteristic is stored and write over it
	saveFileData.seekp(address + 0x2F);
	saveFileData.write(&characteristic, 1);

	//Find offset where racing style is stored and write over it
	saveFileData.seekp(address + 0x3A);
	saveFileData.write(&style, 1);

	//Find offset where temperament is stored and write over it
	saveFileData.seekp(address + 0x3B);
	saveFileData.write(&temperament, 1);

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
// Raise speed to 255, stamina to 255, wins equal to races, can make 255 more babies,
// and raise temperament to happy for this horse
void Horse::maxStats()
{
	speed = (byte)0xFF;	//255
	stamina = (byte)0xFF;	//255
	wins = races;
	fertility = (byte)0xFF;	//255
	temperament = (byte)3;

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
	if (((unsigned int)w & 0xFF) < (unsigned int)0
		|| ((unsigned int)w & 0xFF) > (unsigned int)255
		|| ((unsigned int)w & 0xFF) > races)
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
	if (((unsigned int)r & 0xFF) < (unsigned int)0
		|| ((unsigned int)r & 0xFF) > (unsigned int)255
		|| ((unsigned int)r & 0xFF) < wins)
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

//--------------------------------------------------------------------------------------------
// Mutator function to set 
void Horse::setAppearance(byte app)
{
	if (((unsigned int)app & 0xFF) < (unsigned int)0
		|| ((unsigned int)app & 0xFF) > (unsigned int)255)
	{
		cout << "Data must be within [0,255]\n";
		cout << "Setting appearance to " << ((int)(app % 255) & 0xFF) << endl;
		appearance = (int)(app % 255) & 0xFF;
		return;
	}//end conditional if
	appearance = app;
}//end mutator function 

//--------------------------------------------------------------------------------------------
// Mutator function to set 
void Horse::setCharacteristic(byte chrctr)
{
	if (chrctr < 0 || chrctr > 0x13)
	{
		cout << "Data must be within [0,19]\n";
		cout << "Setting characteristic to 0 (none)\n";
		characteristic = 0;
		return;
	}//end conditional if (chrctr < 0 || chrctr > 0x13)
	characteristic = chrctr;
}//end mutator function 

//--------------------------------------------------------------------------------------------
// Mutator function to set 
void Horse::setFertility(byte fert)
{
	if (((unsigned int)fert & 0xFF) < 0 || ((unsigned int)fert & 0xFF) > 255)
	{
		cout << "Data must be within [0,255]\n";
		cout << "Setting fertility to 3 (fertile)\n";
		fertility = 3;
		return;
	}//end conditional if
	fertility = fert;
}//end mutator function 

//--------------------------------------------------------------------------------------------
// Mutator function to set 
void Horse::setTemperament(byte temper)
{
	if (temper < 0 || temper > 3)
	{
		cout << "Data must be within [0,3]\n";
		cout << "Setting temperament to 3 (happy)\n";
		temperament = temper;
		return;
	}//end conditional if (temper < 0 || temper > 3)
}//end mutator function 

//--------------------------------------------------------------------------------------------
// Mutator function to set 
void Horse::setStyle(byte stl)
{
	if (stl < 0 || stl > 3)
	{
		cout << "Data must be within [0,3]\n";
		cout << "Setting racing style to 0 (F)\n";
		style = 0;
		return;
	}//end conditional if (stl < 0 || stl > 3)
	style = stl;
}//end mutator function 


//////////////////////////////////////////////////////////////////////////////////////////////
//										ACCESSOR FUNCTIONS									//
//////////////////////////////////////////////////////////////////////////////////////////////

byte Horse::getSpeed() { return speed; }
byte Horse::getStamina() { return stamina; }
byte Horse::getWins() { return wins; }
byte Horse::getRaces() { return races; }
byte Horse::getPeak1() { return peak1; }
byte Horse::getPeak2() { return peak2; }
byte Horse::getAppearance() { return appearance; }
byte Horse::getCharacteristic() { return characteristic; }
byte Horse::getFertility() { return fertility; }
byte Horse::getTemperament() { return temperament; }
byte Horse::getStyle() { return style; }

//--------------------------------------------------------------------------------------------
// 
string Horse::appearanceToString()
{
	if (appearance == 0)
		return "Deleted horse (0)";

	if (appearance == 1)
		return "Sunny Fire (1)";

	if (appearance == 2)
		return "Dark Fire (2)";

	if (appearance == 3)
		return "Pompadour (3)";

	if (appearance == 4)
		return "Robot (4)";

	if (appearance == 5)
		return "Dapper (5)";

	if (appearance == 6)
		return "Blue Bow (6)";

	if (appearance == 7)
		return "Kunoichi (7)";

	if (appearance == 8)
		return "Cat Luchador (8)";

	if (appearance == 9)
		return "Witch (9)";

	if (appearance == 0xA)
		return "Dragon (10)";

	if (appearance == 0xB)
		return "Dark Brown (M) (11)";

	if (appearance == 0xC)
		return "Dark Brown (F) (12)";

	if (appearance == 0xD)
		return "Dark Brown (M) (13)";

	if (appearance == 0xE)
		return "Dark Brown (F) (14)";

	if (appearance == 0xF)
		return "Dark Gray (M) (15)";

	if (appearance == 0x10)
		return "Dark Gray (F) (16)";

	if (appearance == 0x11)
		return "Navy Blue (M) (17)";

	if (appearance == 0x12)
		return "Navy Blue (F) (18)";

	if (appearance == 0x13)
		return "Dark Brown (M) (19)";

	if (appearance == 0x14)
		return "Dark Brown (F) (20)";

	if (appearance == 0x15)
		return "Olive Brown (21) (M)";

	if (appearance == 0x16)
		return "Olive Brown (22) (F)";

	if (appearance == 0x17)
		return "Tan (23) (M)";

	if (appearance == 0x18)
		return "Tan (24) (F)";

	if (appearance == 0x19)
		return "White (25) (M)";

	if (appearance == 0x1A)
		return "White (26) (F)";

	if (appearance % 2 == 0)
		return "Generic Female";

	return "Generic Male";

}//end member function string Horse::appearanceToString(byte data)

//--------------------------------------------------------------------------------------------
// 
string Horse::characteristicToString()
{
	switch (characteristic)
	{
	case 1:
	case 2:
	case 3:
		return "Unused Characteristic";
		 
	case 4:
		return "Front Charger (4)";
		 
	case 5:
		return "Back Charger (5)";
		 
	case 6:
		return "Front Unity (6)";
		 
	case 7:
		return "Back Unity (7)";
		 
	case 8:
		return "Middle Charger (8)";
		 
	case 9:
		return "Middle Unity (9)";
		 
	case 0xA:
		return "Lead Charger (10)";
		 
	case 0xB:
		return "Last Charger (11)";
		 
	case 0xC:
		return "Better Turns (12)";
		 
	case 0xD:
		return "L Charger (13)";
		 
	case 0xE:
		return "TL Charger (14)";
		 
	case 0xF:
		return "WL Charger (15)";
		 
	case 0x10:
		return "R Charger (16)";
		 
	case 0x11:
		return "TR Charger (17)";
		 
	case 0x12:
		return "WR Charger (18)";
		 
	case 0x13:
		return "International Star (19)";
		 
	default:
		return "No Characteristic";
		 
	}//end switch (characteristic)

}//end member function string Horse::appearanceToString(byte data)

//--------------------------------------------------------------------------------------------
// 
void Horse::displayAppearanceList()
{
	cout << left << setw(25) << "0) Deleted horse" << setw(25) << "1) Sunny Fire" << setw(25) << "2) Dark Fire" << endl;

	cout << left << setw(25) << "3) Pompadour" << setw(25) << "4) Robot" << setw(25) << "5) Dapper" << endl;

	cout << left << setw(25) << "6) Blue Bow" << setw(25) << "7) Kunoichi" << setw(25) << "8) Cat Luchador" << endl;

	cout << left << setw(25) << "9) Witch" << setw(25) << "10) Dragon" << setw(25) << "11) Dark Brown (M)" << endl;

	cout << left << setw(25) << "12) Dark Brown (F)" << setw(25) << "13) Dark Brown (M)" << setw(25) << "14) Dark Brown (F)" << endl;

	cout << left << setw(25) << "15) Dark Gray (M)" << setw(25) << "16) Dark Gray (F)" << setw(25) << "17) Navy Blue (M)" << endl;

	cout << left << setw(25) << "18) Navy Blue (F)" << setw(25) << "19) Dark Brown (M)" << setw(25) << "20) Dark Brown (F)" << endl;

	cout << left << setw(25) << "21) Olive Brown (M)" << setw(25) << "22) Olive Brown (F)" << setw(25) << "23) Tan (M)" << endl;

	cout << left << setw(25) << "24) Tan (F)" << setw(25) << "25) White (M)" << setw(25) << "26) White (F)" << endl;

	cout << left << setw(25) << "26+ Even) Generic (F)" << setw(25) << "27+ Odd) Generic (M)" << endl;
}//end member function string Horse::appearanceToString(byte data)

//--------------------------------------------------------------------------------------------
// 
void Horse::displayCharacterList()
{
	cout << left << setw(20) << "0) None" << "1) Unused (none)\n";
	cout << left << setw(20) << "2) Unused (none)" << "3) Unused (none)\n";
	cout << left << setw(20) << "4) Front Charger" << "5) Back Charger\n";
	cout << left << setw(20) << "6) Front Unity" << "7) Back Unity \n";
	cout << left << setw(20) << "8) Middle Charger" << "9) Middle Unity\n";
	cout << left << setw(20) << "10) Lead Charger" << "11) Last Charger\n";
	cout << left << setw(20) << "12) Better Turns" << "13) L Charger\n";
	cout << left << setw(20) << "14) TL Charger" << "15) WL Charger\n";
	cout << left << setw(20) << "18) WR Charger" << "19) International Star\n";
}//end member function string Horse::appearanceToString(byte data)

void Horse::displayStyleList()
{
	cout << left << setw(20) << "0) Front-runner (F)" << "1) Stalker (S)\n";
	cout << left << setw(20) << "2) Mid-pack (M)" << "3) Closer (C)\n";
}

void Horse::displayTemperList()
{
	cout << left << setw(20) << "0) Upset" << "1) Uneasy\n";
	cout << left << setw(20) << "2) Content" << "3) Happy\n";
}

//--------------------------------------------------------------------------------------------
// 
string Horse::temperamentToString()
{
	switch (temperament)
	{
	case 0:
		return "Upset";
	case 1:
		return "Uneasy";
	case 2:
		return "Content";
	default:
		return "Happy";
	}//end switch (temperament)
}//end member function string Horse::temperamentToString()

//--------------------------------------------------------------------------------------------
// 
string Horse::styleToString()
{
	switch (style)
	{
	case 0:
		return "Front-runner (F)";
	case 1:
		return "Stalker (S)";
	case 2:
		return "Mid-pack (M)";
	default:
		return "Closer (C)";
	}//end 	switch (style)
}//end member function string Horse::styleToString()