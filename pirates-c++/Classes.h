#pragma once

#include "GlobalSetup.h"
#include <string>

using namespace std;

#ifndef _CLASSES_H
#define _CLASSES_H


class CShip {
private:
	int hullPoints;
	int cannons;
	int cargo[GOOD_TYPES] = { 0 };
	int doublons;
public:
	// Constructor
	CShip(int = 300, int = 10, int = 100);
	
	// Destructor
	~CShip();

	// Getters:
	int getGoodAmount(int);
	int getCannons();
	int getHullPoints();
	int getDoublonsAmount();


	// Setters:
	void setCannons(int);
	void setHullPoints(int);
	void setDoublonsAmount(int);
	void setGoodAmount(int, int);
	void setAllGoodsTo(int);

};

class CPort {
private:
	string name;
	int goods[GOOD_TYPES] = {};
public:
	// Constructor
	CPort(string);

	// Getters:
	string getName();
	int getGoodAmount(int);

	// Setters/Mutators:
	void setName(string);
	void setGoodAmount(int, int);

};

//class CCaptain {
//private:
//	int id;
//public:
//};

class CVictoryCondition {
private:
	int doubloons;
	int maxTurns;
	bool playerMustSurvive;

public:
	// Constructor
	CVictoryCondition(int = 0, int = 0, bool = false);

	// Getters:
	int getDoubloons();
	int getMaxTurns();
	bool getPlayerMustSurvive();

	// Setters/Mutators:
	void setDoubloons(int);
	void setMaxTurns(int);
	void setPlayerMustSurvive(bool);
	void randomizeVictoryConditions();
};

// Players don't need to be unique and are only necessary to display records, so no id is needed.
class CPlayer {
private:
	string name;
	int playedNation;
	int playedWealthPerTurn;
	bool playerVictorious;

public:
	// Constructor
	CPlayer(string = "", int = 0, int = 0, bool = false);

	// Getters:
	string getName();
	int getPlayedNation();
	int getPlayedWealthPerTurn();
	bool getGameOutcome();

	// Setters/Mutators:
	void setName(string);
	void setPlayedNation(int);
	void setPlayedWealthPerTurn(int);
	void setGameOutcome(bool);

	// Operator overloading:
	friend ostream& operator <<(ostream& out, CPlayer& param);
};


#endif