#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

// My header files
#include "Navigation.h"
#include "Game.h"
#include "Graphics.h"
#include "GlobalSetup.h"
#include "DevelopmentTools.h"
#include "Classes.h"
#include "Exceptions.h"


// Not my work, a function I found to hide the console cursor:
#include "Utilities.h"


using namespace std;

int main()
{
	// EnableFullScreen();

	SetConsoleWindowSize(PIXEL_WIDTH, PIXEL_HEIGHT);
	ToggleConsoleCursor(false);

	//countHorChPixels();
	//system("pause");
	//countVerChPixels();
	//system("pause");


	// ***************************************************************************

	int selection = -1;
	int counter = 0;
	bool exitGame = false;
	string temporaryStringDump = "";
	arrayLoadException recordLoadException;


	// FILE INPUT
	// ***************************************************************************
	int numberOfRecords = 8;
	int numberOfAttributesPerRecord = 4;
	ifstream readLog; // create logs object in the ifstream class.
	CPlayer* playerRecords; // allocate dynamic array of CPlayer objects.



	// open file read stream
	readLog.open(LOG_FILE_NAME);

	// FILE EXCEPTION:
	// -----------------------------------------------------------------------------

	// If the program fails to open the file, throw an error and close the program.
	// Same implementation as in my exam.
	if (readLog.fail()) {
		system("cls");
		cout << "\n**************************************************************\n\n";
		// display error in red
		c(4);
		cout << "   ERROR: ";
		// Reset the output back to white:
		c(15);
		cout << "Something went wrong when attempting to read the file." << endl;
		cout << "\n**************************************************************\n\n";

		// exit the program
		exit(NULL);
	}
	readLog.close();





	// LOAD DATA INTO ARRAY:
	// -----------------------------------------------------------------------------

	// handle possible exception

	try {
		// Initialize the previously dynamically declared CPlayer objects array:
		playerRecords = new CPlayer[numberOfRecords];
	}
	catch (bad_alloc& err) {

		cout << "\n**************************************************************\n\n";
		// display error in red
		c(4);
		cout << "   ERROR: ";
		// Reset the output back to white:
		c(15);
		//cout << err.what() << endl;
		//cout << "Memory allocation went wrong." << endl;
		cout << "\n**************************************************************\n\n";

		// exit the program
		exit(NULL);
	}




	readLog.open(LOG_FILE_NAME);

	try {
		// loop until the end of file (or until an error is thrown)
		while (readLog.good()) {
			//  Store items in array
			//  Iterate through every word in each line
			for (int positionInLine = 1; positionInLine <= numberOfAttributesPerRecord; positionInLine++) {
				// If it's any attribute but the last in line, use the specified delimiter.
				if (positionInLine < numberOfAttributesPerRecord) {
					getline(readLog, temporaryStringDump, LOG_SEPARATOR);
				}
				// If it's the last attribute in the line, use line break as a delimiter (delete third argument to get \n default):
				else if (positionInLine == numberOfAttributesPerRecord) {
					getline(readLog, temporaryStringDump);
				}

				// Assign each attribute to the corresponding class method depending on their position in line:
				switch (positionInLine)
				{
				case 1:
					playerRecords[counter].setName(temporaryStringDump);

					break;
				case 2:
					// because the input is not a string, we must convert it before passing it as an argument (string to int):
					playerRecords[counter].setPlayedNation(stoi(temporaryStringDump));

					break;

				case 3:
					// because the input is not a string, we must convert it before passing it as an argument (string to int):
					playerRecords[counter].setPlayedWealthPerTurn(stoi(temporaryStringDump));
					break;

				case 4:
					// because the input is not a string, we must convert it before passing it as an argument (string to boolean):
					if (temporaryStringDump == "true") {
						playerRecords[counter].setGameOutcome(true);
					}
					else if (temporaryStringDump == "false") {
						playerRecords[counter].setGameOutcome(false);
					}

					// increase the counter to start storing the next object:
					counter++;
					break;

				default:
					// will only trigger if the loop has not been properly implemented. 
					// It is unlikely, but if debugging was necessary, add exception handling.
					throw recordLoadException;
				}
				// end switch (array data insertion)					
			} // end for					
		} // end while (iterate file)
	}
	catch (exception& err) {

		cout << "\n****************************************\n\n";
		c(4);
		cout << "   ERROR: ";
		c(15);
		cout << err.what() << endl;
		cout << "\n****************************************\n\n";
	}




	// close file read stream
	readLog.close();


	// MAIN MENU
	// ***************************************************************************

	// Welcome screen will be displayed until intro is pressed.
	PrintWelcomeScreen();


	enum menuOptions {
		CharacterSelection,
		TipsAndRules,
		Scoreboard,
		ExitGame
	};

	do {
		selection = GoToMainMenu();

		switch (selection)
		{
		case CharacterSelection:
			// The program will only continue past this point if the Start Game option is selected in the main menu.
			selection = GoToCharacterSelection();

			enum captains {
				DutchCaptain,
				EnglishCaptain,
				FrenchCaptain,
				SpanishCaptain,
			};

			switch (selection)
			{
			case DutchCaptain:
				StartGame(0);
				break;
			case EnglishCaptain:
				StartGame(1);
				break;
			case FrenchCaptain:
				StartGame(2);
				break;
			case SpanishCaptain:
				StartGame(3);
				break;
			case -10:
				break;
			default:
				// I don't see any situation in which the default case would be triggered, but just in case:
				system("cls");
				cout << "Something went wrong." << endl;
				exit(0);
				break;
			}
			break;

		case TipsAndRules:
			GoToTipsAndRules();
			break;

		case Scoreboard:
			GoToViewScoreboard(numberOfRecords, playerRecords);
			break;

			// Exit game handled instead in the GoToMainMenu() function
		case ExitGame:
			exitGame = true;
			break;
			/*	system("cls");
			cout << "Exiting game..." << endl;
			Sleep(2000);
			exit(0);*/
		default:
			break;
		}

	} while (!exitGame);

		system("cls");
		cout << "Exiting game..." << endl;
		Sleep(2000);
		exit(0);
}

