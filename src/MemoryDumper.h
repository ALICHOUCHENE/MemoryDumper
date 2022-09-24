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

// ensure this library description is only included once

#ifndef MEMORY_DUMPER
#define MEMORY_DUMPER

#include <Arduino.h>
#define  PINB_ADDRESS   0x23
#define  DDRB_ADDRESS   0x24
#define  PORTB_ADDRESS  0x25
#define  PINC_ADDRESS   0x26
#define  DDRC_ADDRESS   0x27
#define  PORTC_ADDRESS  0x28
#define  PIND_ADDRESS   0x29
#define  DDRD_ADDRESS   0x2A
#define  PORTD_ADDRESS  0x2B
#define  TIFR0_ADDRESS  0x35
#define  TIFR1_ADDRESS  0x36
#define  TIFR2_ADDRESS  0x37
#define  PCIFR_ADDRESS  0x3B
#define  EIFR_ADDRESS   0x3C
#define  EIMSK_ADDRESS  0x3D
#define  GPIOR0_ADDRESS 0x3E
#define  EECR_ADDRESS   0x3F
#define  EEDR_ADDRESS   0x40
#define  EEARL_ADDRESS  0x41
#define  EEARH_ADDRESS  0x42
#define  GTCCR_ADDRESS  0x43
#define  TCCR0A_ADDRESS 0x44
#define  TCCR0B_ADDRESS 0x45
#define  TCNT0_ADDRESS  0x46
#define  OCR0A_ADDRESS  0x47
#define  OCR0B_ADDRESS  0x48
#define  GPIOR1_ADDRESS 0x4A
#define  GPIOR2_ADDRESS 0x4B
#define  SPCR_ADDRESS   0x4C
#define  SPSR_ADDRESS   0x4D
#define  SPDR_ADDRESS   0x4E
#define  ACSR_ADDRESS   0x50
#define  SMCR_ADDRESS   0x53
#define  MCUSR_ADDRESS  0x54
#define  MCUCR_ADDRESS  0x55
#define  SPMCSR_ADDRESS 0x57
#define  SPL_ADDRESS    0x5D
#define  SPH_ADDRESS    0x5E
#define  SREG_ADDRESS   0x5F
#define  WDTCSR_ADDRESS 0x60
#define  CLKPR_ADDRESS  0x61
#define  PRR_ADDRESS    0x64
#define  OSCCAL_ADDRESS 0x66
#define  PCICR_ADDRESS  0x68
#define  EICRA_ADDRESS  0x69
#define  PCMSK0_ADDRESS 0x6B
#define  PCMSK1_ADDRESS 0x6C
#define  PCMSK2_ADDRESS 0x6D
#define  TIMSK0_ADDRESS 0x6E
#define  TIMSK1_ADDRESS 0x6F
#define  TIMSK2_ADDRESS 0x70
#define  ADCL_ADDRESS   0x78
#define  ADCH_ADDRESS   0x79
#define  ADCSRA_ADDRESS 0x7A
#define  ADCSRB_ADDRESS 0x7B
#define  ADMUX_ADDRESS  0x7C
#define  DIDR0_ADDRESS  0x7E
#define  DIDR1_ADDRESS  0x7F
#define  TCCR1A_ADDRESS 0x80
#define  TCCR1B_ADDRESS 0x81
#define  TCCR1C_ADDRESS 0x82
#define  TCNT1L_ADDRESS 0x84
#define  TCNT1H_ADDRESS 0x85
#define  ICR1L_ADDRESS  0x86
#define  ICR1H_ADDRESS  0x87
#define  OCR1AL_ADDRESS 0x88
#define  OCR1AH_ADDRESS 0x89
#define  OCR1BL_ADDRESS 0x8A
#define  OCR1BH_ADDRESS 0x8B
#define  TCCR2A_ADDRESS 0xB0
#define  TCCR2B_ADDRESS 0xB1
#define  TCNT2_ADDRESS  0xB2
#define  OCR2A_ADDRESS  0xB3
#define  OCR2B_ADDRESS  0xB4
#define  ASSR_ADDRESS   0xB6
#define  TWBR_ADDRESS   0xB8
#define  TWSR_ADDRESS   0xB9
#define  TWAR_ADDRESS   0xBA
#define  TWDR_ADDRESS   0xBB
#define  TWCR_ADDRESS   0xBC
#define  TWAMR_ADDRESS  0xBD
#define  UCSR0A_ADDRESS 0xC0
#define  UCSR0B_ADDRESS 0xC1
#define  UCSR0C_ADDRESS 0xC2
#define  UBRR0L_ADDRESS 0xC4
#define  UBRR0H_ADDRESS 0xC5
#define  UDR0_ADDRESS   0xC6

// define RAM boundaries
#define START_OF_RAM    0x100       
#define END_OF_RAM      0x8FF

// define the number of registers
#define NUMBER_OF_REGISTERS 86
  

// define a new data structure to easily handle registers
typedef struct{
  byte     address;
  char     register_name[8];
}memory_map;

// declare a table of memory map
const memory_map register_table[] = {

    [0] = {
        .address          = PINB_ADDRESS,
        .register_name    = {'P','I','N','B'},
    },

    [1] = {
        .address          = DDRB_ADDRESS,
        .register_name    = {'D','D','R','B'},
    },

    [2] = {
        .address        = PORTB_ADDRESS,
        .register_name  = {'P','O','R','T','B'},
    },

    [3] = {
        .address        = PINC_ADDRESS,
        .register_name  = {'P','I','N','C'} ,
    },

    [4] = {
        .address        = DDRC_ADDRESS,
        .register_name  = {'D','D','R','C'},
    },

    [5] = {
        .address        = PORTC_ADDRESS,
        .register_name  = {'P','O','R','T','C'},
    },

    [6] = {
        .address        = PIND_ADDRESS,
        .register_name  = {'P','I','N','D'},
    },

    [7] = {
        .address        = DDRD_ADDRESS,
        .register_name  = {'D','D','R','D'},
    },

    [8] = {
        .address        = PORTD_ADDRESS,
        .register_name  = {'P','O','R','T','D'},
    },

    [9] = {
        .address        = TIFR0_ADDRESS,
        .register_name  = {'T','I','F','R','0'},
    },

    [10] = {
        .address        = TIFR1_ADDRESS,
        .register_name  = {'T','I','F','R','1'},
    },

    [11] = {
        .address        = TIFR2_ADDRESS,
        .register_name  = {'T','I','F','R','2'},
    },

    [12] = {
        .address        = PCIFR_ADDRESS,
        .register_name  = {'P','C','I','F','R'},
    },

    [13] = {
        .address        = EIFR_ADDRESS,
        .register_name  = {'E','I','F','R'},
    },

    [14] = {
        .address        = EIMSK_ADDRESS,
        .register_name  = {'E','I','M','S','K'},
    },

    [15] = {
        .address        = GPIOR0_ADDRESS,
        .register_name  = {'G','P','I','O','R','0'},
    },

    [16] = {
        .address        = EECR_ADDRESS,
        .register_name  = {'E','E','C','R'},
    },

    [17] = {
        .address        = EEDR_ADDRESS,
        .register_name  = {'E','E','D','R'},
    },

    [18] = {
        .address        = EEARL_ADDRESS,
        .register_name  = {'E','E','A','R','L'},
    },

    [19] = {
        .address        = EEARH_ADDRESS,
        .register_name  = {'E','E','A','R','H'},
    },

    [20] = {
        .address        = GTCCR_ADDRESS,
        .register_name  = {'G','T','C','C','R'},
    },

    [21] = {
        .address        = TCCR0A_ADDRESS,
        .register_name  = {'T','C','C','R','0','A'},
    },

    [22] = {
        .address        = TCCR0B_ADDRESS,
        .register_name  = {'T','C','C','R','0','B'},
    },

    [23] = {
        .address        = TCNT0_ADDRESS,
        .register_name  = {'T','C','N','T','0'},
    },

    [24] = {
        .address        = OCR0A_ADDRESS,
        .register_name  = {'O','C','R','0','A'},
    },

    [25] = {
        .address        = OCR0B_ADDRESS,
        .register_name  = {'O','C','R','0','B'},
    },

    [26] = {
        .address        = GPIOR1_ADDRESS,
        .register_name  = {'G','P','I','O','R','1'},
    },

    [27] = {
        .address        = GPIOR2_ADDRESS,
        .register_name  = {'G','P','I','O','R','2'},
    },

    [28] = {
        .address        = SPCR_ADDRESS,
        .register_name  = {'S','P','C','R'},
    },

    [29] = {
        .address        = SPSR_ADDRESS,
        .register_name  = {'S','P','S','R'},
    },

    [30] = {
        .address        = SPDR_ADDRESS,
        .register_name  = {'S','P','D','R'},
    },

    [31] = {
        .address        = ACSR_ADDRESS,
        .register_name  = {'A','C','S','R'},
    },

    [32] = {
        .address        = SMCR_ADDRESS,
        .register_name  = {'S','M','C','R'},
    },

    [33] = {
        .address        = MCUSR_ADDRESS,
        .register_name  = {'M','C','U','S','R'},
    },

    [34] = {
        .address        = MCUCR_ADDRESS,
        .register_name  = {'M','C','U','C','R'},
    },

    [35] = {
        .address        = SPMCSR_ADDRESS,
        .register_name  = {'S','P','M','C','S','R'},
    },

    [36] = {
        .address        = SPL_ADDRESS,
        .register_name  = {'S','P','L'},
    },

    [37] = {  
        .address        = SPH_ADDRESS,
        .register_name  = {'S','P','H'},
    },

    [38] = {
        .address        = SREG_ADDRESS,
        .register_name  = {'S','R','E','G'},
    },

    [39] = {
        .address        = WDTCSR_ADDRESS,
        .register_name  = {'W','D','T','C','S','R'},
    },

    [40] = {
        .address        = CLKPR_ADDRESS,
        .register_name  = {'C','L','K','P','R'},
    },

    [41] = {
        .address        = PRR_ADDRESS,
        .register_name  = {'P','R','R'},
    },

    [42] = {
        .address        = OSCCAL_ADDRESS,
        .register_name  = {'O','S','C','C','A','L'},
    },

    [43] = {
        .address        = PCICR_ADDRESS,
        .register_name  = {'P','C','I','C','R'},
    },

    [44] = {
        .address        = EICRA_ADDRESS,
        .register_name  = {'E','I','C','R','A'},
    },

    [45] = {
        .address        = PCMSK0_ADDRESS,
        .register_name  = {'P','C','M','S','K','0'},
    },

    [46] = {
        .address        = PCMSK1_ADDRESS,
        .register_name  = {'P','C','M','S','K','1'},
    },

    [47] = {
        .address        = PCMSK2_ADDRESS,
        .register_name  = {'P','C','M','S','K','2'},
    },

    [48] = {
        .address        = TIMSK0_ADDRESS,
        .register_name  = {'T','I','M','S','K','0'},
    },

    [49] = {
        .address        = TIMSK1_ADDRESS,
        .register_name  = {'T','I','M','S','K','1'},
    },

    [50] = {
        .address        = TIMSK2_ADDRESS,
        .register_name  = {'T','I','M','S','K','2'},
    },

    [51] = {
        .address        = ADCL_ADDRESS,
        .register_name  = {'A','D','C','L'},
    },

    [52] = {
        .address        = ADCH_ADDRESS,
        .register_name  = {'A','D','C','H'},
    },

    [53] = {
        .address        = ADCSRA_ADDRESS,
        .register_name  = {'A','D','C','S','R','A'},
    },

    [54] = {
        .address        = ADCSRB_ADDRESS,
        .register_name  = {'A','D','C','S','R','B'},
    },

    [55] = {
        .address        = ADMUX_ADDRESS,
        .register_name  = {'A','D','M','U','X'},
    },

    [56] = {
        .address        = DIDR0_ADDRESS,
        .register_name  = {'D','I','D','R','0'},
    },

    [57] = {
        .address        = DIDR1_ADDRESS,
        .register_name  = {'D','I','D','R','1'},
    },

    [58] = {
        .address        = TCCR1A_ADDRESS,
        .register_name  = {'T','C','C','R','1','A'},
    },

    [59] = {
        .address        = TCCR1B_ADDRESS,
        .register_name  = {'T','C','C','R','1','B'},
    },

    [60] = {
        .address    = TCCR1C_ADDRESS,
        .register_name  = {'T','C','C','R','1','C'},
    },

    [61] = {
        .address        = TCNT1L_ADDRESS,
        .register_name  = {'T','C','N','T','1','L'},
    },

    [62] = {
        .address        = TCNT1H_ADDRESS,
        .register_name  = {'T','C','N','T','1','H'},
    },

    [63] = {
        .address        = ICR1L_ADDRESS,
        .register_name  = {'I','C','R','1','L'},
    },

    [64] = {
        .address        = ICR1H_ADDRESS,
        .register_name  = {'I','C','R','1','H'},
    },

    [65] = {
        .address        = OCR1AL_ADDRESS,
        .register_name  = {'O','C','R','1','A','L'},
    },

    [66] = {
        .address        = OCR1AH_ADDRESS,
        .register_name  = {'O','C','R','1','A','H'},
    },

    [67] = {
        .address        = OCR1BL_ADDRESS,
        .register_name  = {'O','C','R','1','B','L'},
    },

    [68] = {
        .address        = OCR1BH_ADDRESS,
        .register_name  = {'O','C','R','1','B','H'},
    },

    [69] = {
        .address        = TCCR2A_ADDRESS,
        .register_name  = {'T','C','C','R','2','A'},
    },

    [70] = {
        .address        = TCCR2B_ADDRESS,
        .register_name  = {'T','C','C','R','2','B'},
    },

    [71] = {
        .address        = TCNT2_ADDRESS,
        .register_name  = {'T','C','N','T','2'},
    },

    [72] = {
        .address        = OCR2A_ADDRESS,
        .register_name  = {'O','C','R','2','A'},
    },

    [73] = {
        .address        = OCR2B_ADDRESS,
        .register_name  = {'O','C','R','2','B'},
    },

    [74] = {
        .address        = ASSR_ADDRESS,
        .register_name  = {'A','S','S','R'},
    },

    [75] = {
        .address        = TWBR_ADDRESS,
        .register_name  = {'T','W','B','R'},
    },

    [76] = {
        .address        = TWSR_ADDRESS,
        .register_name  = {'T','W','S','R'},
    },

    [77] = {
        .address        = TWAR_ADDRESS,
        .register_name  = {'T','W','A','R'},
    },

    [78] = {
        .address        = TWDR_ADDRESS,
        .register_name  = {'T','W','D','R'},
    },

    [79] = {
        .address        = TWCR_ADDRESS,
        .register_name  = {'T','W','C','R'},
    },

    [80] = {
        .address        = TWAMR_ADDRESS,
        .register_name  = {'T','W','A','M','R'},
    },

    [81] = {
        .address        = UCSR0A_ADDRESS,
        .register_name  = {'U','C','S','R','0','A'},
    },

    [82] = {
        .address        = UCSR0B_ADDRESS,
        .register_name  = {'U','C','S','R','0','B'},
    },

    [83] = {
        .address        = UCSR0C_ADDRESS,
        .register_name  = {'U','C','S','R','0','C'},
    },

    [84] = {
        .address        = UBRR0L_ADDRESS,
        .register_name  = {'U','B','R','R','0','L'},
    },

    [85] = {
        .address        = UBRR0H_ADDRESS,
        .register_name  = {'U','B','R','R','0','H'},
    },

    [86] = {
        .address        = UDR0_ADDRESS,
        .register_name  = {'U','D','R','0'},
    },
    


};
/*
 ***********************************************************************************************
 *********************                  FUNCTIONS TO CALL                  *********************
 *********************************************************************************************** 
 */


/*! \brief This function enable the Memory dumping by enabling the UART peripheral
 *         The baud rate is given as a parameter
 *
 *  \fn void StartDumping(int baud_rate)
 *  \param baud_rate
 *  
 */
 
void StartDumping(int baud_rate);



/*! \brief This function dump all registers content
 *         and print the results on the arduino serial monitor
 *
 *  \fn DumpAllRegisters()
 *  \param void 
 *  
 */

void DumpAllRegisters();


/*! \brief This function dump stop dumping and disable the UART peripheral
 *
 *  \fn void StopDumping()
 *  \param void 
 *  
 */

void StopDumping();


/*! \brief This function dump the register given as a parameter
 *         It prints its content on the arduino serial monitor
 *
 *  \fn void Dump(String reg)
 *  \param String reg
 *  
 */

void Dump(String reg);



/*! \brief This function dump the RAM 
 *         It prints its content on the arduino serial monitor
 *
 *  \fn void DumpRam();
 *  \param void
 *  
 */

void DumpRam();

#endif
