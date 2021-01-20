#pragma once

#include <iostream>

using namespace std;


// *************************************************************************************
// This file contains code that I have used as tools to help my development but that are
// not used in the final game and can therefore be ignored for the project's evaluation.
// *************************************************************************************

// Test number of horizontal character "pixels" on screen:
void countHorChPixels() {
	
	for (int j = 0; j < 30; j++) {

		if ((j+1) % 10 == 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);
		}
		else if (j % 2 == 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
		}

		for (int i = 0; i < 10; i++) {
			cout << i;
		}			
	}

	// reset to normal
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << endl;

}

// Test number of vertical character "pixels" on screen:
void countVerChPixels() {

	system("cls");

	for (int j = 0; j < 100; j++) {
		cout << j << endl;
	}
}

