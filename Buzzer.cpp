#include "Buzzer.h"
#include <arduino.h>

void buzzer(int choice){
  switch(choice){
    case 1 :
      for(int i=0; i<500; i++){
        digitalWrite(3,1);
        delayMicroseconds(200);
        digitalWrite(3,0);
        delayMicroseconds(200);
      }
  
     break; 
  
     case 2 :
      for(int i=0; i<1000; i++){
        digitalWrite(3,1);
        delayMicroseconds(100);
        digitalWrite(3,0);
        delayMicroseconds(00);
      }
  
     break;
  
     case 3 :
      for(int i=0; i<200; i++){
        digitalWrite(3,1);
        delayMicroseconds(300);
        digitalWrite(3,0);
        delayMicroseconds(300);
      }
  
     break;
  
     case 4 :
      for(int i=0; i<150; i++){
        digitalWrite(3,1);
        delayMicroseconds(600);
        digitalWrite(3,0);
        delayMicroseconds(600);
        }
    
       break;
    
       case 5 :
        for(int i=0; i<150; i++){
          digitalWrite(3,1);
          delay(1);
          digitalWrite(3,0);
          delay(1);
        }
    
       break;

       case 6: 
       for(int i=0 ; i<400 ; i++){
        digitalWrite(3,1);
        delayMicroseconds(600);
        digitalWrite(3,0);
        delayMicroseconds(600);
       }
  }
}

void song(int delay_time, int loop){
  for(int i=0; i<loop; i++){
    digitalWrite(3,1);
    delayMicroseconds(delay_time);
    digitalWrite(3,0);
    delayMicroseconds(delay_time);
  }
}

void init_Effect(){
  song(100,300);
  delay(200);
  song(100,200);
  delay(200);
}


