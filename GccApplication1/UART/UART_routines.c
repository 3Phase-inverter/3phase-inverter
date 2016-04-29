//**************************************************************
//******** FUNCTIONS FOR SERIAL COMMUNICATION USING UART *******
//**************************************************************
//Controller:	ATmega128 (Crystal: 16Mhz)
//Compiler:		winAVR (AVR-GCC)
//Author:		CC Dharmani, Chennai (India)
//				www.dharmanitech.com
//Date:			April 2009
//********************************************************

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "UART_routines.h"


//**************************************************
//Function initialize UART0
//desired baud rate: 19200
//actual: baud rate:19231 (0.2%)
//char size: 8 bit
//parity: Disabled
//**************************************************
void uart0_init(void)
{
 UCSR0B = 0x00; //disable while setting baud rate
 UCSR0A = 0x00;
 UCSR0C = 0x06;
 UBRR0L = 0x33; //set baud rate lo
 UBRR0H = 0x00; //set baud rate hi
 UCSR0B = 0x98;
}
//**************************************************
//Function to receive a single byte
//*************************************************
unsigned char receiveByte( void )
{
	unsigned char data, status;
	
	while(!(UCSR0A & (1<<RXC0))); 	// Wait for incomming data
	
	status = UCSR0A;
	data = UDR0;
		   
	return(data);
}

//***************************************************
//Function to transmit a single byte
//***************************************************
void transmitByte( unsigned char data )
{
	while ( !(UCSR0A & (1<<UDRE0)) )
		; 			                /* Wait for empty transmit buffer */
	UDR0 = data; 			        /* Start transmition */
}

//***************************************************
//Function to transmit a string in Flash
//***************************************************
void transmitString_F(char* string)
{
  while (pgm_read_byte(&(*string)))
   transmitByte(pgm_read_byte(&(*string++)));
}

//***************************************************
//Function to transmit a string in RAM
//***************************************************
void transmitString(char* string)
{
    while (*string)
		transmitByte(*string++);
}
