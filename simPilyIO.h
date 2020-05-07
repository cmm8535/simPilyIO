#ifndef SIMPILYIO_H
#define SIMPILYIO_H
/**
 *This is a simple gpio library for the RaspberryPi (specifically model 4B) for C.
 *This will be an on and off (no pun intended) project for me with the main goal
 *being that I have something usable to control my RaspberryPi with C code and that
 *I can learn more about making useful libraries. Might be buggy, might be unsecure,
 *who knows and we will see. Any feedback appreciated.
 *
 *@Author: Cameron Myron
 *@Email: cmm8535@g.rit.edu
 */

/**
 *Sets the value of a given gpio pin to the given value
 *
 *ERRORS:
 *  -If a value that is not a 1 or 0 is given it will be treated as a 1
 *  -If the given pin is uninitialized (or invalid), nothing happens
 *
 *@Param pin: GPIO number
 *@Param value: 1 to set the pin "high", 0 to set the pin "low"
 */
void setPin(short pin, short value);

/**
 *Gets the value of a given gpio pin
 *
 *ERRORS:
 *  -If the given pin is uninitialized (or invalid), -1 is returned
 *  -If the pin somehow doesn't have a value (which I think is impossible, but
 *  need this part to suppress errors), -1 is returned
 *
 *@Param pin: GPIO number
 *@Return: Value of the given gpio pin (1 if "high", 0 if "low")
 */
short getPin(short pin);

#endif //SIMPILYIO_H
