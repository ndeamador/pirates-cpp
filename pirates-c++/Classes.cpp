#include "GlobalSetup.h"
#include "Classes.h"
#include "Graphics.h" // to format operator overloading output.
#include <string>
#include <iomanip> // to format table-like output in operator overloading
#include <iostream> 



using namespace std;


// PLAYER
// =============================================================================================


// Constructor
CPlayer::CPlayer(string name, int playedNation, int playedWealthPerTurn, bool playerVictorious) {

	// Store name only if it has fewer than 30 characters. Otherwise keep the default value.
	if (name.length() <= 30) {
		this->name = name;
	}
	this->name = playedNation;
	this->name = playedWealthPerTurn;
	this->name = playerVictorious;

}

// Getters:
string CPlayer::getName() { return this->name; }
int CPlayer::getPlayedNation() { return this->playedNation; }
int CPlayer::getPlayedWealthPerTurn() { return this->playedWealthPerTurn; }
bool CPlayer::getGameOutcome() { return this->playerVictorious; }


// Setters:
void CPlayer::setName(string name) {
	this->name = name;
}
void CPlayer::setPlayedNation(int playedNation) {
	this->playedNation = playedNation;
}
void CPlayer::setPlayedWealthPerTurn(int playedWealthPerTurn) {
	this->playedWealthPerTurn = playedWealthPerTurn;
}
void CPlayer::setGameOutcome(bool playerVictorious) {
	this->playerVictorious = playerVictorious;
}

// Operator Overloading implementation
ostream& operator<< (ostream& out, CPlayer& param) {

	// Because we have made the operator a friend of the class, we don't need to use a getter and we can access the private attributes directly.

	PrintFlag(param.playedNation);

	out << " " << setw(32) << left << param.name << setw(32) << left << param.playedWealthPerTurn;

	switch (param.playerVictorious)
	{
	case true:
		c(2);
		out << setw(32) << left << "Victorious" << endl;
		break;
	case false:
		c(4);
		out << setw(32) << left << "Defeated" << endl;
		break;
	}
	c(15);


	return out;
}



// PORT
// =============================================================================================

void CPort::setName(string name) {
	this->name = name;
}


string CPort::getName() {
	return this->name;
}

int CPort::getGoodAmount(int goodId) {
	return this->goods[goodId];
}

void CPort::setGoodAmount(int goodId, int newValue) {
	this->goods[goodId] = newValue;
}

// CPort constructor
CPort::CPort(string name) {
	setName(name);

	////randomize goods available in port:
	for (int i = 0; i < GOOD_TYPES; i++) {
		// each good will have a random amount between 0 and 12
		this->goods[i] = rand() % MAX_GOOD_AMOUNT;
	}
}


// SHIP
// =============================================================================================

// Default constructor for CShip class.
CShip::CShip(int doublons, int cannons, int hullPoints) {
	this->doublons = doublons;
	this->cannons = cannons;
	this->hullPoints = hullPoints;
}

// Default destructor
CShip::~CShip() {}



// Getters
int CShip::getGoodAmount(int goodId) {
	return this->cargo[goodId];
}

int CShip::getDoublonsAmount() {
	return this->doublons;
}


int CShip::getCannons() {
	return this->cannons;
}

int CShip::getHullPoints() {
	return this->hullPoints;
}

// Setters

void CShip::setCannons(int cannons) {
	this->cannons = cannons;
}

void CShip::setHullPoints(int hullPoints) {
	this->hullPoints = hullPoints;
}

void CShip::setDoublonsAmount(int doublons) {
	this->doublons = doublons;
}

void CShip::setGoodAmount(int goodId, int newValue) {
	this->cargo[goodId] = newValue;
}

void CShip::setAllGoodsTo(int newValue) {
	for (int i = 0; i < GOOD_TYPES; i++) {
		this->cargo[i] = newValue;
	}
}




// VICTORY CONDITIONS
// =============================================================================================


CVictoryCondition::CVictoryCondition(int doubloons, int maxTurns,  bool playerMustSurvive) {

	this->doubloons = doubloons;
	this->maxTurns = maxTurns;
	this->playerMustSurvive = playerMustSurvive;

}
	
	// Getters:
	int CVictoryCondition::getDoubloons() { return this->doubloons; }
	int CVictoryCondition::getMaxTurns() { return this->maxTurns; }
	bool CVictoryCondition::getPlayerMustSurvive() { return this->playerMustSurvive; }

	// Setters/Mutators:
	void CVictoryCondition::setDoubloons(int doubloons) {
		this->doubloons = doubloons;
	}
	void CVictoryCondition::setMaxTurns(int maxTurns) {
		this->maxTurns = maxTurns;
	}
	void CVictoryCondition::setPlayerMustSurvive(bool playerMustSurvive) {
		this->playerMustSurvive = playerMustSurvive;
	}
	void CVictoryCondition::randomizeVictoryConditions() {
		 
		int tempValues = 0;

		// SET DOUBLONS TO WIN
		// get a random number between 500 and 1000.
		tempValues = rand() % (1000 - 500) + 1;

		// round to nearest 100th.
		if (tempValues % 100 != 0) {
			tempValues -= tempValues % 100;
		}
		this->setDoubloons(tempValues);

		// SET MAX NUMBER OF TURNS			
		this->setMaxTurns(rand() % (10 - 20) + 1);

		// SET PLAYER CAN'T BE SUNK CONDITION
		// there is a ~33% chance that the player will lose if his hullpoints get to 10.
		tempValues = rand() % 100 + 1;
		if (tempValues < 33) {
			this->setPlayerMustSurvive(true);
		}		
	}