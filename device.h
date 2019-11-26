#ifndef DEVICE_H_
#define DEVICE_H_

#include "arduino.h"

#define MUX_INPUT1 A0
#define MUX_INPUT2 A1
#define MUX_INPUT3 A2
#define MUX_OUTPUT A7

#define BUZZER 3

#define POWER_INPUT 5

#define D1  2
#define D2  4
#define D3  6
#define D4  A3
#define D5  8
#define D6  7

#define TREAM_SW  A6

#define INIT 13

void initializeInputOutput();
void connectedAndroid(bool* connected);
void getControllerData(int* cont_input);
void initializeInputData(int* cont_input);
void getThrottleData(int* roll, int* pitch, int* yaw, int* throttle, int* left, int* right);
void getTreamSwitchData(int* roll_t, int* pitch_t, int* yaw_t);
void getDigitalSwitchData(int* power, int* d1, int* d2, int* d3, int* d4, int* d5, int* d6);
boolean connectToAndroid();
boolean disconnectToAndroid();

#endif
