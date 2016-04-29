// **************************************************************
// ******* 24C256 EEPROM_ROUTINES HEADER FILE ******** 		
// **************************************************************

unsigned char EEPROM_read( unsigned char, unsigned char, unsigned char );
unsigned char EEPROM_write( unsigned char, unsigned char ,unsigned char );
unsigned char EEPROM_writePage( unsigned int,unsigned char );
unsigned char EEPROM_readPage( unsigned int );
unsigned char EEPROM_erase( void );