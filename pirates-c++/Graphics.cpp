#include "Graphics.h"
#include "GlobalSetup.h"
#include "Utilities.h"
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

// Hexadecimal color values:
	//0 = Black       8 = Gray
	//1 = Blue        9 = Light Blue
	//2 = Green       A = Light Green
	//3 = Aqua        B = Light Aqua
	//4 = Red         C = Light Red
	//5 = Purple      D = Light Purple
	//6 = Yellow      E = Light Yellow
	//7 = White       F = Bright White

// A few global constants that should be changed if the game's resolution is modified.
//const int MAX_HORIZONTAL_CHARACTERS = 165;
//const int MAX_VERTICAL_CHARACTERS = 44;
//const int MAX_PORT_MENU_LINES = 22;


// just a funciton to shorten the text color command and make ascii art easier to code
void c(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void IncreaseMargin(int margin) {
	for (int i = 0; i < margin; i++) {
		cout << " ";
	}
}

void PrintFlag(int nation) {

	// flag design:
	int flagColor1 = 17;
	int flagColor2 = 255;
	int flagColor3 = 17;
	char flagSymbol1 = '=';
	char flagSymbol2 = '=';
	char flagSymbol3 = '=';

	enum nations {
		Netherlands,
		England,
		France,
		Spain,
		Ottomans,
		QingChina,
		Scotland,
	};

	switch (nation)
	{
	case Netherlands:
		flagColor1 = 204;
		flagColor2 = 255;
		flagColor3 = 153;
		break;
	case England:
		// England's St.George flat
		flagSymbol1 = '-';
		flagSymbol2 = '+';
		flagSymbol3 = '-';
		//flagSymbol1 = '═';
		//flagSymbol2 = '╬';
		//flagSymbol3 = '═';
		flagColor1 = 116;
		flagColor2 = 116;
		flagColor3 = 116;
		break;
	case France:
		// An attempt to recreate the Fleur de Lys as the french sigil
		flagSymbol1 = '>';
		flagSymbol2 = '|';
		/*  flagSymbol2 = '⚜';*/
		flagSymbol3 = '<';
		flagColor1 = 30;
		flagColor2 = 30;
		flagColor3 = 30;
		break;
	case Spain:
		// Habsburg Spain's Cross of Burgundy flag (yellow version)
		flagSymbol1 = ' ';
		flagSymbol2 = 'X';
		flagSymbol3 = ' ';
		flagColor1 = 68;
		flagColor2 = 100;
		flagColor3 = 68;
		break;
	case Ottomans:
		flagSymbol1 = ' ';
		flagSymbol2 = 'C';
		flagSymbol3 = ' ';
		flagColor1 = 68;
		flagColor2 = 71;
		flagColor3 = 68;
		break;
	case QingChina:
		flagSymbol1 = '~';
		flagSymbol2 = '\\';
		flagSymbol3 = ' ';
		flagColor1 = 97;
		flagColor2 = 97;
		flagColor3 = 254;
		break;
	case Scotland:
		flagSymbol1 = ' ';
		flagSymbol2 = 'X';
		flagSymbol3 = ' ';
		flagColor1 = 31;
		flagColor2 = 31;
		flagColor3 = 31;
		break;
	default:
		break;
	}

	c(flagColor1); cout << flagSymbol1; c(flagColor2); cout << flagSymbol2; c(flagColor3); cout << flagSymbol3; c(15); cout << "";

}

void PrintShip(int nation) {
	// PREVIEW:
	//cout << "            |       " << endl;
	//cout << "            |===    " << endl;
	//cout << "            |       " << endl;
	//cout << "        =========   " << endl;
	//cout << "         &&&&&&&    " << endl;
	//cout << "     =======&&&&    " << endl;
	//cout << "&     %%%%%&&&&&    " << endl;
	//cout << " &    %%%%%&&&&     " << endl;
	//cout << "  &&  %%%%% |  & & &" << endl;
	//cout << "   &&   |   |  &&&&&" << endl;
	//cout << "   ===o=o=o=o=o=====" << endl;
	//cout << "    &&&&&&&&&&&&&&& " << endl;
	//cout << "     &&&&&&&&&&&&&  " << endl;

	// flag design:
	int flagColor1 = 17;
	int flagColor2 = 255;
	int flagColor3 = 17;
	char flagSymbol1 = '=';
	char flagSymbol2 = '=';
	char flagSymbol3 = '=';

	// ship design:
	int hc = 102;// hull color
	int mc = 6; // mast color
	int cc = 96; // cannons deck color




	enum nations {
		Netherlands,
		England,
		France,
		Spain,
	};

	switch (nation)
	{
	case Netherlands:
		flagColor1 = 204;
		flagColor2 = 255;
		flagColor3 = 153;
		break;
	case England:
		// England's St.George flat
		flagSymbol1 = '-';
		flagSymbol2 = '+';
		flagSymbol3 = '-';
		//flagSymbol1 = '═';
		//flagSymbol2 = '╬';
		//flagSymbol3 = '═';
		flagColor1 = 116;
		flagColor2 = 116;
		flagColor3 = 116;
		break;
	case France:
		// An attempt to recreate the Fleur de Lys as the french sigil
		flagSymbol1 = '>';
		flagSymbol2 = '|';
		/*  flagSymbol2 = '⚜';*/
		flagSymbol3 = '<';
		flagColor1 = 30;
		flagColor2 = 30;
		flagColor3 = 30;
		break;
	case Spain:
		// Habsburg Spain's Cross of Burgundy flag (yellow version)
		flagSymbol1 = ' ';
		flagSymbol2 = 'X';
		flagSymbol3 = ' ';
		flagColor1 = 68;
		flagColor2 = 100;
		flagColor3 = 68;
		break;
	default:
		break;
	}

	// coloured version:
	cout << "      " << "            "; c(mc); cout << "|"; c(15); cout << "       " << endl;
	//cout << "            "; c(mc); cout << "|"; c(17); cout << "="; c(255); cout << "="; c(68); cout << "="; c(15); cout << "    " << endl;
	cout << "      " << "            "; c(mc); cout << "|"; c(flagColor1); cout << flagSymbol1; c(flagColor2); cout << flagSymbol2; c(flagColor3); cout << flagSymbol3; c(15); cout << "    " << endl;
	cout << "      " << "            "; c(mc); cout << "|"; c(15); cout << "       " << endl;
	cout << "      " << "        "; c(hc); cout << "========="; c(15); cout << "   " << endl;
	cout << "      " << "         "; c(238); cout << "&&&&&&&"; c(15); cout << "    " << endl;
	cout << "      " << "     "; c(hc); cout << "======="; c(238); cout << "&&&&"; c(15); cout << "    " << endl;; c(15);
	cout << "      "; c(hc); cout << "&"; c(15); cout << "     "; c(255); cout << "%%"; c(68); cout << "%"; c(255); cout << "%%"; c(238); cout << "&&&&&"; c(15); cout << "    " << endl;
	cout << "      " << " "; c(hc); cout << "&"; c(15); cout << "    "; c(68); cout << "%%%%%"; c(238); cout << "&&&&"; c(15); cout << "     " << endl;
	cout << "      " << "  "; c(hc); cout << "&&"; c(15); cout << "  "; c(255); cout << "%%"; c(68); cout << "%"; c(255); cout << "%%"; c(15); cout << " "; c(mc); cout << "|"; c(15); cout << "  "; c(hc); cout << "&"; c(15); cout << " "; c(hc); cout << "&"; c(15); cout << " "; c(hc); cout << "&" << endl; c(15);
	cout << "      " << "   "; c(hc); cout << "&&"; c(15); cout << "   "; c(mc); cout << "|"; c(15); cout << "   "; c(mc); cout << "|"; c(15); cout << "  "; c(hc); cout << "&&&&&" << endl; c(15);
	cout << "      " << "   "; c(cc); cout << "===o=o=o=o=o=====" << endl; c(15);
	//cout << "      " << "    "; c(hc); cout << "&&&&&&&&&&&&&&&"; c(15);  cout << " " << endl; \\ with endl
	cout << "      " << "    "; c(hc); cout << "&&&&&&&&&&&&&&&"; c(15);  cout << " ";

}

void PrintMap() {

	static const int mapHeight = MAX_VERTICAL_CHARACTERS - MAX_PORT_MENU_LINES;
	static const int mapWidth = MAX_HORIZONTAL_CHARACTERS;

	static char mapMatrix[mapHeight][mapWidth] = {};

	for (int line = 1; line <= mapHeight; line++) {


		for (int column = 1; column <= mapWidth; column++) {

			if (line == 1 || line == mapHeight) {
				mapMatrix[line][column] = '*';
			}

			if (column == 1 || column == mapWidth) {
				mapMatrix[line][column] = '*';
			}
			cout << mapMatrix[line][column];
		}
		// Line break at the end of each line
		cout << endl;
	}

}

void PrintEmptyLines(int numberOfLines) {
	for (int i = 0; i < numberOfLines; i++) {
		cout << "                                                                                                                      \n";
	}
}


void PrintCaptainBoxes(int captainSelection) {

	int color0 = 15;
	int color1 = 15;
	int color2 = 15;
	int color3 = 15;

	//// horizontal and vertical frame characters
	//char ch = '=';
	//char vc = '|';

	switch (captainSelection)
	{
	case 0:
		color0 = SELECTION_COLOR;
		break;
	case 1:
		color1 = SELECTION_COLOR;
		break;
	case 2:
		color2 = SELECTION_COLOR;
		break;
	case 3:
		color3 = SELECTION_COLOR;
		break;
	default:
		break;
	}

	c(color0); cout << " " << "________________________________________" << " "; c(color1); cout << "________________________________________" << " "; c(color2); cout << "________________________________________" << " "; c(color3); cout << "________________________________________" << " " << endl;
	c(color0); cout << " " << "| ____________________________________ |" << " "; c(color1); cout << "| ____________________________________ |" << " "; c(color2); cout << "| ____________________________________ |" << " "; c(color3); cout << "| ____________________________________ |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |         Luuk de Ruyter           | |" << " "; c(color1); cout << "| |          Thomas Nelson           | |" << " "; c(color2); cout << "| |    Jean-Baptiste de Vermandois   | |" << " "; c(color3); cout << "| |         Fernando de Bazan        | |" << " " << endl;
	c(color0); cout << " " << "| |              "; PrintFlag(0); c(color0); cout << "                 | |" << " "; c(color1); cout << "| |               "; PrintFlag(1); c(color1); cout << "                | |" << " "; c(color2); cout << "| |               "; PrintFlag(2); c(color2); cout << "                | |" << " "; c(color3); cout << "| |               "; PrintFlag(3); c(color3); cout << "                | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |                                  | |" << " "; c(color1); cout << "| |                                  | |" << " "; c(color2); cout << "| |                                  | |" << " "; c(color3); cout << "| |                                  | |" << " " << endl;
	c(color0); cout << " " << "| |__________________________________| |" << " "; c(color1); cout << "| |__________________________________| |" << " "; c(color2); cout << "| |__________________________________| |" << " "; c(color3); cout << "| |__________________________________| |" << " " << endl;
	c(color0); cout << " " << "________________________________________" << " "; c(color1); cout << "|______________________________________|" << " "; c(color2); cout << "|______________________________________|" << " "; c(color3); cout << "|______________________________________|" << " " << endl;

}

void PrintPortMenuHeader(std::string headerText) {
	
	MoveCursorTo(0, HEADER_START);
	cout << endl;
	cout << "    " << headerText;
	cout << "                                                                            \n";
	cout << endl;
	cout << "================================================================================" << endl;
}

//void PrintWavyMessage(string text, int margin, int speed) {
//	// Create animation for bottom part
//	// Will keep playing until intro is pressed.
//
//	int colors[6] = { 1, 9, 3, 11, 7, 15 };
//
//	while (true) {
//		for (int i = 0; i < 6; i++) {
//			MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - 7);
//			IncreaseMargin(margin); c(colors[i]); cout << text; c(15); cout << endl;
//			Sleep(speed);
//			if (GetAsyncKeyState(VK_RETURN || VK_ESCAPE) != 0) {
//				return;
//			}
//		}
//		for (int i = 5; i >= 0; i--) {
//			MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - 7);
//			IncreaseMargin(margin); c(colors[i]); cout << text; c(15); cout << endl;
//			Sleep(speed);
//			if (GetAsyncKeyState(VK_RETURN || VK_ESCAPE) != 0) {
//				return;
//			}
//		}
//	}
//}


	void PrintWelcomeScreen() {

		int colors[6] = { 1, 9, 3, 11, 7, 15 };

		PrintEmptyLines(11);
		cout << "                                                                                          x000000000v                                                               " << endl;
		cout << "                                                                                       x000000000000000C                                                             " << endl;
		cout << "      voC      xxxv                                                                   800000000000000000C                                                            " << endl;
		cout << "       00000000000000C                                                 0C             0000000000000000080              8C                                            " << endl;
		cout << "        cCI   vcc  O00C                                                00C            0000000000000000000             00C                                            " << endl;
		cout << "            0000C  i000                                                0000           88     I0000     0C           v000C                                            " << endl;
		cout << "            i000    000c                                               i0000c         v0v  vo0C 00v c x0C          80000   x0oo0oC  0000oo             00            " << endl;
		cout << "            i000    000                                                  00000c        000000C 8 x000000C        x00000    cI000Cc  i000C             800            " << endl;
		cout << "            i000C   000  xvv  xxvvxc       xc c0vx00xx xooooo   o000C     000000        0c 000000000 x0        800000C       000     000C             800            " << endl;
		cout << "            i0000o0000c  I0C  c00cC80C     00    0C  I 80  8  I0C c8C      i000000C     i0C 08IC0  VV0C     v0000000C        000     000    vo000x    800            " << endl;
		cout << "            i0000000     i0    00  i0C    I00    00    I0     800           c80000000c   0000000000000    x0000000           00000000000   x0C  cV0C  00C            " << endl;
		cout << "            v000C         0    00vo00     0 0C   00    80o0C  i0000v           I0000000x  00000000000  x00000000             800ccccc000   00    v00  800            " << endl;
		cout << "            i000C         0    i0 800     0000   80    i0      c00000             800080000c         00000000C              v00C     800   00    v00  800            " << endl;
		cout << "             000C        i0C   00  I00   IC i0   80    I0      v cI00C              C800080000v vo0000I000C                 x000     000c  80V   00C  800            " << endl;
		cout << "            v0000c      v000C x000  c00  00 800  00C  I00000C 80C  i0C                   000vo000CV0000C                   0000000 8000000  800000    i00            " << endl;
		cout << "           v00000C                    I000C                   0C   i0C                 vx000CIo000Cx00xcc                  ccccc c c  cccc     cc                    " << endl;
		cout << "                                                              i0  x0C             xo80CIx000c     I000xCIV0xocc                                       00             " << endl;
		cout << "                                                               cI0c           0000000O0                 x0I000000v                                    00             " << endl;
		cout << "                                                                        8000O00000C   i0                0    8000008000C                                             " << endl;
		cout << "                                                                        8000Cc        8C                0C        v8000                                              " << endl;
		cout << "                                                                             80v   xo0C                 c80vc cxo0C                                                  " << endl;
		cout << "                                                                                 Cc                         cCc                                                      " << endl;
		PrintEmptyLines(4);



		// Create animation for bottom part
		// Will keep playing until intro is pressed.
		while (true) {
			for (int i = 0; i < 6; i++) {
				MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - 7);
				cout << "                                                                                          "; c(colors[i]); cout << "PRESS INTRO"; c(15); cout << "                                                                 \n";
				PrintEmptyLines(5);
				cout << "    "; c(8); cout << "A game by Nicolas de Amador"; c(15); cout << "\n";
				Sleep(100);
				if (GetAsyncKeyState(VK_RETURN) != 0) {
					return;
				}
			}
			for (int i = 5; i >= 0; i--) {
				MoveCursorTo(0, MAX_VERTICAL_CHARACTERS - 7);
				cout << "                                                                                          "; c(colors[i]); cout << "PRESS INTRO"; c(15); cout << "                                                                 \n";
				PrintEmptyLines(5);
				cout << "    "; c(8); cout << "A game by Nicolas de Amador"; c(15); cout << "\n";
				Sleep(100);
				if (GetAsyncKeyState(VK_RETURN) != 0) {
					return;
				}
			}

			// Stay in Welcome screen until intro is pressed:
			//do {
			//	// Do if intro key is pressed. It prevents accidental action triggers when returning from other menus.
			//} while (GetAsyncKeyState(VK_RETURN) != 0);

		}
	}


	void PrintMainMenuBanner(int margin) {

		IncreaseMargin(margin); cout << "      voC      xxxv                                                                                                 " << endl;
		IncreaseMargin(margin); cout << "       00000000000000C                                                                                              " << endl;
		IncreaseMargin(margin); cout << "        cCI   vcc  O00C                                                                                             " << endl;
		IncreaseMargin(margin); cout << "            0000C  i000                                                                                             " << endl;
		IncreaseMargin(margin); cout << "            i000    000c                                                  x0oo0oC  0000oo             00            " << endl;
		IncreaseMargin(margin); cout << "            i000    000                                                   cI000Cc  i000C             800            " << endl;
		IncreaseMargin(margin); cout << "            i000C   000  xvv  xxvvxc       xc c0vx00xx xooooo   o000C       000     000C             800            " << endl;
		IncreaseMargin(margin); cout << "            i0000o0000c  I0C  c00cC80C     00    0C  I 80  8  I0C c8C       000     000    vo000x    800            " << endl;
		IncreaseMargin(margin); cout << "            i0000000     i0    00  i0C    I00    00    I0     800           00000000000   x0C  cV0C  00C            " << endl;
		IncreaseMargin(margin); cout << "            v000C         0    00vo00     0 0C   00    80o0C  i0000v        800ccccc000   00    v00  800            " << endl;
		IncreaseMargin(margin); cout << "            i000C         0    i0 800     0000   80    i0      c00000      v00C     800   00    v00  800            " << endl;
		IncreaseMargin(margin); cout << "             000C        i0C   00  I00   IC i0   80    I0      v cI00C     x000     000c  80V   00C  800            " << endl;
		IncreaseMargin(margin); cout << "            v0000c      v000C x000  c00  00 800  00C  I00000C 80C  i0C    0000000 8000000  800000    i00            " << endl;
		IncreaseMargin(margin); cout << "           v00000C                    I000C                   0C   i0C    ccccc c c  cccc     cc                    " << endl;
		IncreaseMargin(margin); cout << "                                                              i0  x0C                                 00            " << endl;
		IncreaseMargin(margin); cout << "           "; c(8); cout << "A game by Nicolas de Amador"; c(15); cout << "                         cI0c                                                 " << endl;

	}




