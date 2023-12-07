/* Analogin.cpp
 *
 * Class implementation file by David Melanson
 * for IoT Homework 8 Problem 2
 *
 */


#include <iostream>
#include <sstream>
#include <fstream>
#include "AnalogIn.h"

using namespace std;

#define ADC_PATH "/sys/bus/iio/devices/iio:device0/in_voltage"

AnalogIn::AnalogIn(){}

AnalogIn::AnalogIn(unsigned int n){
	this->number = n;
}

 void AnalogIn::setNumber(unsigned int n){
	this->number = n;
}

 int AnalogIn::readAdcSample(){
	stringstream ss;
	ss << ADC_PATH << this->number << "_raw";
	fstream fs;
	fs.open(ss.str().c_str(), fstream::in);
	fs >> number;
	fs.close();
	return number;
}

AnalogIn::~AnalogIn(){}
