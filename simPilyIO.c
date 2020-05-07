/**
 *Code for the functions defined in simPilyIO.h
 *
 *@Author: Cameron Myron
 *@Email: cmm8535@g.rit.edu
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define GPIO_PATH "/sys/class/gpio"
#define PATH_BUFFER 100

///Initalizes the given pin for use
int addPin(short pin, char* direction){
  char path[PATH_BUFFER];
  snprintf(path, PATH_BUFFER, "%s/export", GPIO_PATH);
  FILE* f;
  if(!(f=fopen(path, "w"))){
    fprintf(stderr, "Couldn't Open %s\n", path);
    return 1;
  }
  fprintf(f, "%hi", pin);
  fclose(f);
  snprintf(path, PATH_BUFFER, "%s/gpio%hi/direction", GPIO_PATH, pin);
  if(!(f=fopen(path, "w"))){
    fprintf(stderr, "Couldn't Open %s\n", path);
    return 1;
  }
  fprintf(f, "%s", direction);
  fclose(f);
  return 0;
}

///Un-initalizes the given pin
int removePin(short pin){
  (void)pin;
  return 0;
}

///Sets the given gpio pin to the given value
void setPin(short pin, short value){
  char path[PATH_BUFFER];
  FILE* f;
  snprintf(path, PATH_BUFFER, "%s/gpio%hi/direction", GPIO_PATH, pin);
  if(!(f=fopen(path, "r"))){
    fprintf(stderr, "Couldn't Open %s\n", path);
    return;
  }
  char dir[3];
  fscanf(f, "%3s", dir);
  fclose(f);
  if(strncmp(dir, "out", 3)){
    fprintf(stderr, "This Is An Input Pin\n");
    return;
  }
  snprintf(path, PATH_BUFFER, "%s/gpio%hi/value", GPIO_PATH, pin);
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
  snprintf(path, PATH_BUFFER, "%s/gpio%hi/value", GPIO_PATH, pin);
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
