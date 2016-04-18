//-----------------------------------------------------------------------------
// Copyright:      www.elasa.ir
// Author:         OZHAN KD ported by Sh. Nourbakhsh Rad
// Remarks:        
// known Problems: none
// Version:        1.1.0
// Description:    SPWM test...
//-----------------------------------------------------------------------------
//#ifndef F_CPU
//#define F_CPU 8000000UL // 16 MHz clock speed
//#endif
//	Include Headers
//*****************************************************************************
 



#include "app_config.h"
#include "defines.h"

#include "HW_SPWM.h"
#include "SPWM\SPWM.h" 

//--------------------------------------------------
#include "N11\N1100.h"
#include "sFONT\sFONT.h"

//--------------------------------------------------
#include "ADC\ADC.h"

//flags={0,0,0};
//--------------------------------------------------



//----------------------------------------------------------------

#define D4 eS_PORTC4
#define D5 eS_PORTC5
#define D6 eS_PORTC6
#define D7 eS_PORTC7
#define RS eS_PORTC2
#define EN eS_PORTC3
#include "lcd.h" //Can be download from the bottom of this article
//	Constants and Varables
//*****************************************************************************
//-------------------------------------------------- From inverter 4
enum
{
 STOP_MODE=0,
 RUN_MODE,
 FAULT_MODE
};
enum
{
 RUN_CODE=0,
 STOP_CODE,
 DIR_CODE,
 NO_KEY_CODE
};

volatile unsigned char temp_key_code=NO_KEY_CODE,
mode=STOP_MODE;//a_boost=A_BOOST_MIN;
/*
struct 
{
 volatile unsigned char 
 dir_f:1,
 deceleration_f:1,
 dir_change_f:1;
}flags={0,0,0};

 */

//Temp Const.
char 														Ctemp[24];
int  														Itemp = 0;
int  														key_code,old_key_code ;


//	Functions Prototype
//*****************************************************************************
void Initial(void);
void Splash(void);

void test01(void);
void LCD_0(void);

//	<<< main function >>>
//*****************************************************************************
void main(void)
{
	
	DDRE = (1<<PE4);     // put PortB bit 5 as input
	PORTE = 1<<PE4;		// Enable PE4 pull-up resistor
    EIMSK = (1<<INT4)| (1<<INT5)| (1<<INT6); // Enable INT0 External Interrupt

	flags.dir_f=0;
	ENABLE_DDR|=1<<ENABLE_bp; // Turn on as output port
    DISABLE_MOTOR;
 FAULT_PORT|=1<<FAULT_bp; // Turn on fault input pullup
 RUN_LED_DDR|=1<<RUN_LED_bp;
 RUN_LED_OFF;
 DIR_LED1_DDR|=1<<DIR_LED1_bp;
 DIR_LED2_DDR|=1<<DIR_LED2_bp;
 DIR_LED1_ON;
 DIR_LED2_OFF;
 KEY_PORT|=(1<<RUN_KEY_bp)|(1<<STOP_KEY_bp)|(1<<DIR_KEY_bp); // Turn on pullups 
 
 flags.deceleration_f=flags.dir_change_f=0;flags.dir_f=1;
 
 cli(); 
 sei();
	LCD_0();
	Initial();
	
	while (1)
 {
  
  /*
  char str[16];

  
  itoa(mode, str, 10);
			//itoa();
  Lcd4_Init();
  Lcd4_Set_Cursor(1,1);
  Lcd4_Write_String(str) ;
  _delay_ms(100);
  */
  
  test01();
 }	//while(1);
} //main


//---------------------------------------------------------//
//---------------------------------------------------------//
void Initial(void)
{
	cli();												//Interrupts disable

	HW_init();
	a2dInit();										//AVCC & DIV64
	
	_delay_ms(500);

	//----------------------
	N11_Init();
	N11_Contrast(10);
	N11_Backlight(ON);
	
	//----------------------
	BUZZER(BOOT_sign);
	_delay_ms(500);

	//----------------------
	//static FILE mystdout = FDEV_SETUP_STREAM(N11_PrintChar, NULL, _FDEV_SETUP_WRITE);
  //stdout = &mystdout;
	
	N11_CLS();
	
	//----------------------
	Splash();
	BUZZER(OK_sign);

	//------------
	sei();												//Interrupts enabel	
}	//Initial

void Splash(void)
{
	static char *SPchar[5] = {
			"  SPWM test!!!",
			"by :",
			"Nourbakhsh & elasa.ir",
			"Copyright:",
			"    OZHAN KD"
			};

	//-------------
	StringAt(0, 2, SPchar[0]);
	StringAt(2, 2, SPchar[1]);
	StringAt(3, 2, SPchar[2]);
	StringAt(5, 2, SPchar[3]);
	StringAt(6, 2, SPchar[4]);

	//-------------
	_delay_ms(3000);
	N11_CLS();
}	//Splash


//---------------------------------------------------------//
//---------------------------------------------------------//
void test01(void)
{
	unsigned char				LVflag 	= 0;
	unsigned int				TCRtemp = 0;
	unsigned char				i 			= 0;

	unsigned int				FRQtemp;
	unsigned char				ACCtemp;
	unsigned char				DECtemp;

	SPWM_init();
	
	ADC_CH_init(FRQ_ACH);
	ADC_CH_init(ACC_ACH);
	ADC_CH_init(DEC_ACH);
	
	//----- main loop!
	while(1)  
	{
		unsigned char temp8;	
  temp8=KEY_PIN&((1<<DIR_KEY_bp)|(1<<STOP_KEY_bp)|(1<<RUN_KEY_bp));
  switch(temp8)
  {
  case RUN_gc:
   temp_key_code=RUN_CODE;
   break; 
  case STOP_gc:
   temp_key_code=STOP_CODE;
   break;
  case DIR_gc:
   temp_key_code=DIR_CODE;
   break;
  default:
   temp_key_code=NO_KEY_CODE;  
  }
  
  key_code=temp_key_code;
  switch(mode)
  {
  
//----------------------------------------------------------------
  
  case STOP_MODE:   // 0
   if((FAULT_PIN&(1<<FAULT_bp))==0)
   {
    old_key_code=key_code;
    mode=FAULT_MODE; // IR2130 fault condition
	RUN_LED_OFF;
	DISABLE_MOTOR;
	
    break;
   }
   if((key_code==RUN_CODE)&&(key_code!=old_key_code))
   {
    old_key_code=key_code;
    mode=RUN_MODE;
    RUN_LED_ON;
    ENABLE_MOTOR; 
	 if(flags.dir_f)
    {     
     DIR_LED1_ON;
     DIR_LED2_OFF;     
    }
    else
    {     
     DIR_LED1_OFF;
     DIR_LED2_ON;
    }      
   }
   else if((key_code==DIR_CODE)&&(key_code!=old_key_code))
   {
    old_key_code=key_code;
    if(flags.dir_f)
    {     
     DIR_LED1_ON;
     DIR_LED2_OFF;     
    }
    else
    {     
     DIR_LED1_OFF;
     DIR_LED2_ON;
    }
    flags.dir_f^=1;
   }
   else old_key_code=key_code;   
   break;
  
//----------------------------------------------------------------
  
  case RUN_MODE:    //1
   if((FAULT_PIN&(1<<FAULT_bp))==0)
   {
	   
    DISABLE_MOTOR;
	RUN_LED_OFF;
    flags.deceleration_f=0;
    flags.dir_change_f=0;
    old_key_code=key_code;
    mode=FAULT_MODE; // Fault condition
    break;
   }
   if((key_code==STOP_CODE)&&(key_code!=old_key_code))
   {
    old_key_code=key_code;    
    flags.deceleration_f=1;    
   }
   else if((key_code==DIR_CODE)&&(key_code!=old_key_code))
   {
    old_key_code=key_code;
    cli()   ; 
    flags.deceleration_f=1;
    flags.dir_change_f=1;
    sei() ;  
   }
   else old_key_code=key_code;
   break;  
   
//----------------------------------------------------------------
  
  case FAULT_MODE:  //   2
  
  
   if((FAULT_PIN&(1<<FAULT_bp))&&(key_code==STOP_CODE)&&(key_code!=old_key_code))    
   {
     old_key_code=key_code;
     mode=STOP_MODE;
     RUN_LED_OFF;DISABLE_MOTOR;
   }   
   else old_key_code=key_code;
   break;   
  }
  char str2[16];
   itoa(mode, str2, 10);
			//itoa();
  Lcd4_Init();
  Lcd4_Set_Cursor(1,1);
  sprintf(str2, "mode:%03d ", mode);
  Lcd4_Write_String(str2) ;
  _delay_ms(10);
  	
		if((TCounter>=TCRtemp) &&  mode!=FAULT_MODE && mode!=STOP_MODE)//&& !bit_is_set(PORTD, 1))									//100mS //loop until fault is coming from portd.1 
		{
			TCRtemp = TCounter +100;						//1mS x100
			
			FRQtemp = a2dConvert10bit(FRQ_ACH);
			ACCtemp = a2dConvert8bit(ACC_ACH);
			DECtemp = a2dConvert8bit(DEC_ACH);
			
			//-------------------------------
			FRQtemp = SetFrequency(FRQtemp);
			ACCtemp = SetAcceleration(ACCtemp);
			DECtemp = SetDeceleration(DECtemp);
	
			//-------------------------------
			
			float a;
			char str[16];

			a = (FRQtemp/10); // or some other calculation
			itoa(a, str, 10);
			//itoa();
			Lcd4_Init();
			/*
			Lcd4_Set_Cursor(1,1);
			Lcd4_Write_String("FQ: ") ;
			
			Lcd4_Set_Cursor(1,5);
			Lcd4_Write_String(str) ;   
			*/
			
			sprintf(Ctemp, "FRQ:%03d.%01dHz ", (FRQtemp/10), (FRQtemp%10));
			Lcd4_Set_Cursor(1,1);
			Lcd4_Write_String(Ctemp) ;
			
			//StringAt(1, 2, Ctemp);
			
			sprintf(Ctemp,"%03dS ", ACCtemp);
			Lcd4_Set_Cursor(1,13);
			Lcd4_Write_String("ACC:");
			Lcd4_Set_Cursor(2,1);
			Lcd4_Write_String(Ctemp) ;
			
			//StringAt(3, 2, Ctemp);
	
			sprintf(Ctemp, "DEC:%03dS ", DECtemp);
			Lcd4_Set_Cursor(2,6);
			Lcd4_Write_String(Ctemp) ;
			//StringAt(5, 2, Ctemp);
			
			i++;
			if(i==5)					{						LVflag = 1;		}
			else if(i==10)		{	i = 0;		LVflag = 0;	}
		}
		else if( mode==FAULT_MODE)
		{
		 Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("Fault accrued !!") ;	
		FRQtemp = SetFrequency(0);
			ACCtemp = SetAcceleration(1);
			DECtemp = SetDeceleration(1);
			RUN_LED_OFF;DISABLE_MOTOR;
		}
		else if( mode==STOP_MODE)
		{
		 Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("STOP_MODE accrued !!") ;	
		FRQtemp = SetFrequency(0);
			ACCtemp = SetAcceleration(1);
			DECtemp = SetDeceleration(1);
			RUN_LED_OFF;DISABLE_MOTOR;
		}
		
		GLED(LVflag);
		//_delay_ms(200);
	}//while
} //test01


//---------------------------------------------------------//
//---------------------------------------------------------//
void LCD_0(void)
{
	/*
' Lcd module connections
dim LCD_RS as sbit at PORTc2_bit
dim LCD_EN as sbit at PORTc3_bit
dim LCD_D4 as sbit at PORTc4_bit
dim LCD_D5 as sbit at PORTc5_bit
dim LCD_D6 as sbit at PORTc6_bit
dim LCD_D7 as sbit at PORTc7_bit

dim LCD_RS_Direction as sbit at DDc2_bit
dim LCD_EN_Direction as sbit at DDc3_bit
dim LCD_D4_Direction as sbit at DDc4_bit
dim LCD_D5_Direction as sbit at DDc5_bit
dim LCD_D6_Direction as sbit at DDc6_bit
dim LCD_D7_Direction as sbit at DDc7_bit

*/

//DDRD = 0xFF;
DDRC = 0xFF;
int i;
Lcd4_Init();
Lcd4_Set_Cursor(1,1);
Lcd4_Write_String("Elasa.ir Test");  
	
}	


//SIGNAL(SIG_INTERRUPT4) {
	ISR(INT4_vect){

// this function is called when INT0 bit (PD2) is interrupted.

// You can also use INTERRUPT() function instead.

// SIG_INTERRUPT0 -> INT0 (PD2)

// SIG_INTERRUPT1 -> INT1 (PD3)

// While Button is pressed, LED is on

Lcd4_Init();
Lcd4_Set_Cursor(1,1);
Lcd4_Write_String("RUN_MODE");  
_delay_ms(200);

mode=RUN_MODE;
/*
PORTB |= (1<<PB0);     // Put PortB bit 5 HIGH

_delay_ms(10);

PORTB &= ~(1<<PB0);     // Put PortB bit 5 LOW

_delay_ms(10);
*/

}

SIGNAL(SIG_INTERRUPT5) {
	//ISR(INT4_vect){

// this function is called when INT0 bit (PD2) is interrupted.

// You can also use INTERRUPT() function instead.

// SIG_INTERRUPT0 -> INT0 (PD2)

// SIG_INTERRUPT1 -> INT1 (PD3)

// While Button is pressed, LED is on

Lcd4_Init();
Lcd4_Set_Cursor(1,1);
Lcd4_Write_String("Stop on");  
_delay_ms(200);
mode=STOP_MODE;
RUN_LED_OFF;
DISABLE_MOTOR;
//RUN_LED_OFF;

}

SIGNAL(SIG_INTERRUPT6) {
	//ISR(INT4_vect){

// this function is called when INT0 bit (PD2) is interrupted.

// You can also use INTERRUPT() function instead.

// SIG_INTERRUPT0 -> INT0 (PD2)

// SIG_INTERRUPT1 -> INT1 (PD3)

// While Button is pressed, LED is on
key_code=DIR_CODE;
Lcd4_Init();
Lcd4_Set_Cursor(1,1);
Lcd4_Write_String("DIR_CODE");  
_delay_ms(200);
 /*
 DIR_LED1_OFF;
      DIR_LED2_ON;
_delay_ms(200);
DIR_LED1_ON;
      DIR_LED2_OFF;
*/	  
flags.dir_change_f=1;
if(flags.dir_f)
    {     
		Lcd4_Set_Cursor(1,1);
Lcd4_Write_String("DIR_1    ");_delay_ms(200);
     DIR_LED1_ON;
     DIR_LED2_OFF;     
    }
    else
    {     
		Lcd4_Set_Cursor(1,1);
Lcd4_Write_String("DIR_0    ");_delay_ms(200);
     DIR_LED1_OFF;
     DIR_LED2_ON;
    }
}