/**
 *Code for the functions defined in simPilyIO.h
 *
 *@Author: Cameron Myron
 *@Email: cmm8535@g.rit.edu
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "simPilyIO.h"

#define GPIO_PATH "/sys/class/gpio"
#define EXPORT_PATH "/sys/class/gpio/export"
#define UNEXPORT_PATH "/sys/class/gpio/unexport"
#define PATH_BUFFER 100
#define GPIO_MIN 2
#define GPIO_MAX 27
#define PINS_LEN GPIO_MAX-GPIO_MIN+1

pin_t* pins[PINS_LEN];
FILE* export;
FILE* unexport;

///
void init(){
  if(!(export=fopen(EXPORT_PATH, "w"))){
    fprintf(stderr, "Couldn't Open %s\n", EXPORT_PATH);
    exit(1);
  }
  if(!(unexport=fopen(UNEXPORT_PATH, "w"))){
    fprintf(stderr, "Couldn't Open %s\n", UNEXPORT_PATH);
    exit(1);
  }
}

///
void uninit(){
  fclose(export);
  int i;
  for(i = 0; i < PINS_LEN; i++)
    if(pins[i]){
      fclose(pins[i]->dir_path);
      fclose(pins[i]->val_path);
      fprintf(unexport, "%hi", i);
      fflush(unexport);
      free(pins[i]);
    }
  fclose(unexport);
}

///Initalizes the given pin for use
int addPin(short pin, char* direction){
  char path[PATH_BUFFER];
  if(!export){
    fprintf(stderr, "Didn't Initalize The Program\n");
    return 1;
  }
  fprintf(export, "%hi", pin);
  fflush(export);
  snprintf(path, PATH_BUFFER, "%s/gpio%hi/direction", GPIO_PATH, pin);
  pin_t* new = malloc(sizeof(pin_t));
  if(!(new->dir_path=fopen(path, "w"))){
    fprintf(stderr, "Couldn't Open %s\n", path);
    free(new);
    return 1;
  }
  snprintf(path, PATH_BUFFER, "%s/gpio%hi/value", GPIO_PATH, pin);
  if(!(new->val_path=fopen(path, "w"))){
    fprintf(stderr, "Couldn't Open %s\n", path);
    free(new);
    return 1;
  }
  if(fprintf(new->dir_path, "%s", direction)<0){
    fprintf(stderr, "Invalid Direction %s\n", direction);
    free(new);
    return 1;
  }
  fflush(new->dir_path);
  new->num = pin;
  new->val = 0;
  new->dir = strncmp(direction, "out", 3) ? 0 : 1;
  pins[pin] = new;
  return 0;
}

///Un-initalizes the given pin
int removePin(short pin){
  (void)pin;
  return 0;
}

///Sets the given gpio pin to the given value
void setPinVal(short pin, short value){
  if(!pins[pin]){
    fprintf(stderr, "This Pin Is Uninitialized\n");
    return;
  }
  if(!pins[pin]->dir){
    fprintf(stderr, "This Is An Input Pin\n");
    return;
  }
  if(pins[pin]->val!=(value ? 1 : 0)){
    fprintf(pins[pin]->val_path, "%hi", value);
    fflush(pins[pin]->val_path);
    pins[pin]->val = value ? 1 : 0;
  }
}

///Gets the value of the given gpio pin
short getPinVal(short pin){
  return pins[pin] ? pins[pin]->val : -1;
}
