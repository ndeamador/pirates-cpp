#include "Navigation.h"
#include "Classes.h"
#include "Graphics.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <stdlib.h> //enables the method exit();
#include <iomanip> // to format table-like output in operator overloading


// making sure that the sleep function works for both Windows and Linux/Unix
// windows.h also includes the GetAsyncKeyState() method required for the arrow controls.
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

void GoToTipsAndRules() {
    system("cls");

    int margin = 2; 

    IncreaseMargin(margin); cout << "\n\n";
    IncreaseMargin(margin);IncreaseMargin(margin); cout << "  TIPS AND RULES\n";
    IncreaseMargin(margin); cout << "  =================================================================================================================================\n\n";
    IncreaseMargin(margin); cout << "  HOW TO PLAY" << endl;
    IncreaseMargin(margin); cout << "  ---------------------------------------------------------------------------------------------------------------------------------\n\n";
    IncreaseMargin(margin);(margin); cout << "  * You will start the game at a given port." << endl;
    IncreaseMargin(margin); cout << "  * First thing you should do is to buy some cargo at the port's market to sell it somewhere else." << endl;
    IncreaseMargin(margin); cout << "  * Every time you sail to a different port, there will be an increased chance of encountering pirates. Have your cannons ready!" << endl;
    IncreaseMargin(margin); cout << "  * The game will guide you through each phase, so don't be afraid and just jump in!" << endl;
    IncreaseMargin(margin); cout << "\n\n";
    IncreaseMargin(margin); cout << "  TIPS" << endl;
    IncreaseMargin(margin); cout << "  ---------------------------------------------------------------------------------------------------------------------------------\n\n";
    IncreaseMargin(margin); cout << "  * Visit the port's tavern to try and get some helful gossip." << endl;
    IncreaseMargin(margin); cout << "  * If you think a pirate is too powerfull for you, you can always try to run away." << endl;
    IncreaseMargin(margin); cout << "  * Cannons are regular sellable cargo, but be careful not to leave your ship undefended." << endl;
    IncreaseMargin(margin); cout << "  * Market prices adjust dynamically accodring to supply and demand. The fewer units of a good in a port, the more expensive it is." << endl;
    IncreaseMargin(margin); cout << "  * Ports are really wealthy, they will always have money to buy your cargo." << endl;
    IncreaseMargin(margin); cout << "  * Combat will never last more than 5 rounds. If 5 rounds are played, the ship wich has taken the most damage loses." << endl;
    MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - 2);
    //PrintWavyMessage("Press any key to return to the main menu", 2, 150);
    IncreaseMargin(margin); cout << "  Press any key to return to the main menu\n\n";
    system("pause > nul");  //prevent pause from printing its message so that we can print our own custom message.

}


void GoToViewScoreboard(int numberOfRecords, CPlayer * playerRecords) {
    system("cls");

    int margin = 2;

    PrintEmptyLines(2);
    IncreaseMargin(margin); cout << "SCOREBOARD\n";
    IncreaseMargin(margin); cout << "========================================================================================\n\n";
    IncreaseMargin(margin); cout << "       " << setw(32) << left << "Player" << setw(32) << left << "Wealth per turn" << setw(32) << left << "Career Outcome" << endl;
    IncreaseMargin(margin); cout << endl;
    // Display only the top 15 results.
    for (int i = 0; i < min(numberOfRecords, 15); i++) {
        IncreaseMargin(margin); cout << "   "<<playerRecords[i] << endl;
    }
    PrintEmptyLines(1);
    IncreaseMargin(margin); cout << "========================================================================================\n\n";
    MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - 2);
    IncreaseMargin(margin); cout << "Press any key to return to the main menu" << endl;
    //PrintWavyMessage("Press any key to return to the main menu", 2, 150);
    system("pause > nul"); //prevent pause from printing its message so that we can print our own custom message.
};


int GoToCharacterSelection() {
    system("cls");

    int selector = 0;
    string captains[4] = { "Dutch Captain", "English Captain", "French Captain", "Spanish Captain" };
    int numberOfCaptains = sizeof(captains) / sizeof(captains[0]);

    enum menuOptions {
        DutchCaptain,
        EnglishCaptain,
        FrenchCaptain,
        SpanishCaptain,
    };


    cout << "SELECT YOUR CAPTAIN" << endl;

    while (true) {
        system("cls");

    /*    for (int i = 0; i < numberOfCaptains; i++) {
            if (i == selector) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << captains[i];
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << captains[i];
            }
        }*/

        PrintCaptainBoxes(selector);
        PrintEmptyLines(2);
        PrintShip(selector);
        PrintEmptyLines(1);
        IncreaseMargin(MAX_HORIZONTAL_CHARACTERS - 72);
        cout << "Press ESCAPE to return to main menu or INTRO to select your captain." << endl;


        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

        // Do nothing if intro key remains pressed. It prevents accidental character selection when coming from the main menu.
        do {
        } while (GetAsyncKeyState(VK_RETURN) != 0);

        while (true) {

            if (GetAsyncKeyState(VK_RIGHT) != 0) {
                selector++;
                if (selector == numberOfCaptains) {
                    selector = 0;
                }
                break;
            }
            else if (GetAsyncKeyState(VK_LEFT) != 0) {
                selector--;
                if (selector == -1) {
                    selector = numberOfCaptains - 1;
                }
                break;
            }
            else if (GetAsyncKeyState(VK_RETURN) != 0) {

                switch (selector)
                {
                case DutchCaptain:                    
                    return 0;
                case EnglishCaptain:
                    return 1;
                case FrenchCaptain:
                    return 2;
                case SpanishCaptain:
                    return 3;
                default:
                    break;
                }
            }
            else if (GetAsyncKeyState(VK_ESCAPE) != 0) {
                // Bugged, disabled until fixed.
                //GoToMainMenu();
                ////return -1;
                return -10;
            }
        }

        Sleep(140);

    }
};


int GoToMainMenu() {
    int selector = 0; 
    
    string menuOptions[4] = { "START NEW GAME", "Tips and Rules", "Scoreboard", "Exit" };
    int numberOfOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

    int mainMenuMargin = 70;

    // An enumeration just for clarity in the switch statement below.
    enum menuOptions {
        StartGame,
        TipsAndRules,
        Scoreboard,
        ExitGame,
    };


    // Create scrolling menu controlled by arrow keys instead of single key inputs
    while (true) {
        //Refresh screen output everytime a different option is selected.
        system("cls");


        //cout << "MY PIRATES GAME\n\n";
        PrintEmptyLines(10);
        PrintMainMenuBanner(25);
        PrintEmptyLines(5);

        // Display menu options and highlight currently selected option:
        for (int i = 0; i < numberOfOptions; i++) {

            if (i == selector) {

                // A not very elegant way of centering my menu:
                switch (i)
                {
                case 0:
                    IncreaseMargin(mainMenuMargin);
                    break;
                case 1:
                    IncreaseMargin(mainMenuMargin);
                    break;

                case 2:
                    IncreaseMargin(mainMenuMargin+2);
                    break;

                case 3:
                    IncreaseMargin(mainMenuMargin+5);
                    break;
                default:
                    break;
                }

                c(SELECTION_COLOR);
                cout <<">> " << menuOptions[i] << " <<\n";
                c(15);
            }
            else {
                switch (i)
                {
                case 0:
                    IncreaseMargin(mainMenuMargin);
                    break;
                case 1:
                    IncreaseMargin(mainMenuMargin);
                    break;

                case 2:
                    IncreaseMargin(mainMenuMargin+2);
                    break;

                case 3:
                    IncreaseMargin(mainMenuMargin+5);
                    break;
                default:
                    break;
                }

                // compensate for the arrow extra margin
                IncreaseMargin(3);

                cout << menuOptions[i] << endl;
            }

        }

        do {
            // Do if intro key is pressed. It prevents accidental action triggers when returning from other menus.
        } while (GetAsyncKeyState(VK_RETURN) != 0);


        // Implement arrow key controls:
        while (true) {

            // GetAsyncKeyState() checks it the down arrow key has been pressed (value 0 indicates not pressed):
            if (GetAsyncKeyState(VK_DOWN) != 0) {                              

                // Once the down key is pressed, cycle to the next menuOption:
                selector++;
                // Cycle back to the first option after the last option.
                if (selector == numberOfOptions) {
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
                    selector = numberOfOptions-1;
                }

                // Break so that the menu gets refreshed to display the new selection:
                break;
            }

            // Implement option selection with return key:
            else if (GetAsyncKeyState(VK_RETURN) != 0) {

                return selector;
                
                //// If the last option is selected, exit the game, otherwise, return selection.
                //if (selector < numberOfOptions - 1) {
                //    return selector;
                //}
                //else {              
                //    system("cls");
                //    cout << "Exiting game..." << endl;
                //    Sleep(2000);
                //    exit(0);
                //}
            }
        }

        // Workaround to lower the arroy input "sensitivity" (Slightly delay the program so that a single arrow key press is not registered multiple times).
        // It prevents the menu going down or up several times when pressing an arrow key if we only want it to move a single step.
        Sleep(120);
    }
};




