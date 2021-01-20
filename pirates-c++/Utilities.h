#pragma once

#include <fstream>
#include <string>
#include "Classes.h"

using namespace std;


void MoveCursorTo(int, int);

void LoadLogData(ifstream&, string, int&, int&);


void ToggleConsoleCursor(bool);

//void EnableFullScreen();

void SetConsoleWindowSize(int, int);

//void UnicodeToggle(int);
