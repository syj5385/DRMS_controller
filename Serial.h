#ifndef SERIAL_H_
#define SERIAL_H_

#include "define.h"

void initializeSerial();
Command readCommand();
void sendResultToAndroidOfConnectionRequest();
void sendResultToAndroidOfDisconnectionRequest();
void sendInputDataToAndroid(int* cont_input);

#endif
