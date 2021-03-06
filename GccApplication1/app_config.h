//-----------------------------------------------------------------------------
// Copyright:      RAD Electronic Co. LTD,
// Author:         Sh. Nourbakhsh Rad
// Remarks:        
// known Problems: none
// Version:        3.0.1
// Description:    WinAVR & CodeVision compatibility ...........
//								 
//-----------------------------------------------------------------------------

#ifndef _APP_CONFIG_H_
	#define _APP_CONFIG_H_

	
	//----------  WinAVR compliler used
	#if defined(__GNUC__)
		#include <avr/io.h>
		#include <inttypes.h>
		#include <compat/deprecated.h>
		
		#include <avr/interrupt.h>
		#include <avr/sleep.h>
		
		#include <util/twi.h>
		#include <avr/pgmspace.h>
		#include <avr/eeprom.h>
		
		#include <util/delay.h>
		
		#include <stdlib.h>
		#include <stdio.h>

		//-----------------------	 
		#define _NOP()                         	        asm volatile("nop\n\t")

		//-----------------------	 
		#if	defined(__AVR_AT90S4414__) || defined(__AVR_AT90S8515__) || defined(__AVR_ATmega64__)  || \
  	    defined(__AVR_ATmega8515__)|| defined(__AVR_ATmega103__) || defined(__AVR_ATmega128__) || \
    	  defined(__AVR_ATmega161__) || defined(__AVR_ATmega162__)
    
    	#define XMemory_OK
    #endif

	//----------  CodeVision compiler used
	#elif defined(__CODEVISIONAVR__)
		//#include <mega64.h>		//Include your uC file!
		#include <mega128.h>		//Include your uC file!
		#include "CV_GNU_comp.h"
		#include <stdlib.h>
		#include <stdio.h>
		#include <string.h>
		#include <delay.h>

		//-----------------------	 
		#ifndef F_CPU
			#define F_CPU																	_MCU_CLOCK_FREQUENCY_
		#endif
		
		//-----------------------	 
		typedef signed char             								int8;
		typedef unsigned char           								uint8;
		typedef signed int              								int16;
		typedef unsigned int            								uint16;
		typedef signed long int         								int32;
		typedef unsigned long int       								uint32;	
		
		//-----------------------	 
		#define PGM_P                                  	char flash *
		#define PROGMEM                                	flash
		#define const																		flash
		#define PSTR(x)                                	x

		#define EEMEM                                 	eeprom
		#define pgm_read_byte(x)                  	   	(*((uint8  flash *)(x)))
		#define pgm_read_word(x)                   	    (*((uint16 flash *)(x)))
		#define pgm_read_byte_near(x)										(*((uint8  flash *)(x)))

		#define eeprom_read_byte(ads)               	  (*((uint8  eeprom *)(ads)))
		#define eeprom_read_word(ads)               	  (*((uint16 eeprom *)(ads)))

		#define eeprom_write_byte(ads, x)          	    (*((uint8  eeprom *)(ads))) = x
		#define eeprom_write_word(ads, x)        	      (*((uint16 eeprom *)(ads))) = x

		#define _NOP()                         	        #asm("nop")
		#define sei()                       	          #asm("sei")
		#define cli()                     	            #asm("cli")

		#define _delay_ms               	              delay_ms

		#ifndef ISR(vec)
			#define ISR(vec)            	                interrupt [vec] void isr##vec(void)
		#endif

		#define _BV(pin)            	                  (1<< pin)
		#define sbi(port, pin)      	                  (port |=  _BV(pin))
		#define cbi(port, pin)  		                    (port &= ~_BV(pin))
		#define outb(port, data)												(port = data)
		#define inb(port)																(port)
		
		#define bit_is_set(port, pin)		        				(port &   _BV(pin))
		#define loop_until_bit_is_set(port, pin)      	while(!bit_is_set(port, pin));

		//-----------------------	 
  	#define strncpy(a, b, c)												strncpy(a, b, c)
		#define strnlen(a, b)														strlen(a)

  	#define strncpy_P(a, b, c)											strcpyf(a, b)
		#define strnlen_P(a, b)													strlenf(a)
		
		#define prog_char																flash char
		
		//----------------------------------------------------------------
		#if	defined(_CHIP_AT90S4414_) || defined(_CHIP_AT90S8515_) || defined(_CHIP_ATMEGA64_)  || \
  	   	defined(_CHIP_ATMEGA8515_)|| defined(_CHIP_ATMEGA103_) || defined(_CHIP_ATMEGA128_) || \
    	 	defined(_CHIP_ATMEGA161_) || defined(_CHIP_ATMEGA162_)

    	#define XMemory_OK
    #endif

	//----------  Compiler Error
	#else		
		#error "compiler error ( only WinAVR or CodeVision can be used !!! )"
		
	#endif
	
	//----------------------------------------------------------------
	//----------------------------------------------------------------
  #define _rol(x) 																	((x & 0x80) ? ((x << 1) | 0x01) : (x << 1))
  #define _ror(x)																		((x & 0x01) ? ((x >> 1) | 0x80) : (x >> 1))

	#define True																			1
	#define False																			0
	
	#define ON																				1
	#define OFF																				0
	
	#define HIGH																			1
	#define LOW																				0

#endif	//_APP_CONFIG_H_
