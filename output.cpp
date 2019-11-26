
#include <arduino.h>
#include "output.h"

void connectLED(boolean onoff){
  if(onoff)
    digitalWrite(OUTPUT_LED,HIGH);
  else
    digitalWrite(OUTPUT_LED,LOW);

}
