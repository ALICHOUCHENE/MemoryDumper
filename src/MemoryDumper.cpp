/*
 * MemoryDumper.h - Debugging library for Arduino - Version 1.1.0
 *
 * Original library        (0.1)   by CHOUCHENE Ali.
 *
 * This library is free software; you can redistribute it and/or
 * modify it. 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * This library is made to dump the registers and the RAM of the atmega328p microcontroller
 *
 *  This library uses the serial port to print registers and RAM contentes 
 *  The UART communication layer is developped with bare metal programming so the Serial library is not used in order to 
 *  optimise the library size and the run time
 */

 
#include"MemoryDumper.h"

/*  this function wiatuntilthe TX data transmission register is 
    cleared so the next transmission can be processed */

static void wait_until_transmition(){

  while ( !( UCSR0A & (1 << UDRE0)) );

}


/*  this function enable the UART perepheral and set the baud rate
    the baud rate is given as a parameter and it only can be 
    one od the standards baud rates                             */

static void UartBegin(int baud_rate){
  
  UCSR0B = (1 << TXEN0);                //Enable the serial output

  switch (baud_rate){

    case 57600 :
      UBRR0L = 16;                      //Set the baud rate to 57600bps 
      break;
      
    case 9600 :
      UBRR0L = 103;                     //Set the baud rate to 9600bps 
      break;
      
    case 4800 :
      UBRR0L = 207;                     //Set the baud rate to 4800bps 
      break;
    
    case 115200 :
      UBRR0L = 8;                       //Set the baud rate to 115200bps 
      break;

    }
  
}

static void UartStop(){
  
  UCSR0B &=~ (1 << TXEN0);              //Disable the serial output

}


static uint8_t GetRegisterContent(uint8_t register_adress){
  
  uint8_t register_content;
  register_content = *(byte *)(register_adress);
  return register_content;
 
}


static void SendDumpedData(char register_name[], uint8_t register_content){
  int i=0;
  // print the register name
    while(register_name[i]!='\0'){
      
      UDR0=(char)(register_name[i]);
      wait_until_transmition();
      i++;
  }
  
  UDR0 = 0x20;                          // ascii code of  " " in hex
  while ( !( UCSR0A & (1 << UDRE0)) );
  UDR0=(char)(0x3D);                    // ascii code of "=" in hex
  wait_until_transmition();
  UDR0 = 0x20;                          // ascii code of " " in hex
  wait_until_transmition();
  UDR0 = 0x30;                          // ascii code of "0" in hex                 
  wait_until_transmition();           
  UDR0 = 0x78;                          // ascii code of "x" in hex            
  wait_until_transmition();
  
  // convert data content to ascii so it can be easely interpretated
  
  if (((register_content >> 4) & 0x0F) > 9)UDR0 = 55 + (register_content >> 4 & 0x0F);
  else UDR0 = 48 + ((register_content >> 4) & 0x0F);
  wait_until_transmition();

  if ((register_content & 0x0F) > 9)UDR0 = 55 + (register_content & 0x0F);
  else UDR0 = 48 + (register_content & 0x0F);
  wait_until_transmition();

  UDR0 = 0x0A;                      // ascii code in hex of "\n"
  wait_until_transmition();
}


void DumpAllRegisters(){
  
  for(int i=0;i<=NUMBER_OF_REGISTERS;i++){
    
    uint8_t register_adress=register_table[i].address;
    char reg_name[8];
    memcpy(reg_name,register_table[i].register_name,8);
    uint8_t register_content=GetRegisterContent(register_adress);
    SendDumpedData(reg_name,register_content);
  }
}


void StartDumping(int baud_rate){
  
  UartBegin(baud_rate);
  
}


void StopDumping(){
  
  UartStop();
}


void Dump(String RegisterToDump){
  char reg_name[8];
  for(int i=0;i<=NUMBER_OF_REGISTERS;i++){
    
    String reg = String(register_table[i].register_name);
    if( reg==RegisterToDump){

      memcpy(reg_name,register_table[i].register_name,8);
      uint8_t register_adress=register_table[i].address;
      uint8_t register_content=GetRegisterContent(register_adress);
      SendDumpedData(reg_name,register_content);
     
    }
  }

}


void DumpRam() {

  uint16_t address;
  uint8_t adress_content, new_line;
  address = START_OF_RAM;
  new_line = 1;

  while (address <= END_OF_RAM) {
    adress_content = *(byte *)address;

    if (((adress_content >> 4) & 0x0F) > 9)UDR0 = 55 + (adress_content >> 4 & 0x0F);
    else UDR0 = 48 + ((adress_content >> 4) & 0x0F);
    wait_until_transmition();

    if ((adress_content & 0x0F) > 9)UDR0 = 55 + (adress_content & 0x0F);
    else UDR0 = 48 + (adress_content & 0x0F);
    wait_until_transmition();

    UDR0 = 0x20;
    wait_until_transmition();

    if (new_line == 64) {
      new_line = 0;
      UDR0 = 0x0A;
      wait_until_transmition();
      UDR0 = 0x0D;
      wait_until_transmition();
    }

    address ++;
    new_line ++;
  }
}
