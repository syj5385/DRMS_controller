
#include "device.h"
#include "output.h"
#include "Buzzer.h"
#include "EEPROM.h"

boolean connectToAndroid(){
  connectLED(true);
}

boolean disconnectToAndroid(){
  connectLED(false);
}
void initializeInputOutput(){
  //Multiplexer input
  pinMode(MUX_INPUT1,OUTPUT);
  pinMode(MUX_INPUT2,OUTPUT);
  pinMode(MUX_INPUT3,OUTPUT);

  // Common Input / Output
  pinMode(BUZZER,OUTPUT);
  pinMode(POWER_INPUT,OUTPUT);

  // Customize Input
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);

  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,HIGH);
  digitalWrite(D5,HIGH);
  digitalWrite(D6,HIGH);
  
  digitalWrite(POWER_INPUT,HIGH);
}

void connectedAndroid(bool* connected){
  if(*connected == true){
    digitalWrite(INIT,HIGH);
    delay(1);
  }
  else{
    digitalWrite(INIT,LOW);
    delay(1);
  }
}

void initializeInputData(int* cont_input){
  cont_input[0] = 1500;
  cont_input[1] = 1500;
  cont_input[2] = 1500;
  cont_input[3] = 1000;

  cont_input[4]   = 1000;
  cont_input[5]   = 1000;
  cont_input[6]   = 1000;
  cont_input[7]   = 1000;
  cont_input[8]   = 1000;
  cont_input[9]   = 1000;
  cont_input[10]  = 1000;

  cont_input[11]  = 1000;
  cont_input[12]  = 1000;

  cont_input[13]  = 1500;
  cont_input[14]  = 1500;
  cont_input[15]  = 1500;
  
}



void getControllerData(int* cont_input){
  
// Cont_input[16] = {1500, 1500, 1500, 1000, 1000, 1000 , 1000, 1000, 1000, 1000, 1000, 1000,  1000 , 127,  127, 127};
                  //  R   /  P  /  Y / thro/ power/ D2  / D4  / D5  / D6  / D7  / D8  /  left / rightR  /  P  / Y 
  getThrottleData(cont_input, cont_input+1, cont_input+2,cont_input+3, cont_input+11, cont_input+12);
  getDigitalSwitchData(cont_input+4, cont_input+5, cont_input+6, cont_input+7, cont_input+8, cont_input+9,cont_input+10);
  getTreamSwitchData(cont_input+13, cont_input+14, cont_input+15);
}

void getTreamSwitchData(int* roll_t, int* pitch_t, int* yaw_t){
  int tream_temp = analogRead(TREAM_SW);
  if(tream_temp <= 2){
    *pitch_t = 2000;
    buzzer(2);
  }

  else if(tream_temp >2 && tream_temp <= 12){
    *pitch_t = 1000;
    buzzer(2);
  }

  else if(tream_temp > 17 && tream_temp <= 24){
    *roll_t = 2000;
    buzzer(2);
  }

  else if(tream_temp > 27 && tream_temp <= 34){
    *roll_t = 1000;
    buzzer(2);
  }

  else if(tream_temp > 55 && tream_temp <= 65){
    *yaw_t = 2000;
    buzzer(2);
  }

  else if(tream_temp > 85 && tream_temp <= 95){
    *yaw_t = 1000;
    buzzer(2);
  }
}

void getDigitalSwitchData(int* power, int* d1, int* d2, int* d3, int* d4, int* d5, int* d6){
  if(digitalRead(POWER_INPUT) == 0){
    buzzer(1);
    if(*power == 1000)
      *power = 2000;
    
  }
  
  if(digitalRead(D1) == 0){
    buzzer(1);
    if(*d1 == 1000)
      *d1 = 2000;
  }

  if(digitalRead(D2) == 0){
    buzzer(1);
    if(*d2 == 1000)
      *d2 = 2000;
  }

  if(digitalRead(D3) == 0){
    buzzer(1);
    if(*d3 == 1000)
      *d3 = 2000;
  }

  if(digitalRead(D4) == 0){
    buzzer(1);
    if(*d4 == 1000)
      *d4 = 2000;
  }

  if(digitalRead(D5) == 0){
    buzzer(1);
    if(*d5 == 1000)
      *d5 = 2000;
  }

  if(digitalRead(D6) == 0){
    buzzer(1);
    if(*d6 == 1000)
      *d6 = 2000;
  }


}

void getThrottleData(int* roll, int* pitch, int* yaw,int* throttle,int* left, int* right){
  // Roll
  digitalWrite(MUX_INPUT1,LOW); digitalWrite(MUX_INPUT2,LOW); digitalWrite(MUX_INPUT3,LOW);
  *roll = ((long)analogRead(MUX_OUTPUT) * 1000) / 1023 + 1000;
  if(*roll > 2000) *roll = 2000;
  if(*roll < 1000) *roll = 1000;

  //Pitch
  digitalWrite(MUX_INPUT1,HIGH); digitalWrite(MUX_INPUT2,LOW); digitalWrite(MUX_INPUT3,LOW);
  *pitch = ((long)analogRead(MUX_OUTPUT) * 1000) / 1023 + 1000;
  if(*pitch > 2000) *pitch = 2000;
  if(*pitch < 1000) *pitch = 1000;
  
  // Yaw
  digitalWrite(MUX_INPUT1,LOW); digitalWrite(MUX_INPUT2,HIGH); digitalWrite(MUX_INPUT3,LOW);
  *yaw = ((long)analogRead(MUX_OUTPUT) * 1000) / 1023 + 1000;
  if(*yaw > 2000) *yaw = 2000;
  if(*yaw < 1000) *yaw = 1000;

  // Throttle
  digitalWrite(MUX_INPUT1,HIGH); digitalWrite(MUX_INPUT2,HIGH); digitalWrite(MUX_INPUT3,LOW);
  *throttle = ((long)analogRead(MUX_OUTPUT) * 1000) / 1023 + 1000;
  if(*throttle > 2000) *throttle = 2000;
  if(*throttle < 1000) *throttle = 1000;

  // Left register
  digitalWrite(MUX_INPUT1,LOW); digitalWrite(MUX_INPUT2,LOW); digitalWrite(MUX_INPUT3,HIGH);
  *left = ((long)analogRead(MUX_OUTPUT) * 1000) / 1023 + 1000;
  if(*left > 2000) *left = 2000;
  if(*left < 1000) *left = 1000;

  // Left register
  digitalWrite(MUX_INPUT1,HIGH); digitalWrite(MUX_INPUT2,LOW); digitalWrite(MUX_INPUT3,HIGH);
  *right = ((long)analogRead(MUX_OUTPUT) * 1000) / 1023 + 1000;
  if(*right > 2000) *right = 2000;
  if(*right < 1000) *right = 1000;
}
