//**************************************************************
//    ******** FUNCTIONS FOR I2C COMMUNICATION  *******
//**************************************************************
//Controller:        ATmega128 (Crystal: 16Mhz)
//Compiler:                winAVR (AVR-GCC)
//Author:                CC Dharmani, Chennai (India)
//                                www.dharmanitech.com
//Date:                        April 2009
//********************************************************

//link to post: http://www.dharmanitech.com/2008/08/interfacing-rtc-serial-eeprom-using-i2c.html
#include "..\app_config.h"
#include "..\UART\UART_routines.h"	
#include "eeprom_init.h"	

volatile unsigned char errorStatus, data_1, option, totalChar;
volatile unsigned int pageNumber;
                  
void port_init(void)
{
 /*PORTA = 0x00;
 DDRA  = 0x00;
 PORTB = 0x00;
 DDRB  = 0x00;
 PORTC = 0x00;
 DDRC  = 0xff;
 PORTD = 0x00;
 DDRD  = 0x00;
 PORTE = 0x00;
 DDRE  = 0x00;
 PORTF = 0x00;
 DDRF  = 0x00;
 PORTG = 0x00;
 DDRG  = 0x00;
 */
 cli(); //disable all interrupts
sei(); //re-enable interrupts
}
//TWI initialize
// bit rate:18 (freq: 100Khz)
void twi_init(void)
{
 TWCR= 0X00; //disable twi
 TWBR= 0x12; //set bit rate
 TWSR= 0x00; //set prescale
 TWCR= 0x44; //enable twi
}
//call this routine to initialize all peripherals
void init_devices(void)
{
 //stop errant interrupts until set up
 cli(); //disable all interrupts
 XDIV  = 0x00; //xtal divider
 XMCRA = 0x00; //external memory
 port_init();
 uart0_init();
 twi_init();
 
 MCUCR = 0x00;
 EICRA = 0x00; //extended ext ints
 EICRB = 0x00; //extended ext ints
 EIMSK = 0x00;
 TIMSK = 0x00; //timer interrupt sources
 ETIMSK = 0x00; //extended timer interrupt sources
 //SEI(); //re-enable interrupts
} 
        

