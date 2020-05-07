/**
 *Code for the functions defined in simPilyIO.h
 *
 *@Author: Cameron Myron
 *@Email: cmm8535@g.rit.edu
 */

#include <stdio.h>
#include <unistd.h>

#define GPIO_PATH "/sys/class/gpio"
#define PATH_BUFFER 100

///Sets the given gpio pin to the given value
void setPin(short pin, short value){
  char path[PATH_BUFFER];
  sprintf(path, "%s/gpio%hi/value", GPIO_PATH, pin);
  FILE* f;
  if(!(f=fopen(path, "w"))){
    fprintf(stderr, "Couldn't Open %s\n", path);
    return;
  }
  fprintf(f, "%hi", value);
  fclose(f);
}

///Gets the value of the given gpio pin
short getPin(short pin){
  char path[PATH_BUFFER];
  sprintf(path, "%s/gpio%hi/value", GPIO_PATH, pin);
  FILE* f;
  if(!(f=fopen(path, "r"))){
    fprintf(stderr, "Couldn't Open %s\n", path);
    return -1;
  }
  short rtn = -1;
  fscanf(f, "%hi", &rtn);
  fclose(f);
  return rtn;
}