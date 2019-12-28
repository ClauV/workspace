
# define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "shift.h"

shiftReg anode;

int main()
{
	//(shiftReg handler, uint8_t DDR,uint8_t PORT,uint8_t DS,uint8_t ST_CP,uint8_t SH_CP,uint8_t MR,uint8_t OE)
   shiftInit(&anode,DDRC,PORTC,PC0,PC2,PC1,PC3,0); //Initialise
   uint8_t i=0;
  // clear(&anode);
    shiftWrite(&anode,  0x33);   //Write the data to shift register
    shiftWrite(&anode,  0x0F);   //Write the data to shift register
    shiftWrite(&anode,  0xFF);   //Write the data to shift register
   
	//unClear(&anode);
	 
	 _delay_ms(1000000);
	 
   while(1)
   {
     
         shiftWrite(&anode,  i/*0b01010101*/);   //Write the data to shift register
		
		 Wait(); 
		 if (i==128) 
		 i = 0;
         
		 i++;                //Wait
      
   }
   return 1;
}