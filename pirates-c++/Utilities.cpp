#include "Utilities.h"
#include "GlobalSetup.h"
#include "Classes.h"

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


void MoveCursorTo(int x, int y) {

	COORD coord = { x, y };
	SetConsoleCursorPosition(OUTPUT_HANDLE, coord);
}


// Counts number of lines and number of attributes per line in the external file.
// It is the same function I used in my exam
void LoadLogData(ifstream& databaseRead, string filename, int& numberOfItemsPerLine, int& numberOfLinesInFile) {

	string temporaryStringDump;
	int currentLineDelimiterCount = 0;

	// Should the function be called more than once, make sure that the numbers don't add up:
	numberOfLinesInFile = 0;
	numberOfItemsPerLine = 0;


	//  Open file read stream.
	databaseRead.open(filename);

	// loop until the end of file (or until an error is thrown)
	while (databaseRead.good()) {

		// Find the next line break (default third argument of getline) and add one line to the count.
		getline(databaseRead, temporaryStringDump);
		numberOfLinesInFile++;


		// Count the number of appearances of the delimiter in the current line.
		currentLineDelimiterCount = count(temporaryStringDump.begin(), temporaryStringDump.end(), LOG_SEPARATOR);

		// If the curren number of delimiter appearances is larger than the stored maximum, replace the values:
		// Add one since the number of words per line is the number of delimiters+1
		if (currentLineDelimiterCount + 1 > numberOfItemsPerLine) {
			numberOfItemsPerLine = currentLineDelimiterCount + 1;
		}
	}

	// close the file read stream
	databaseRead.close();
}





// Hide the blinking cursor
void ToggleConsoleCursor(bool showFlag)
{

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(OUTPUT_HANDLE, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(OUTPUT_HANDLE, &cursorInfo);
}


//// Play the game in fullscreen.
//void EnableFullScreen() {
//	SetConsoleDisplayMode(OUTPUT_HANDLE, CONSOLE_FULLSCREEN_MODE, 0);
//}

// Set default console size at startup 
void SetConsoleWindowSize(int width, int height) {
	// Implementaiton 1:
	//HWND console = GetConsoleWindow();
	//RECT ConsoleRect;
	//GetWindowRect(console, &ConsoleRect);
	//MoveWindow(console, ConsoleRect.left, ConsoleRect.top, width, height, TRUE);



	// Implementation 2:
	// Get console window handle
	HWND wh = GetConsoleWindow();

	// Move window to required position
	MoveWindow(wh, 100, 100, width, height, TRUE);
}

//// Enable unicode characters
//void UnicodeToggle(int toggle) {
//	//SetConsoleCP(437);
//	//SetConsoleOutputCP(437);
//	// store current console output in variable:
//	static UINT oldcp = GetConsoleOutputCP();
//
//	if (toggle == 1) {
//
//		// Change console output to UTF-8:
//		SetConsoleOutputCP(CP_UTF8);
//	}
//
//	if (toggle == 0) {
//
//		// Reset console output:
//		SetConsoleOutputCP(oldcp);
//	}
//}


