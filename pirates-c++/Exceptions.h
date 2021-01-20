#pragma once

#include <exception>

using namespace std;


class arrayLoadException : public exception {

	// Reimplementation of the what() method to learn the cause of an exception.
	// Virtual so that it can be overriden
	// const throw() is an exception specification confirm that this function will never return an exception.
	virtual const char* what() const throw() {

		// this message will be displayed when customException.what() is called, instead of the default exception class message.
		return "Failed to load data into array.";
	}
};
