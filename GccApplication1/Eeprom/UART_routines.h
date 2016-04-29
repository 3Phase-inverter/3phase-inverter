// **************************************************************
// ***  UART_ROUTINES HEADER FILE ******** 		
// **************************************************************

#define TX_NEWLINE		{transmitByte(0x0d); transmitByte(0x0a);}

void uart0_init(void);
unsigned char receiveByte(void);
void transmitByte(unsigned char);
void transmitString_F(char*);
void transmitString(char*);
