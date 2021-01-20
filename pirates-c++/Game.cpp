#include "GlobalSetup.h"
#include "Game.h"
#include "Graphics.h"
#include "Utilities.h"
#include "Classes.h"
#include "Navigation.h"

#include <iostream>
#include <string>
#include <stdlib.h> // for rand() and cls
#include <Windows.h> // for sleep() and GetAsyncKeyState()
#include <iomanip> // to format tables
#include <algorithm> // to use max()



using namespace std;

// Global constants
//const int GOOD_TYPES = 6;
//const int MAX_GOOD_AMOUNT = 12;
//const string GOOD_NAMES[GOOD_TYPES] = { "Wood", "Exotic Fruits", "Sugar Cane", "Rum", "Metals", "Cannons" };
//const HANDLE OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
//const int PORT_HEADER_LINES = 4;
//const int PORT_MAIN_MENU_LINES = 5;
//const int MAX_SECONDARY_MENU_LINES = 13;
//const int MAX_PORT_MENU_LINES = PORT_HEADER_LINES + PORT_MAIN_MENU_LINES + MAX_SECONDARY_MENU_LINES;
//const int MAX_VERTICAL_CHARACTERS = 44;
//const int SELECTION_COLOR = 10;



// FUNCTIONS
// =====================================================================================================================

void PirateCheck(CShip& playerShip, int playerNation, int dangerousRoute, int safeRoute, int destination) {

	bool piratesEncountered = false;

	// Modifies the encounter roll. Static so that it persists between function calls
	// intended so that no pirates are encountered in the first turn.
	static int encounterModifier = -100;
	//encounterModifier = 100; //delete


	// Random dice roll (1-100) plus the encounter modifier:
	int encounterDiceRoll = (rand() % 100 + 1) + encounterModifier;

	// increase or decrease pirate chance according to gossip
	if (destination == dangerousRoute) {
		encounterDiceRoll = max(100, (rand() % 100 + 1) + 90);
	}
	else if (destination == safeRoute) {
		encounterDiceRoll = min(0, (rand() % 10 + 1) - 90);
	}

	// will be used if the players wins the battle to set the loot found.
	int randomLootAmmount;

	if (encounterDiceRoll > 50) {
		piratesEncountered = true;
	}


	// enable the  modifier after the first turn so that encounters are possible.
	if (encounterModifier == -100) {
		encounterModifier = 0;
	}
	// increase the modifier each function call (to a maximum of 100)
	else if (encounterModifier >= 0 && encounterModifier <= 80) {
		encounterModifier += 20;
	}


	// Move cursor right below the map to clear the port menu:
	MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - MAX_PORT_MENU_LINES);

	// piratesEncountered is a bool and therefore no default case is needed (only two possible values)
	switch (piratesEncountered)
	{
	case 0:
		cout << "\n              No pirates encountered.                                              \n\n";
		break;
	case 1:
		cout << "\n              PIRATES AHOY!!!                                                      \n\n";
		break;
	}
	cout << "================================================================================" << endl;

	switch (piratesEncountered)
	{
	case 0:
		PrintEmptyLines(1);
		cout << "Press any key to continue to destination.                                  \n";
		PrintEmptyLines(MAX_PORT_MENU_LINES - PORT_HEADER_LINES - 2);
		system("pause > nul");
		break;
	case 1:
		PrintEmptyLines(MAX_PORT_MENU_LINES - PORT_HEADER_LINES);

		Sleep(2000);
		break;
	}



	if (piratesEncountered) {

		//playerShip.setAllGoodsTo(10); // delete, only for testing.

		int selector = 0;
		int combatCounter = 0;
		bool tryngToFlee = false;
		bool inCombat = false;
		bool combatOver = false;
		string combatOptions[2] = { "Throw some cargo overboard and try to outrun them!", "All hands to battle stations! Prepare to fight!" };
		int numberOfCombatOptions = sizeof(combatOptions) / sizeof(combatOptions[0]);
		// create a temporaty empty array to later determine which goods to throw overboard if tryng to flee.
		int goodsToJettison[GOOD_TYPES] = { 0 };
		int chanceToGetAway = 0;

		// Create new pirate ship
		CShip pirateShip;
		// Set cannons to a random amount between 10 and 50.
		pirateShip.setCannons(rand() % (50 - 10) + 10);

		int pirateShipCannons = pirateShip.getCannons();
		int playerShipCannons;

		// Make an estimation of enemy ships cannons:
		int cannonsEstimation = pirateShip.getCannons();
		if (cannonsEstimation % 10 != 0) {
			cannonsEstimation -= cannonsEstimation % 10;
		}

		while (true) {

			// Move cursor to the end of the map to reprint only the menu (printing the map is very slow).
			MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - MAX_PORT_MENU_LINES);

			if (!tryngToFlee && !inCombat) {

				cout << "\n      They seem to have at least " << cannonsEstimation << " cannons for our " << playerShip.getCannons() << ". ";
				cout << "What shall we do, captain?                                              \n\n";
				cout << "================================================================================" << endl;

				// Display menu options and highlight currently selected option:
				for (int i = 0; i < numberOfCombatOptions; i++) {
					if (!tryngToFlee && !inCombat && selector == i) {
						SetConsoleTextAttribute(OUTPUT_HANDLE, SELECTION_COLOR);
					}
					cout << combatOptions[i] << "                                            " << endl;
					// Reset output format for unselected menu options:
					if (!tryngToFlee && !inCombat && selector == i) {
						SetConsoleTextAttribute(OUTPUT_HANDLE, 15);
					}
				}
			}


			// TRYING TO FLEE
			// ------------------------------------------------------------------------------------------------------
			// ------------------------------------------------------------------------------------------------------

			// Print ships cargo
			if (tryngToFlee) {

				cout << "\n            Which goods do you want thrown overboard, captain?                                              \n\n";
				cout << "================================================================================" << endl;

				// clear section to prevent leftovers from previous prints and then move the cursor back to the start of the section
				for (int i = 0; i < MAX_SECONDARY_MENU_LINES; i++) {
					cout << "                                                                                             \n";
				}
				MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - MAX_SECONDARY_MENU_LINES - PORT_MAIN_MENU_LINES);

				cout << endl;
				cout << setw(20) << left << "";
				cout << setw(20) << left << "In ship";
				cout << setw(20) << left << "Throw overboard";
				cout << endl;

				for (int i = 0; i < GOOD_TYPES; i++) {
					// highlight the currently selected good:
					if (selector == i) {
						SetConsoleTextAttribute(OUTPUT_HANDLE, SELECTION_COLOR);
					}
					cout << setw(20) << left << GOOD_NAMES[i];
					cout << setw(20) << left << playerShip.getGoodAmount(i);
					cout << setw(20) << left << goodsToJettison[i];
					cout << endl;

					// Reset output format for unselected menu options:
					if (selector == i) {
						SetConsoleTextAttribute(OUTPUT_HANDLE, 15);
					}
				}
				cout << "                                                                                        " << endl;
				cout << "                                                                                        " << endl;
				cout << "Chance to escape: ";
				// change color depending on the escape chance:
				if (chanceToGetAway < 40) { SetConsoleTextAttribute(OUTPUT_HANDLE, 4); }
				else if (chanceToGetAway >= 40 && chanceToGetAway < 80) { SetConsoleTextAttribute(OUTPUT_HANDLE, 6); }
				else if (chanceToGetAway >= 80) { SetConsoleTextAttribute(OUTPUT_HANDLE, 2); }
				cout << chanceToGetAway;
				cout << "%                                            " << endl;
				SetConsoleTextAttribute(OUTPUT_HANDLE, 15);
				cout << "                                                                                        " << endl;
				cout << "                                                                                        " << endl;
				cout << "-> to choose a unit of the selected good to be thrown overboard.                        " << endl;
				cout << "<- to change your mind and keep a unit of the selected good in the ship.                " << endl;
				cout << "ESC to return to choose again between fighting or fleeing.                              " << endl;
				if (tryngToFlee) {
					cout << "INTRO to throw selected goods overboard and try your luck to escape.                                                                                        " << endl;
				}
				else {
					PrintEmptyLines(1);
				}
				PrintEmptyLines(1);

			}

			// COMBAT
			// ------------------------------------------------------------------------------------------------------
			// ------------------------------------------------------------------------------------------------------

			// Print ships cargo
			if (inCombat) {

				playerShipCannons = playerShip.getCannons();

				//  Combat resolution
				// ----------------------------------------------------------


				if (inCombat) {

					do {

						MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - MAX_PORT_MENU_LINES);

						cout << "\n        HERE THEY COME!                                                                \n\n";
						cout << "====================================================================================================================" << endl;
						PrintEmptyLines(1);
						cout << setw(5) << left << "";
						cout << setw(25) << left << "Your hull points";
						cout << setw(25) << left << "Pirate's hull points";
						cout << setw(25) << left << "Broadside cannonades";
						cout << endl;
						cout << setw(5) << left << "";
						cout << setw(25) << left << playerShip.getHullPoints();
						cout << setw(25) << left << pirateShip.getHullPoints();
						cout << setw(25) << left << combatCounter;
						PrintEmptyLines(4);
						cout << setw(5) << "Awaiting your command! (press any key to fire)." << endl;
						PrintEmptyLines(MAX_SECONDARY_MENU_LINES - 8);

						system("pause > nul");

						// CALCULATE DAMAGE
						// deduct hullpoints according to opponent's number of cannonts (with some luck factor, up to 10 cannonballs might miss)
						playerShip.setHullPoints(playerShip.getHullPoints() - pirateShipCannons + (rand() % max(10, pirateShipCannons) + 1));
						pirateShip.setHullPoints(pirateShip.getHullPoints() - playerShipCannons + (rand() % max(10, playerShipCannons) + 1));

						// Don't allow player's hullpoints to go bellow 10:
						if (playerShip.getHullPoints() < 10) { playerShip.setHullPoints(10); };

						// increase number of cannondades:
						combatCounter++;

						// PRINT ROUND RESULTS
						MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - MAX_PORT_MENU_LINES);

						cout << "\n        FIRE!                                                                \n\n";
						cout << "====================================================================================================================" << endl;
						PrintEmptyLines(1);
						cout << setw(5) << left << "";
						cout << setw(25) << left << "Your hull points";
						cout << setw(25) << left << "Pirate's hull points";
						cout << setw(25) << left << "Broadside cannonades";
						cout << endl;
						cout << setw(5) << left << "";
						cout << setw(25) << left << playerShip.getHullPoints();
						cout << setw(25) << left << pirateShip.getHullPoints();
						cout << setw(25) << left << combatCounter;
						cout << endl;
						PrintEmptyLines(MAX_SECONDARY_MENU_LINES - 3);





						Sleep(2400);

					} while (playerShip.getHullPoints() != 10 && pirateShip.getHullPoints() > 0 && combatCounter != 5);


					// Combat results
					// ----------------------------------------------------------

					MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - MAX_PORT_MENU_LINES);

					if (pirateShip.getHullPoints() <= 0 || (!(pirateShip.getHullPoints() <= 0) && pirateShip.getHullPoints() < playerShip.getHullPoints())) {
						cout << "\n            THEY FLEE! HUZZA!                                            \n\n";
						cout << "================================================================================" << endl;
						PrintEmptyLines(1);
						cout << "You see some barrels among the floating debris.                                " << endl;
						PrintEmptyLines(1);
						cout << "  You get :" << endl;
						cout << endl;
						for (int i = 0; i < GOOD_TYPES; i++) {
							cout << "  " << setw(15) << left << GOOD_NAMES[i];
							randomLootAmmount = rand() % 4; //player might find between 0 and 3 units of each good.
							cout << "  " << setw(10) << left << randomLootAmmount << endl;
							playerShip.setGoodAmount(i, playerShip.getGoodAmount(i) + randomLootAmmount);
						}
					}
					else if (playerShip.getHullPoints() == 10 || (playerShip.getHullPoints() != 0 && pirateShip.getHullPoints() > playerShip.getHullPoints())) {
						cout << "\n            They are about to board us! Drop what you can and flee!                       \n\n";
						cout << "================================================================================" << endl;
						PrintEmptyLines(1);
						cout << "Your sailors throw overboard what they can get their hands on to make the ship faster and flee.                           " << endl;
						PrintEmptyLines(1);
						cout << "  You lose :" << endl;
						cout << endl;
						for (int i = 0; i < GOOD_TYPES; i++) {
							cout << "  " << setw(15) << left << GOOD_NAMES[i];
							randomLootAmmount = rand() % 6; //player might find between 0 and 5 units of each good.
							// don't let player cargo go negative:
							if (playerShip.getGoodAmount(i) - randomLootAmmount < 0) {
								playerShip.setGoodAmount(i, 0);
								randomLootAmmount = 0;
							}
							cout << "  " << setw(10) << left << randomLootAmmount << endl;
							playerShip.setGoodAmount(i, playerShip.getGoodAmount(i) - randomLootAmmount);

						}
					}

					PrintEmptyLines(2);
					cout << "Press any key to continue to destination.                                      " << endl;
					PrintEmptyLines(MAX_PORT_MENU_LINES - PORT_HEADER_LINES - 14);

					combatOver = true;
					//system("pause");
					system("pause > nul");

					// continue to destination:
					return;


				}


			}

			else if (!tryngToFlee && !inCombat) {
				// print empty lines until the end of the section
				PrintEmptyLines(MAX_PORT_MENU_LINES - PORT_HEADER_LINES - 2);


				/*	for (int i = 0; i < MAX_PORT_MENU_LINES - PORT_HEADER_LINES-2; i++) {
						cout << "                                                                                 \n";
					}*/

			}
			cout << "================================================================================";






			// ARROW MENU
			// ----------------------------------------------------------
			do {
				// Do nothing if intro key remains pressed. It prevents accidental action triggers when returning from other menus.
			} while (GetAsyncKeyState(VK_RETURN) != 0);

			while (true) {

				// GetAsyncKeyState() checks it the down arrow key has been pressed (value 0 indicates not pressed):
				if (GetAsyncKeyState(VK_DOWN) != 0) {

					// Once the down key is pressed, cycle to the next option:
					selector++;
					// Cycle back to the first option after the last option.
					if (!tryngToFlee && !inCombat && selector == numberOfCombatOptions) {
						selector = 0;
					}
					if (tryngToFlee && selector == GOOD_TYPES) {
						selector = 0;
					}

					// Break so that the menu gets refreshed to display the new selection:
					break;
				}

				// Do the reverse for the up arrow key:
				else if (GetAsyncKeyState(VK_UP) != 0) {
					selector--;
					// Cycle back to the first option after the last option.
					if (!tryngToFlee && !inCombat && selector == -1) {
						selector = numberOfCombatOptions - 1;
					}
					if (tryngToFlee && selector == -1) {
						selector = GOOD_TYPES - 1;
					}

					// Break so that the menu gets refreshed to display the new selection:
					break;
				}



				// Left and right arrow functionality only when tryng to flee (Select what to throw overboard):
				else if (tryngToFlee && GetAsyncKeyState(VK_RIGHT) != 0) {

					// Prevent players to throw more goods than required to achieve a 100% escape chance.
					if (chanceToGetAway <= 90) {
						// Add goods to the list of goods to throw overboard
						if (playerShip.getGoodAmount(selector) > 0) {

							playerShip.setGoodAmount(selector, playerShip.getGoodAmount(selector) - 1);
							goodsToJettison[selector]++;

							// increase chance to escape:
							chanceToGetAway += 10;
						}
					}

					break;
				}
				else if (tryngToFlee && GetAsyncKeyState(VK_LEFT) != 0) {

					// Remove goods from the list of goods to throw overboard
					if (goodsToJettison[selector] > 0) {

						playerShip.setGoodAmount(selector, playerShip.getGoodAmount(selector) + 1);
						goodsToJettison[selector]--;

						// decrease chance to escape:
						chanceToGetAway -= 10;
					}

					break;
				}


				// Behaviour for escape key:
				else if (GetAsyncKeyState(VK_ESCAPE) != 0) {
					if (!inCombat) {
						selector = 0;
						tryngToFlee = false;
					}
					break;
				}

				// Implement option selection with return key:
				else if (GetAsyncKeyState(VK_RETURN) != 0) {

					if (!tryngToFlee && !inCombat) {

						// An enumeration just for clarity in the switch statement below.
						enum portMenuOptions {
							Flee,
							Fight
						};

						switch (selector)
						{
						case Flee:
							tryngToFlee = true;
							selector = 0;

							break;

						case Fight:
							inCombat = true;
							selector = 0;
							break;

						default:
							break;
						}
					}
					else if (tryngToFlee) {
						// dice roll to determine if player gets away
						if (rand() % 100 + 1 >= chanceToGetAway) {

							// player does not escape and combat starts							
							tryngToFlee = false;
							inCombat = true;

							MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - MAX_PORT_MENU_LINES);
							cout << "\n              It's not enough, they are catching us! Prepare for combat!                             \n\n";
							cout << "================================================================================" << endl;

							PrintEmptyLines(MAX_PORT_MENU_LINES - PORT_HEADER_LINES);

							Sleep(2000);
						}
						else {
							// player escapes. 
							MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - MAX_PORT_MENU_LINES);
							cout << "\n              Shiver me timbers captain! We outrun them!!!                                                     \n\n";
							cout << "================================================================================" << endl;
							PrintEmptyLines(1);
							//CustomPause("Press any key to continue to destination.");
							cout << "Press any key to continue to destination.                                  \n";
							//system("pause");
							PrintEmptyLines(MAX_PORT_MENU_LINES - PORT_HEADER_LINES - 2);

							system("pause > nul");

							// Leave the pirate check function and procceed to next port.
							return;
						}
					}
					else if (inCombat && combatOver) {
						// if combat is over, proceed to next port
						return;
					}

					// break out of the return if
					break;
				}
			}

			// Workaround to lower the arroy input "sensitivity" (Slightly delay the program so that a single arrow key press is not registered multiple times).
			// It prevents the menu going down or up several times when pressing an arrow key if we only want it to move a single step.
			Sleep(150);
		}
	}

};



int GoToPortMenu(CPort* allPorts, int currentPlayerLocation, CShip& playerShip, int playerNation, int numberOfPorts, int& dangerousRoute, int& safeRoute) {
	int selector = 0;
	string menuOptions[4] = { "Buy and sell goods", "Repair ship", "Visit tavern", "Set sail" };
	int numberOfMenuOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
	//int selector = selector - numberOfMenuOptions - 1; //just for market transactions

	// Current menu flags
	bool inMainPortMenu = true;
	bool inMarketMenu = false;
	bool settingSail = false;
	bool repairingShip = false;
	bool inTavern = false;


	// Set Sail variables
	bool setSailSkipPortTrigger = false;
	int setSailIterator = 0;

	// Repair ship variables
	int woodFor10Hullpoints = 1;
	int repairShipFee = 25;
	int currentWoodUnitPrice = 0;
	bool playerHasEnoughFunds = true;
	int playerDoublonsToBeUsed = 0;
	int playerWoodToBeUsed = 0;
	int marketWoodToBeUsed = 0;
	int totalMarketWoodCost = 0;
	int tempWoodBill = 0;
	bool shipRepaired = false;
	bool LeftArrowRegistered = false;
	bool RightArrowRegistered = false;

	// For quit to main menu
	bool keepPlaying = false;

	// For Tavern gossip
	int diceRoll1 = 0;
	int diceRoll2 = 0;
	int drinkPrice = 25;




	// determine starting print position for secondary menu so that content is centered (used in set sail):
	int secondaryMenuPrintStart = floor((MAX_SECONDARY_MENU_LINES - 1) / 2) - floor(numberOfPorts / 2);

	system("cls");

	// Display upper half screen section (Map)
	PrintMap();
	/*PrintEmptyLines(24);
	PrintShip(playerNation);
	PrintEmptyLines(5);
	cout << "**************************************************************************************************\n";
	cout << "**************************************************************************************************\n";*/


	// Create scrolling menu controlled by arrow keys instead of single key inputs
	while (true) {

		// Print current port's name and flag.
		cout << endl;
		cout << allPorts[currentPlayerLocation].getName() << " "; PrintFlag(currentPlayerLocation);
		cout << "                                                  ";
		cout << endl;
		cout << endl;
		cout << "================================================================================" << endl;

		// Display menu options and highlight currently selected option:
		for (int i = 0; i < numberOfMenuOptions; i++) {

			// The empty space after the print are necessary to properly overwrite the line after the menu is refreshed.
			if (inMainPortMenu && i == selector) {
				cout << ">> " << menuOptions[i] << " <<                           \n";
			}
			else {
				cout << menuOptions[i] << "                           " << endl;
			}
		}
		cout << "================================================================================" << endl;


		// MARKET
		// ------------------------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------------------------

		// Print market info (unless setting sail or visiting the tavern)
		if (inMarketMenu || inMainPortMenu) {
			cout << "Your doublons: " << playerShip.getDoublonsAmount() << "                                          \n";
			cout << setw(25) << left << "";
			cout << setw(25) << left << "Price per unit";
			cout << setw(25) << left << "In port";
			cout << setw(25) << left << "In ship";
			cout << "                                                      ";
			cout << endl;
		}


		for (int i = 0; i < GOOD_TYPES; i++) {
			// If in the market menu highlight the currently selected good:
			if (inMarketMenu && selector == i) {
				c(SELECTION_COLOR);
			}
			// Print good name label
			cout << setw(25) << left << GOOD_NAMES[i];

			// Print price per unit of cargo. The prices follow an exponential supply curve
			// price turns red if the player cannot buy it.
			if (playerShip.getDoublonsAmount() < ceil(20 / max(1, allPorts[currentPlayerLocation].getGoodAmount(i)))) { c(4); };
			cout << setw(25) << left << ceil(20 / max(1, allPorts[currentPlayerLocation].getGoodAmount(i)));

			if (inMarketMenu && selector == i) {
				c(SELECTION_COLOR);
			}
			else {
				c(15);
			}

			// Number of items in port
			cout << setw(25) << left << allPorts[currentPlayerLocation].getGoodAmount(i);
			// Number of items in the player's ship
			cout << setw(25) << left << playerShip.getGoodAmount(i) << endl;

			// Reset output format for unselected menu options:
			if (inMarketMenu && selector == i) {
				c(15);
			}

		}

		// print market instructions only if in the market menu:
		if (inMarketMenu) {
			cout << endl;
			cout << "-> to purchase a unit of the selected good" << endl;
			cout << "<- to sell a unit of the selected good" << endl;
			cout << "ESC to return to port menu. " << endl;
			cout << endl;
		}
		else if (inMainPortMenu) {
			PrintEmptyLines(MAX_SECONDARY_MENU_LINES - GOOD_TYPES - 4);
			cout << "ESC to return quit game and return to main menu. " << endl;
			PrintEmptyLines(1);
		}
		cout << "================================================================================";



		// REPAIRING SHIP
		// ------------------------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------------------------

		playerShip.setHullPoints(20); // delete - testing

		// Print the Repair ship menu:
		if (repairingShip && !shipRepaired) {

			if (playerShip.getHullPoints() == 100) {
				MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - MAX_SECONDARY_MENU_LINES);
				PrintEmptyLines(1);
				cout << "Your ship is fully repaired.                                                             \n";
				PrintEmptyLines(MAX_SECONDARY_MENU_LINES - 4);
				cout << "Press ESCAPE or INTRO to return to the port's main menu.                                   \n";
				PrintEmptyLines(1);
			}
			else {
				currentWoodUnitPrice = ceil(20 / max(1, allPorts[currentPlayerLocation].getGoodAmount(0) - marketWoodToBeUsed));
				playerShip.getDoublonsAmount() < currentWoodUnitPrice ? playerHasEnoughFunds = false : playerHasEnoughFunds = true;

				// print player and market info
				MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - MAX_SECONDARY_MENU_LINES);
				PrintEmptyLines(1);
				cout << "Your doublons: " << playerShip.getDoublonsAmount() - playerDoublonsToBeUsed << "                                                                  \n";
				cout << "Wood on board: " << playerShip.getGoodAmount(0) - playerWoodToBeUsed << "                                                                       \n";
				cout << "Wood in Market: " << allPorts[currentPlayerLocation].getGoodAmount(0) - marketWoodToBeUsed << " (";
				if (!playerHasEnoughFunds) { c(4); };
				cout << currentWoodUnitPrice; c(15); cout << " doublons per unit).                                               \n";
				PrintEmptyLines(1);

				// Print hull points to be repaired selector
				cout << "HullPoints to be repaired:   ";
				c(SELECTION_COLOR);
				cout << "<-- " << 10 * (playerWoodToBeUsed + marketWoodToBeUsed);
				cout << " -->";
				c(15);
				cout << "     (Current ship hullpoints = " << playerShip.getHullPoints() + 10 * (playerWoodToBeUsed + marketWoodToBeUsed) << ")";
				cout << "                                                                  \n";

				PrintEmptyLines(1);

				cout << "This will cost you ";
				c(6);
				cout << tempWoodBill + ((playerWoodToBeUsed + marketWoodToBeUsed > 0) ? repairShipFee : 0);
				c(15);
				cout << " doublons (" << tempWoodBill << " for purchased wood plus the fixed " << repairShipFee << " doublons fee).";
				cout << "                                                   \n";

				PrintEmptyLines(1);
				c(8);
				cout << "* Repairing your ship requires " << woodFor10Hullpoints << " unit of wood per 10 hullpoints repaired.                      \n";
				cout << "* You will use wood from your cargo, but if you have no wood you can choose to buy it from the market.                     \n";
				cout << "* Every ship repair has a fixed fee of " << repairShipFee << " doublons.                                                   \n";
				c(15);
				//PrintEmptyLines(1);
			}
		}

		// TAVERN
		// ------------------------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------------------------
				// print available destinations only if setting sail:
		if (inTavern) {

			// Move cursor to after the main menu prompt to overwrite the market menu.
			// (the +1 is to take into account the horizontal separation line).
			MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - MAX_SECONDARY_MENU_LINES);
			PrintEmptyLines(1);
			cout << "You enter the port's tavern. Rum is flowing and tongues are loose.                                                            " << endl;
			cout << "\"Shoud I try my luck buying one of these fine sailors a drink? They might have something interesting to tell\"              " << endl;
			PrintEmptyLines(1);

			selector == 0 ? c(SELECTION_COLOR) : c(15);
			cout << "Buy a few drinks for " << drinkPrice << " doublons.";
			c(15);
			cout << "                                                     \n";

			selector == 1 ? c(SELECTION_COLOR) : c(15);
			cout << "Maybe some other time.";
			c(15);
			cout << "                                                               \n";
			PrintEmptyLines(MAX_SECONDARY_MENU_LINES - 6);

		}



		// SET SAIL
		// ------------------------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------------------------

		// print available destinations only if setting sail:
		if (settingSail) {

			// reset port triggering.
			setSailSkipPortTrigger = false;

			// Move cursor to after the main menu prompt to overwrite the market menu.
			// (the +1 is to take into account the horizontal separation line).
			MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - MAX_SECONDARY_MENU_LINES);
			for (int i = 0; i < MAX_SECONDARY_MENU_LINES; i++) {
				if (i < secondaryMenuPrintStart) {
					cout << "                                                                                 \n";
				}
				else if (i == secondaryMenuPrintStart) {

					// the -1 is due to not taking into account the current port
					// we might still need to access all the ports, but the issue is accounted for inside the loop.
					for (int j = 0; j < numberOfPorts - 1; j++) {

						setSailIterator = j;

						// since we don't print the current port, we have to adapt the selector
						if (selector == currentPlayerLocation) {
							setSailSkipPortTrigger = true;
							setSailIterator = j + 1;
						}


						// highlight the currently selected good:
						if (selector == setSailIterator) {
							SetConsoleTextAttribute(OUTPUT_HANDLE, SELECTION_COLOR);
						}

						cout << "            " << allPorts[setSailIterator].getName() << "                                                            " << endl;


						//// Print the port name (jump one if next port to print is the current port;
						//if (setSailSkipPortTrigger == false) {
						//	cout << "            " << allPorts[j].getName() << "                                                            " << endl;
						//}
						//else if (setSailSkipPortTrigger == true) {
						//	cout << "            " << allPorts[j + 1].getName() << "                                                         " << endl;
						//}

						// Reset output format for unselected menu options:
						if (selector == setSailIterator) {
							SetConsoleTextAttribute(OUTPUT_HANDLE, 15);
						}

						// adjust the selection if the current iteration is the current port.			
					/*	if (setSailSkipPortTrigger == true) {
							selector++;
						}*/

					}

					for (int j = 0; j < secondaryMenuPrintStart + numberOfPorts - 4; j++) {
						cout << "                                                                                 \n";
					}
					cout << "INTRO to sail to destination  -  ESCAPE to stay in " << allPorts[currentPlayerLocation].getName() << endl;
					cout << "                                                                                                            ";
				}
			}
		}




		// MENU CONTROLS
		// ------------------------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------------------------
		do {
			// Do nothing if intro key remains pressed. It prevents accidental action triggers when returning from other menus.
		} while (GetAsyncKeyState(VK_RETURN) != 0);


		// Implement arrow key controls:
		while (true) {

			// DOWN ARROW BEHAVIOUR
			// GetAsyncKeyState() checks it the down arrow key has been pressed (value 0 indicates not pressed).
			// down arrow disabled if repairing ship
			if (GetAsyncKeyState(VK_DOWN) != 0 && !repairingShip) {

				// Once the down key is pressed, cycle to the next menuOption:
				selector++;
				// Cycle back to the first option after the last option.
				if (inMainPortMenu && selector == numberOfMenuOptions) {
					selector = 0;
				}
				else if (inMarketMenu && selector == GOOD_TYPES) {
					selector = 0;
				}
				// -1 because we don't take the current port into account.
				else if (settingSail && selector == numberOfPorts - 1) {
					selector = 0;
				}
				else if (inTavern && selector == 2) {
					selector = 0;
				}



				// Do the same if browsing the market instead of the port menu (for instance, 0,1,2,3 would be the port menu
				// while 5,6,7,8,9,10 would be the market menu. Values 5 and 
				/*		if (selector == numberOfMenuOptions + GOOD_TYPES + 1) {
					selector = numberOfMenuOptions + 1;
				}*/

				// Break so that the menu gets refreshed to display the new selection:
				break;
			}



			// UP ARROW BEHAVIOUR
			// up arrow disabled if repairing ship
			if (GetAsyncKeyState(VK_UP) != 0 && !repairingShip) {
				selector--;
				// Cycle back to the first option after the last option.
				if (inMainPortMenu && selector == -1) {
					selector = numberOfMenuOptions - 1;
				}
				else if (inMarketMenu && selector == -1) {
					selector = GOOD_TYPES - 1;
				}
				else if (settingSail && selector == -1) {
					// -2 because we don't take the current port into account.
					selector = numberOfPorts - 2;
				}
				else if (inTavern && selector == -1) {
					selector = 1;
				}

				// Break so that the menu gets refreshed to display the new selection:
				break;
			}




			// ESCAPE BEHAVIOUR
			else if (GetAsyncKeyState(VK_ESCAPE) != 0) {

				if (!inMainPortMenu) {

					if (repairingShip && !shipRepaired) {

						tempWoodBill = 0;
						playerWoodToBeUsed = 0;
						marketWoodToBeUsed = 0;
					}

					inMarketMenu = false;
					settingSail = false;
					repairingShip = false;
					inMainPortMenu = true;
					selector = 0;
				}
				else {
					// QUIT TO MAIN MENU SCREEN
					// ************************************

					// reset flag
					keepPlaying = false;

					PrintPortMenuHeader("Quit game and go back to main menu?");
					PrintEmptyLines(2);

					// print confirmation selector

					string quitToMainMenuOptions[2] = { "Keep playing", "Quit to main menu" };
					int numberOfQuitToMainOptions = sizeof(quitToMainMenuOptions) / sizeof(quitToMainMenuOptions[0]);


					// An enumeration just for clarity in the switch statement below.
					enum quitToMainMenuOptions {
						KeepPlaying,
						QuitToMain,
					};


					// Create scrolling menu controlled by arrow keys instead of single key inputs
					while (!keepPlaying) {

						MoveCursorTo(0, MAIN_GAME_MENU_START);
						PrintEmptyLines(1);

						// Display menu options and highlight currently selected option:
						for (int i = 0; i < numberOfQuitToMainOptions; i++) {

							if (i == selector) {
								c(SELECTION_COLOR);
							}
							cout << quitToMainMenuOptions[i] << endl;
							c(15);

						}

						PrintEmptyLines(PORT_MAIN_MENU_LINES + MAX_SECONDARY_MENU_LINES - 3);

						do {
							// Do if intro key is pressed. It prevents accidental action triggers when returning from other menus.
						} while (GetAsyncKeyState(VK_RETURN) != 0);


						// Implement arrow key controls:
						while (!keepPlaying) {

							// GetAsyncKeyState() checks it the down arrow key has been pressed (value 0 indicates not pressed):
							if (GetAsyncKeyState(VK_DOWN) != 0) {

								// Once the down key is pressed, cycle to the next menuOption:
								selector++;
								// Cycle back to the first option after the last option.
								if (selector == numberOfQuitToMainOptions) {
									selector = 0;
								}

								// Break so that the menu gets refreshed to display the new selection:
								break;
							}

							// Do the reverse for the up arrow key:
							else if (GetAsyncKeyState(VK_UP) != 0) {
								selector--;
								// Cycle back to the first option after the last option.
								if (selector == -1) {
									selector = numberOfQuitToMainOptions - 1;
								}

								// Break so that the menu gets refreshed to display the new selection:
								break;
							}

							// Implement option selection with return key:
							else if (GetAsyncKeyState(VK_RETURN) != 0) {

								switch (selector)
								{
								case KeepPlaying:
									// continue playing as normal
									keepPlaying = true;
									break;
								case QuitToMain:
									selector = 0;
									return -10;
									//GoToMainMenu();
									//break;
								default:
									break;
								}

							}
						}

						// Workaround to lower the arroy input "sensitivity" (Slightly delay the program so that a single arrow key press is not registered multiple times).
						// It prevents the menu going down or up several times when pressing an arrow key if we only want it to move a single step.
						Sleep(120);
					}
				}

				break;
			}

			// RIGHT ARROW BEHAVIOUR
			else if (GetAsyncKeyState(VK_RIGHT) != 0) {

				// Left and right arrow (sell and buy) functionality only when in the market menu:
				if (inMarketMenu) {

					// Purchase selected good if available at the market and the players has enough funds
					if (allPorts[currentPlayerLocation].getGoodAmount(selector) > 0) {

						// buy only if the player has enough funds:
						if (playerShip.getDoublonsAmount() >= ceil(20 / max(1, allPorts[currentPlayerLocation].getGoodAmount(selector)))) {

							allPorts[currentPlayerLocation].setGoodAmount(selector, allPorts[currentPlayerLocation].getGoodAmount(selector) - 1);
							playerShip.setGoodAmount(selector, playerShip.getGoodAmount(selector) + 1);

							// subtract money from the player's purse
							playerShip.setDoublonsAmount(playerShip.getDoublonsAmount() - ceil(20 / max(1, allPorts[currentPlayerLocation].getGoodAmount(selector))));
						}
					}
				}


				// RIGHT ARROW REPAIRING SHIP BEHAVIOUR
				if (repairingShip && !shipRepaired && playerWoodToBeUsed + marketWoodToBeUsed < 10 && playerShip.getHullPoints() < 100) {

					if (playerShip.getGoodAmount(0) - playerWoodToBeUsed > 0) {
						playerWoodToBeUsed++;
					}
					else if (allPorts[currentPlayerLocation].getGoodAmount(0) - marketWoodToBeUsed > 0) {
						marketWoodToBeUsed++;
						tempWoodBill += currentWoodUnitPrice;
					}
				}


				break;
			}

			// LEFT ARROW BEHAVIOUR
			else if (GetAsyncKeyState(VK_LEFT) != 0) {

				if (inMarketMenu) {
					// Sell the selected good while available on the ship
					if (playerShip.getGoodAmount(selector) > 0) {

						allPorts[currentPlayerLocation].setGoodAmount(selector, allPorts[currentPlayerLocation].getGoodAmount(selector) + 1);
						playerShip.setGoodAmount(selector, playerShip.getGoodAmount(selector) - 1);

						// add profit to the player's purse:
						playerShip.setDoublonsAmount(playerShip.getDoublonsAmount() + ceil(20 / max(1, allPorts[currentPlayerLocation].getGoodAmount(selector))));
					}
				}

				// LEFT ARROW REPAIRING SHIP BEHAVIOUR
				if (repairingShip && !shipRepaired && playerWoodToBeUsed + marketWoodToBeUsed > 0) {

					if (marketWoodToBeUsed > 0) {
						marketWoodToBeUsed--;
						tempWoodBill -= currentWoodUnitPrice;
					}
					else if (playerWoodToBeUsed > 0) {
						playerWoodToBeUsed--;
					}

				}


				break;
			}



			// Implement option selection with return key:
			else if (GetAsyncKeyState(VK_RETURN) != 0) {

				// Intro behaviour if in the main port menu

				if (inMainPortMenu) {
					// An enumeration just for clarity in the switch statement below.
					enum portMenuOptions {
						BuyAndSellGoods,
						RepairShip,
						VisitTavern,
						SetSail,
					};

					switch (selector)
					{
					case BuyAndSellGoods:
						/*selector = numberOfMenuOptions + 1;*/
						inMainPortMenu = false;
						inMarketMenu = true;
						selector = 0;
						break;

					case RepairShip:
						inMainPortMenu = false;
						repairingShip = true;
						//shipRepaired = false; // delete
						selector = 0;
						break;

					case VisitTavern:
						inMainPortMenu = false;
						inTavern = true;
						selector = 0;
						break;

					case SetSail:
						inMainPortMenu = false;
						settingSail = true;
						selector = 0;
						break;

					default:
						break;
					}
				}
				// Intro behaviour repairing ship
				else if (repairingShip && !shipRepaired && !(playerShip.getHullPoints() == 100)) {

					playerShip.setGoodAmount(0, playerShip.getGoodAmount(0) - playerWoodToBeUsed);
					allPorts[currentPlayerLocation].setGoodAmount(0, allPorts[currentPlayerLocation].getGoodAmount(0) - marketWoodToBeUsed);
					playerShip.setDoublonsAmount(playerShip.getDoublonsAmount() - tempWoodBill);
					playerShip.setHullPoints(max(100, playerShip.getHullPoints() + 10 * (playerWoodToBeUsed + marketWoodToBeUsed)));

					shipRepaired = true;
				}
				else if (repairingShip && (shipRepaired || playerShip.getHullPoints() == 100)) {
					inMainPortMenu = true;
					repairingShip = false;
					selector = 0;
				}
				// Behaviour if in tavern
				else if (inTavern) {
					if (selector == 0) {

						MoveCursorTo(0, SECONDARY_MENU_START);
						PrintEmptyLines(1);

						if (playerShip.getDoublonsAmount() < drinkPrice) {
							cout << "You don't have enough doublons.                                                                 \n";
						}
						else {
							playerShip.setDoublonsAmount(playerShip.getDoublonsAmount() - drinkPrice);

							// generate a safe and a danerous route that the player wont know unless he gossips:
							dangerousRoute = rand() % numberOfPorts;
							safeRoute = rand() % numberOfPorts;

							cout << "One of the drunken sailors you have invited to a drink tells you:                                        \n";
							// Give some random gossip
							switch (rand() % 3)
							{
							case 0:
								cout << "\"I hear the route to " << allPorts[dangerousRoute].getName() << " is infested with pirates. Avoid if if you don't want a fight!\"                                  \n";
								break;
							case 1:
								cout << "\"Our trip back from " << allPorts[safeRoute].getName() << " was quite pleasant. Not a pirate in sight.\"                                            \n";

								break;
							case 2:
								diceRoll1 = rand() % numberOfPorts;
								diceRoll2 = rand() % GOOD_TYPES;
								cout << "\"I just came from " << allPorts[diceRoll1].getName() << " and the price of " << GOOD_NAMES[diceRoll2] << " was " << allPorts[diceRoll1].getGoodAmount(diceRoll2) << ".\"                                   \n";
								break;
							default:
								break;
							}
						}

						PrintEmptyLines(MAX_SECONDARY_MENU_LINES -5);
						cout << "Press any key to go back to the port's menu";
						cout << "                                                  \n";
						system("pause > nul");


					}
					//else if (selector == 1) {
					inTavern = false;
					inMainPortMenu = true;
					selector = 0;
					//}
				}
				// Intro behaviour if setting sail
				else if (settingSail) {

					// adjust selection to port selection (to avoid choosing the current port)
					if (setSailSkipPortTrigger == true) {
						selector++;
					}

					// return the chosen destination.
					switch (selector)
					{
					case 0:
						return 0;
					case 1:
						return 1;
					case 2:
						return 2;
					case 3:
						return 03;

					default:
						break;
					}
				}

				// break out of the if
				break;
			}
		}

		// Workaround to lower the arroy input "sensitivity" (Slightly delay the program so that a single arrow key press is not registered multiple times).
		// It prevents the menu going down or up several times when pressing an arrow key if we only want it to move a single step.
		Sleep(150);

		// Move cursor to the end of the map to reprint only the menu (printing the map is very slow).
		MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - MAX_PORT_MENU_LINES);
	} //end of while (print port menu)
}



// MAIN GAME FUNCTION
// =====================================================================================================================
// =====================================================================================================================

int StartGame(int captainSelection) {
	system("cls");

	int turn = 1;


	// CREATE PORT CLASS INSTANCES (Objects)
	const int numberOfPorts = 4;

	CPort frenchPort("Le Petit Champlain");
	CPort spanishPort("Nueva Granada de Indias");
	CPort englishPort("Port Royale");
	CPort dutchPort("Sint Maarten");

	// add all ports to an array of CPort objects to iterate between them easily as the player change slocations.
	CPort allPorts[numberOfPorts] = { dutchPort, englishPort, frenchPort, spanishPort };


	// a variables to be modified dynamically in the port menu
	int dangerousRoute = -1;
	int safeRoute = -1;

	// SETUP INITIAL PLAYER CONDITIONS

	// randomize the starting port
	srand(time(NULL)); // initialize rand() seed;
	int currentPlayerLocation = rand() % numberOfPorts;

	int playerDoublons = 50;

	CShip playerShip;


	// PORT ACTIONS
	// keep visiting ports and taking actions until an end condition is met.
	do {
		currentPlayerLocation = GoToPortMenu(allPorts, currentPlayerLocation, playerShip, captainSelection, numberOfPorts, dangerousRoute, safeRoute);

		// currentPlayerLocation is the return integer from GoToPortMenu(), if -10 it means the players is going to back to the main menu
		if (currentPlayerLocation == -10) { return 0; };

		PirateCheck(playerShip, captainSelection, dangerousRoute, safeRoute, currentPlayerLocation);
		// advance one turn;
		turn++;
	} while (true);






	//cout << "******************************************************" << endl;
	//cout << endl;
	//cout << "Location: " << frenchPort.getName()<< endl;
	//for (int i = 0; i < GOOD_TYPES; i++) {
	//	cout << GOOD_NAMES[i] << ": " << frenchPort.getGoodAmount(i) << endl;
	//}
	//cout << endl;
	//cout << "******************************************************" << endl;
	//cout << endl;
	//cout << "Location: " << spanishPort.getName() << endl;
	//for (int i = 0; i < GOOD_TYPES; i++) {
	//	cout << GOOD_NAMES[i] << ": " << spanishPort.getGoodAmount(i) << endl;
	//}
	//cout << endl;
	//cout << "******************************************************" << endl;
	//cout << endl;
	//cout << "Location: " << englishPort.getName() << endl;
	//for (int i = 0; i < GOOD_TYPES; i++) {
	//	cout << GOOD_NAMES[i] << ": " << englishPort.getGoodAmount(i) << endl;
	//}
	//cout << endl;
	//cout << "******************************************************" << endl;
	//cout << endl;
	//cout << "Location: " << dutchPort.getName() << endl;
	//for (int i = 0; i < GOOD_TYPES; i++) {
	//	cout << GOOD_NAMES[i] << ": " << dutchPort.getGoodAmount(i) << endl;
	//}
	//cout << endl;
	//cout << "******************************************************" << endl;








	system("pause");
	return 0;
}