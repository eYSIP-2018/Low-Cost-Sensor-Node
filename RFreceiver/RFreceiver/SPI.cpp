#include "SPI.h"
#include <stdint-gcc.h>

SPIClass SPI;
void SPIClass::begin()
{
   cli();//noInterrupts(); // Protect from a scheduler and prevent transactionBegin
 
    
    Set_pin(SS, OUT);

    // Warning: if the SS pin ever becomes a LOW INPUT then SPI
    // automatically switches to Slave, so the data direction of
    // the SS pin MUST be kept as OUT.
    SPCR |= _BV(MSTR);
    SPCR |= _BV(SPE);

    // Set direction register for SCK and MOSI pin.
    // MISO pin automatically overrides to INPUT.
    // By doing this AFTER enabling SPI, we avoid accidentally
    // clocking in a single bit since the lines go directly
    // from "input" to SPI control.
    // http://code.google.com/p/arduino/issues/detail?id=888
    Set_pin(SCK, OUT);
    Set_pin(MOSI, OUT);
  
}

void SPIClass::end()
 {
  uint8_t sreg = SREG;
   cli(); //noInterrupts(); // Protect from a scheduler and prevent transactionBegin
  // Decrease the reference counter
}

