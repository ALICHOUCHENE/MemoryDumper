# MemoryDumper
## Arduino library to dump registers and RAM contents

Bare metal programming is a way to create efficient and lightweight real-time applications. However, writing a piece of code that modifies bits in registers to achieve the desired behavior of the microcontroller requires a lot of debugging to see what is actually happening in the hardware.

This library uses the serial port to print registers and RAM contentes.
The UART communication layer is developed in bare metal programming so the Serial library is not used in order to optimize the library size and execution time.

## Implemented functions

- void StartDumping(int baud_rate)

>  This function enable the Memory dumping by enabling the UART peripheral with the baud rate given as a parameter

- void DumpAllRegisters()

>  This function dump all registers content and print the results on the arduino serial monitor

- void Dump(String reg)

>  This function dump the register given as a parameter and print its content on the arduino serial monitor

- void DumpRam()

>  This function dump the RAM and print its content on the arduino serial monitor
  
- void StopDumping()

>  This function dump stop dumping and disable the UART peripheral
 