#include "MemoryDumper.h"



void setup() {
  StartDumping(9600);    // start dumping by enabling the serial output

}

void loop() {
  DumpAllRegisters();   // dump all registers contents
  StopDumping();        // Stop dumping by disabling the serial output
  while(1);             // wait for ever

}
