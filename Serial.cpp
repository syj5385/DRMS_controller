
#include "Serial.h"
#include <arduino.h>
#include <string.h>

void initializeSerial(){
  Serial.begin(9600);
  Serial.println("Initialize Serial");
}

Command readCommand(){
  char temp; 
  String commandString ="";
//  while((temp = Serial.read()) != '#'){
//    delayMicroseconds(500);
//  }
  if(Serial.available() >= 5){
    temp = (char)Serial.read();
    if(temp == '#'){
      while((temp = Serial.read()) != '\n'){
        commandString += temp; 
        delayMicroseconds(500);
      }
      if(commandString.equals("hello")){        
        return HELLO;
      }
      if(commandString.equals("bye")){        
        return BYE;
      }
      if(commandString.equals("get")){        
        return GET;
      }
      return 0; 
    }
  }
  return 0; 
}

void sendResultToAndroidOfConnectionRequest(){
  Serial.print("HELLO");  
}

void sendResultToAndroidOfDisconnectionRequest(){
  Serial.print("BYE");
 
}
void sendInputDataToAndroid(int* cont_input){
  // Cont_input[16] = {1500, 1500, 1500, 1000, 1000, 1000 , 1000, 1000, 1000, 1000, 1000, 1000,  1000 , 127,  127, 127};
                  //  R   /  P  /  Y / thro/ power/ D2  / D4  / D5  / D6  / D7  / D8  /  left / right /R  /  P  / Y 
  uint8_t* serialdata = (uint8_t*)malloc(sizeof(uint8_t)*22);

  // Throttle
  serialdata[0] = cont_input[0] % 256; 
  serialdata[1] = cont_input[0] / 256;
  serialdata[2] = cont_input[1] % 256; 
  serialdata[3] = cont_input[1] / 256;
  serialdata[4] = cont_input[2] % 256; 
  serialdata[5] = cont_input[2] / 256;
  serialdata[6] = cont_input[3] % 256; 
  serialdata[7] = cont_input[3] / 256;

  //DigitalSwitch
  if(cont_input[4] == 2000){
    serialdata[8] = 200;
    cont_input[4] = 1000;
  }
  else
    serialdata[8] = 100;

  if(cont_input[5] == 2000){
    serialdata[9] = 200;
    cont_input[5] = 1000;
  }
  else
    serialdata[9] = 100;

  if(cont_input[6] == 2000){
    serialdata[10] = 200;
    cont_input[6] = 1000;
  }
  else
    serialdata[10] = 100;

  if(cont_input[7] == 2000){
    serialdata[11] = 200;
    cont_input[7] = 1000;
  }
  else
    serialdata[11] = 100;

  if(cont_input[8] == 2000){
    serialdata[12] = 200;
    cont_input[8] = 1000;
  }
  else
    serialdata[12] = 100;

  if(cont_input[9] == 2000){
    serialdata[13] = 200;
    cont_input[9] = 1000;
  }
  else
    serialdata[13] = 100;

  if(cont_input[10] == 2000){
    serialdata[14] = 200;
    cont_input[10] = 1000;
  }
  else
    serialdata[14] = 100;

  //analogResistor
  serialdata[15] = cont_input[11] % 255;
  serialdata[16] = cont_input[11] / 255;
  serialdata[17] = cont_input[12] % 255;
  serialdata[18] = cont_input[12] / 255;

  //Tream
  if(cont_input[13] == 2000){
    serialdata[19] = 200;
  }
  else if(cont_input[13] == 1000){
    serialdata[19] = 100;
  }
  else if(cont_input[13] == 1500){
    serialdata[19] = 150;
  }

  if(cont_input[14] == 2000){
    serialdata[20] = 200;
  }
  else if(cont_input[14] == 1000){
    serialdata[20] = 100;
  }
  else if(cont_input[14] == 1500){
    serialdata[20] = 150;
  }

  if(cont_input[15] == 2000){
    serialdata[21] = 200;
  }
  else if(cont_input[15] == 1000){
    serialdata[21] = 100;
  }
  else if(cont_input[15] == 1500){
    serialdata[21] = 150;
  }
  for(int i = 13 ; i<16; i++){
    if(cont_input[i] != 1500){
      cont_input[i] = 1500; 
    }
  }
  
  // Send data 
  Serial.write('#');
  delayMicroseconds(500);
  Serial.write('c');
  delayMicroseconds(500);
  Serial.write('o');
  delayMicroseconds(500);
  Serial.write('n');
  delayMicroseconds(500);
  Serial.write('t');
  delayMicroseconds(500);

  uint8_t checksum = 0;
  for(int i=0; i<22; i++){
    checksum ^= serialdata[i];
  }

  for(int i=0; i<22 ;i++){
    Serial.write(serialdata[i]);
    delayMicroseconds(500);
  }
  Serial.write(checksum);
  delay(1);
  free(serialdata);
  
}
