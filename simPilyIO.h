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

///This part is for an idea to speed up functions to only access files
///When neccessary (like setting a value that it doesn't have already)
struct pin{
  short num:5;
  short val:1;
  short dir:1;
};

typedef struct pin* pin_t;

/**
 *Initializes the given pin for use (set to 0 by default)
 *
 *ERRORS:
 *  -Invalid GPIO number
 *  -Direction is invalid
 *  -Program doesn't have root priveledges (can't access a needed path)
 *
 *@Param pin: GPIO number
 *@Param direction: String indicating the pin's direction ("in" or "out")
 *@Return: 0 if successful, 1 otherwise
 */
int addPin(short pin, char* direction);

/**
 *Un-initializes the given pin when not needed anymore
 *
 *ERRORS:
 *  -If the given pin is uninitialized (or invalid)
 *  -Program doesn't have root priveledges (can't access a needed path)
 *
 *@Param pin: GPIO number
 *@Return: 0 if successful, 1 otherwise
 */
int removePin(short pin);

/**
 *Sets the value of a given gpio pin to the given value
 *
 *ERRORS:
 *  -If a value that is not a 1 or 0 is given it will be treated as a 1
 *  -If the given pin is uninitialized (or invalid), nothing happens
 *  -The given pin has a direction of "in"
 *  -Program doesn't have root priveledges (can't access a needed path)
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
 *  -Program doesn't have root privelegdes (can't access a needed path)
 *
 *@Param pin: GPIO number
 *@Return: Value of the given gpio pin (1 if "high", 0 if "low")
 */
short getPin(short pin);

#endif //SIMPILYIO_H
