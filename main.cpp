//////////////////////////////////////////////////////////////////////////////////////////////
//								POCKET CARD JOCKEY SAVE EDITOR								//
//////////////////////////////////////////////////////////////////////////////////////////////
//	Type of Program:				Save editing tool										//
//	Author:							Jeremy Robles											//
//	Date Started:					August 8, 2018											//
//	Last modified:					August 11, 2018											//
//	File Name:						main.cpp												//
//																							//
//////////////////////////////////////////////////////////////////////////////////////////////
//	This program allows user to edit their horse's stats and cash. Currently, the program	//
//	doesn't edit the player data, horse's name, skills, and, active shop items.				//
//	There are no plans to implement a puzzle pieces or trophies editor.						//
//																							//
//	To use this program, you must have a 3DS homebrew tool that allows you to extract and	//
//	inject save data for the Pocket Card Jockey software. Once you extract the data, it		//
//	must be	named "gamedata" and in the same directory as this program's executable.		//
//																							//
//	Program author: Jeremy Robles 2018														//
//	I do not own the rights to Pocket Card Jockey.											//
//////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////
//								INCLUDED HEADERS/LIBRARIES									//
//////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include "SaveData.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
//									FUNCTION PROTOTYPES										//
//////////////////////////////////////////////////////////////////////////////////////////////
void displayMenu();
int editHorseOption(SaveData* pocketCardJockey);
bool maxAllStatsOption();
bool maxCashOption();
bool saveDataOption();
int quitOption();
void about();

void displayCharacterList()
{

}//end member function string Horse::appearanceToString(byte data)

//////////////////////////////////////////////////////////////////////////////////////////////
//										MAIN FUNCTION										//
//////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	fstream savedata("gamedata", ios::in | ios::binary | ios::ate | ios::out);

	short int userInput = 0;	//User input from IO stream is stored here

	bool menuFlag = true;		//Flag for menu

	//Terminate program if file cannot be found
	if (savedata.is_open() == false)
	{
		cout << "Unable to locate Pocket Card Jockey save file.\n";
		cout << "Save file must be in the same directory as this executable and must be named 'gamedata'\n";
		cout << "Exiting program...\n";
		return(1);
	}//end conditional statement if (savedata.is_open() == false)

	cout << "Welcome to the Pocket Card Jockey save editor.\n";

	SaveData pocketCardJockey(savedata);
	savedata.seekp(0, ios::beg);

	displayCharacterList();

	while (menuFlag)
	{
		displayMenu();
		cout << "=>";
		cin >> userInput;
		cout << endl;

		switch (userInput)
		{
		//User wishes to see about
		case 0:
			about();
			break;

		//User wishes to view all player data
		case 1:
			pocketCardJockey.printAllData();
			break;

		//User wishes to edit a single horse
		case 2:
			userInput = editHorseOption(&pocketCardJockey);
			if (userInput)
				pocketCardJockey.writeIndividualHorse(userInput - 1);
			userInput = 0;
			break;

		//User wishes to max all horses
		case 3:
			if (maxAllStatsOption())
				pocketCardJockey.maxAllHorse();
			break;

		//User wishes to max out all cash rewards
		case 4:
			if (maxCashOption())
				pocketCardJockey.maxAllCash();
			break;

		//User wishes to edit their name/gender
		case 5:
			cout << "Unfortunately, this feature has not been implemented.\n";
			cout << "Sorry! :(\n";
			break;

		//User wishes to edit their active racing items
		case 6:
			cout << "Unfortunately, this feature has not been implemented.\n";
			cout << "Sorry! :(\n";
			break;

		//User wishes to create a new horse
		case 7:
			cout << "Unfortunately, this feature has not been implemented.\n";
			cout << "Sorry! :(\n";
			break;

		//User wishes to overwrite save data
		case 8:
			if (saveDataOption())
			{
				pocketCardJockey.overwriteData(savedata);
				cout << "\n>>Data saved.\n";
			}
			break;

		//User wishes to quit program
		case 9:
			userInput = quitOption();

			if (userInput == 1)
			{
				cout << "Data will not be saved.\n";
				menuFlag = false;
			}//end conditional if (userInput == 1)

			if (userInput == 2)
			{
				pocketCardJockey.overwriteData(savedata);
				cout << "\n>>Data saved.\n";
				menuFlag = false;
			}//end conditional if (userInput == 2)

			break;

		default:
			cout << "Invalid option. Please type in an option from 0-8 as stated in the menu:\n";
			break;
		}//end switch statement switch (userInput)

		cout << "\n*Reminder: If you made any changes, remember to save them!\n";
		cout << endl;

	}//end loop while (menuFlag)

	cout << "Exiting Pocket Card Jockey Save Editor...\n";

	savedata.close();
	return 0;
}//end function int main()

//////////////////////////////////////////////////////////////////////////////////////////////
//									FUNCTION DEFINITIONS									//
//////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------------------
// Displays the main menu for program
void displayMenu()
{
	cout << "Select an option:\n";
	cout << "=================== MENU =================\n";
	cout << "1) View your horses\n";
	cout << "2) Edit individual stats\n";
	cout << "3) Maximize all stats\n";
	cout << "4) Maximize cash prizes\n";
	cout << "5) Edit player name/gender\n";
	cout << "6) Edit active items\n";
	cout << "7) Create new horse\n";
	cout << "8) Save data\n";
	cout << "9) Quit program\n";
	cout << "0) About/info\n";
	cout << "===========================================\n";
}//end function void displayMenu()

//--------------------------------------------------------------------------------------------
// Sub-menu to edit an individual horse. It will list options of horses to edit. Returns
// true if horse was editted, or false if user changed their mind
int editHorseOption(SaveData* pocketCardJockey)
{
	int userInput = 0;
	cout << "=========> Edit individual stats <=========\n";
	cout << "Select a horse from the following list (1-22):\n";
	cout << "  0) Nevermind (exit)...\n";
	pocketCardJockey->printShortList();
	cout << "=>";
	cin >> userInput;
	cout << endl;

	if (userInput < 0 || userInput > HORSE_MAX)
	{
		cout << "Invalid option. Let's try that again:\n";
		return editHorseOption(pocketCardJockey);
	}//end conditional if (userInput < 0 || userInput > 22)

	return userInput;
}//end function int editHorseOption(SaveData* pocketCardJockey)

//--------------------------------------------------------------------------------------------
// Submenu to max out the stats of all horses. Returns true if user does want to max out
// all stats or returns false if they changed their mind.
bool maxAllStatsOption()
{
	char userInput = 'j';
	cout << "===========> Maximize all stats <==========\n";
	cout << "This will affect ALL of your horses!\n";
	cout << "This will raise speed and stamina to 255, and raise the number\n";
	cout << "of wins to match the number of races your horse participated in.\n";
	cout << "The horse's temperament will be happy and can make 255 more babies.\n";
	cout << "Are you sure you want to do this? (Y/N)\n";
	cout << "=>";
	cin >> userInput;

	switch (toupper(userInput))
	{
	case 'Y':
		cout << "\n>>Maximized all horses.\n\n";
		return true;
	case 'N':
		return false;
	default:
		cout << "Invalid option. Let's try that again.\n";
		return maxAllStatsOption();
	}//end statement switch (toupper(userInput))

}//end function bool maxAllStatsOption()

//--------------------------------------------------------------------------------------------
// Submenu to max out all cash prizes. Returns true if user does want to max their cash
// or returns false if they changed their mind.
bool maxCashOption()
{
	char userInput = 'j';
	cout << "===========> Maximize cash prizes <==========\n";
	cout << "This will give you money for all current racing horses\n";
	cout << "Are you sure you want to do this? (Y/N)\n";
	cout << "=>";
	cin >> userInput;

	switch (toupper(userInput))
	{
	case 'Y':
		cout << "\n>>Maximized all cash prizes.\n\n";
		return true;
	case 'N':
		return false;
	default:
		cout << "Invalid option. Let's try that again.\n";
		return maxCashOption();
	}//end statement switch (toupper(userInput))
}//end function bool maxCashOption()

//--------------------------------------------------------------------------------------------
// Submenu to save data. This will reaffirm whether the user wants to overwrite save data
// Returns true if user wishes to save, returns false if user changed their mind
bool saveDataOption()
{
	char userInput = 'j';

	cout << "=======> Save data <=======\n";
	cout << "*I am not responsible for any damages caused to your save data. BACKUP YOUR ORIGINAL SAVE BEFORE MODIFYING IT.\n";
	cout << "Are you sure you want to save? (Y/N)\n";
	cout << "=>";
	cin >> userInput;

	switch (toupper(userInput))
	{
	case 'Y':
		return true;
	case 'N':
		return false;
	default:
		cout << "Invalid option. Let's try that again.\n";
		return saveDataOption();
	}//end statement switch (toupper(userInput))
}//end function bool saveDataOption()

//--------------------------------------------------------------------------------------------
// Submenu for quitting program. Returns 1 if user wishes to quit, returns 2 if user wishes
// to stay, or returns 3 if user wishes to save and quit
int quitOption()
{
	char userInput = 'j';

	cout << "=======> Quit Program  <=======";
	cout << "*NOTE: This program does not automatically save. Enter 'S' to save and quit.\n";
	cout << "Are you sure you want to quit? (Y/N/S)\n";
	cout << "=>";
	cin >> userInput;

	switch (toupper(userInput))
	{
	case 'Y':
		return 1;
	case 'N':
		return 0;
	case 'S':
		return 2;
	default:
		cout << "Invalid option. Let's try that again.\n";
		return quitOption();
	}//end statement switch (toupper(userInput))
	
}//end function int quitOption()

//--------------------------------------------------------------------------------------------
// Displays information about this program
void about()
{
	cout << "/////////////////////////////////////////////////////////////////\n";
	cout << "//                             ABOUT                           //\n";
	cout << "/////////////////////////////////////////////////////////////////\n";
	cout << "// This program allows user to edit their horse's stats and    //\n";
	cout << "// and cash. Currently, the program doesn't edit the player    //\n";
	cout << "// data, horse's name, skills, and active shop items. There    //\n";
	cout << "// are no plans to implement a puzzle or trophies editor.      //\n";
	cout << "//                                                             //\n";
	cout << "// To use this program, you must have a 3DS homebrew  tool     //\n";
	cout << "// that allows you to extract/inject save data for the Pocket  //\n";
	cout << "// Card Jockey software. Once you extract the data, it must be //\n";
	cout << "// named \"gamedata\" and in the same directory as this          //\n";
	cout << "//  program's executable.                                      //\n";
	cout << "//                                                             //\n";
	cout << "// Program author: Jeremy Robles 2018                         //\n";
	cout << "// I do not own the rights to Pocket Card Jockey.              //\n";
	cout << "/////////////////////////////////////////////////////////////////\n";
	cout << endl;

}//end function void about()