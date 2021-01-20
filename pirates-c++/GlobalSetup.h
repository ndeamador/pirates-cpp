#pragma once
#include <Windows.h> //required for handle
#include <string>

using namespace std;

// These are variables that I have decided to define as global for two reasons:
// 1. Some are used across different files and it's more convenient and consisten to be able to modify them just once.
// 2. Development convenience. Easier to access when I have to try different values.
const int GOOD_TYPES = 6;
const int MAX_GOOD_AMOUNT = 12;
const string GOOD_NAMES[GOOD_TYPES] = { "Wood", "Exotic Fruits", "Sugar Cane", "Rum", "Metals", "Cannons" };
const HANDLE OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
const int MAX_HORIZONTAL_CHARACTERS = 165;
const int MAX_VERTICAL_CHARACTERS = 44;
const int SELECTION_COLOR = 10;
const string LOG_FILE_NAME = "gameLogs.txt";
const char LOG_SEPARATOR = ';';
const int PIXEL_WIDTH = 1366;
const int PIXEL_HEIGHT = 768;


// Other onvenience globals
const int PORT_HEADER_LINES = 4;
const int PORT_MAIN_MENU_LINES = 5;
const int MAX_SECONDARY_MENU_LINES = 13;
const int MAX_PORT_MENU_LINES = PORT_HEADER_LINES + PORT_MAIN_MENU_LINES + MAX_SECONDARY_MENU_LINES;
const int HEADER_START = MAX_VERTICAL_CHARACTERS - MAX_PORT_MENU_LINES;
const int MAIN_GAME_MENU_START = MAX_VERTICAL_CHARACTERS - MAX_PORT_MENU_LINES + PORT_HEADER_LINES;
const int SECONDARY_MENU_START = MAX_VERTICAL_CHARACTERS - MAX_SECONDARY_MENU_LINES;



