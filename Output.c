//The output file which handles the output

#include <pic32mx.h>

//Updates the LEDs with correct value.
//If you have two values, two leds will be lit.
void updateOutput(int value) {
      
      
  switch (value) {
    //
    case  0 : 
      PORTE = 0x0;
      break;

    case  1 : 
      PORTE = 0x1;
      break;

    case  2 : 
      PORTE = 0x3;
      break;

    case  3 : 
      PORTE = 0x7;
      break;

    case  4 : 
      PORTE = 0xF;
      break;

    case  5 : 
      PORTE = 0x1F;
      break;

    case  6 : 
      PORTE = 0x3F;
      break;

    case  7 : 
      PORTE = 0x7F;
      break;

    case  8 : 
      PORTE = 0xFF;
      break;
  }
}
