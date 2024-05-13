#include <cstdlib>
#include <string>
#include <iostream>

const int PIN_ONE = 26;
const int PIN_TWO = 20;
const int PIN_THREE = 21;

void initPin(int pin);
void turnOnPin(int pin);
void turnOffPin(int pin);
void executeCommand(const std::string& cmd);

