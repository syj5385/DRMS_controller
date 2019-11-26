#include "EEPROM.h"
#include <EEPROM.h>

int tream1 = 127, tream2 = 127, tream3 = 127;

void initializeEEPROM(){
  if(EEPROM.read(EEPROM_TREAM1) == 0 || EEPROM.read(EEPROM_TREAM1) == 255){
    tream1 = 127; EEPROM.write(EEPROM_TREAM1,tream1);
  }
  else{
    tream1 = EEPROM.read(EEPROM_TREAM1);
  }

  if(EEPROM.read(EEPROM_TREAM2) == 0 || EEPROM.read(EEPROM_TREAM2) == 255){
    tream2 = 127; EEPROM.write(EEPROM_TREAM2,tream2);
  }
  else{
    tream2 = EEPROM.read(EEPROM_TREAM2);
  }

  if(EEPROM.read(EEPROM_TREAM3) == 0 || EEPROM.read(EEPROM_TREAM3) == 255){
    tream3 = 127; EEPROM.write(EEPROM_TREAM3,tream3);
  }
  else{
    tream3 = EEPROM.read(EEPROM_TREAM3);
  }
}

