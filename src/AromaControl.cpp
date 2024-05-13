/**
 * @file AromaControl.cpp
 * @brief Functions to turn difusers on or off.
 * @author Bruce Scott
 */

#include "../include/AromaControl.h"

/**
 * @brief Initializes a pin
 * @param pin The pin to initialize
*/
void initPin(int pin)
{
    // Command to init a pin
    const std::string cmd = "raspi-gpio set " + std::to_string(pin) + " op";
    executeCommand(cmd);

    // Turns the pin off, because default state is on
    turnOffPin(pin);
}

/**
 * @brief turns a given pin on
 * @param pin The pin to turn on
*/
void turnOnPin(int pin)
{
    // Calls terminal command to turn pin on
    const std::string cmd = "raspi-gpio set " + std::to_string(pin) + " dh";
    executeCommand(cmd);
}

/**
 * @brief turns a given pin off
 * @param pin the pin to turn off
*/
void turnOffPin(int pin)
{

    // Calls terminal command to turn pin off
    const std::string cmd = "raspi-gpio set " + std::to_string(pin) + " dl";
    executeCommand(cmd);
}

/**
 * @brief executes a given command in the system terminal
 * @param cmd the command to execute
*/
void executeCommand(const std::string& cmd)
{

    // Converts the given string to a c-like string to execute, then calls it from system
    const char* cString = cmd.c_str();
    int exitCode = system(cString);
}