#include "Serial.h"
#include "define.h"
#include "output.h"
#include "device.h"


boolean executeCommand(Command comm);


int* cont_input;

void setup() {
  // put your setupcode here, to run once
  Serial.begin(57600);
  initializeInputOutput();
  cont_input = (int*)malloc(sizeof(int)*16);
  initializeInputData(cont_input);
  Serial.println("Finished to initialize Controller");
}


void loop() {
  /* 1. read Serial Command */
  Command read_C = readCommand();
  if(read_C != 0){
    executeCommand(read_C); 
  }

  read_C = 0;
}

boolean executeCommand(Command comm){
  switch(comm){
    case HELLO : 
      sendResultToAndroidOfConnectionRequest();
      connectToAndroid();
      return true; 

    case BYE : 
      disconnectToAndroid();
      sendResultToAndroidOfDisconnectionRequest();
      return true;

    case GET : 
      getControllerData(cont_input);
      sendInputDataToAndroid(cont_input);
      return true;  

    default : 
      return false; 
  }
}
