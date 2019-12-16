/*
 * shift_lib.c
 *
 * Created: 16/12/2019 17:26:23
 * Author : Clau
 */ #include <avr/io.h>
# define F_CPU 16000000UL
#include <util/delay.h>

#define HC595_PORT   PORTB
#define HC595_DDR    DDRB
#define HC595_DS_POS PB0      //Data pin (DS) pin location
#define HC595_SH_CP_POS PB1     //Shift Clock (SH_CP) pin location
#define HC595_ST_CP_POS PB2      //Store Clock (ST_CP) pin location

typedef struct  
{
	uint8_t PORT;
	uint8_t DDR;
	uint8_t DS;
	uint8_t SH_CP;
	uint8_t ST_CP;
} shiftHandler;

void shiftInit(shiftHandler *hand,uint8_t DDR,uint8_t PORT,uint8_t DS,uint8_t SH_CP,uint8_t ST_CP)
{
	hand->DDR = DDR;
	hand->PORT= PORT;
	hand->DS = DS;
	hand->SH_CP = SH_CP;
	hand->ST_CP = ST_CP;
    hand->DDR = ((1<< hand->SH_CP )|(1<<hand->ST_CP)|(1<<hand->DS));
	HC595_DDR = hand->DDR;
  
}
// change data (DS)lines
void HC595DataHigh(shiftHandler *hand) {
	(hand->PORT|=(1<<hand->DS));
	 HC595_PORT = hand->PORT;
}
void HC595DataLow(shiftHandler *hand) {
	(hand->PORT &=(~(1<<hand->DS)));
	 HC595_PORT = hand->PORT;
}
//Sends a clock pulse on SH_CP line
void shiftPulse(shiftHandler *hand)
{
   //Pulse the Shift Clock
   hand->PORT |=(1<<hand->SH_CP);//HIGH
   HC595_PORT = hand->PORT;
   hand->PORT &=(~(1<<hand->SH_CP));//LOW
   HC595_PORT = hand->PORT;
}
//Sends a clock pulse on ST_CP line
void shiftLatch(shiftHandler *hand)
{
   //Pulse the Store Clock
   hand->PORT|=(1<<hand->ST_CP);//HIGH
    HC595_PORT = hand->PORT;
   _delay_loop_1(1);
   hand->PORT&=(~(1<<hand->ST_CP));//LOW
    HC595_PORT = hand->PORT;
   _delay_loop_1(1);
}
/*
Main High level function to write a single byte to
Output shift register 74HC595.
Arguments:
   single byte to write to the 74HC595 IC
Returns:
   NONE
Description:
   The byte is serially transfered to 74HC595
   and then latched. The byte is then available on
   output line Q0 to Q7 of the HC595 IC.
*/
void shiftWrite(shiftHandler *hand,uint8_t data)
{
   //Send each 8 bits serially
   //Order is MSB first
   for(uint8_t i=0;i<8;i++)
   {
      //Output the data on DS line according to the
      //Value of MSB
      if(data & 0b10000000)
      {
         //MSB is 1 so output high
         HC595DataHigh(hand);
      }
      else
      {
         //MSB is 0 so output high
         HC595DataLow(hand);
      }
      shiftPulse(hand);  //Pulse the Clock line
      data=data<<1;  //Now bring next bit at MSB position
   }
   //Now all 8 bits have been transferred to shift register
   //Move them to output latch at one
   shiftLatch(hand);
}
/*
Simple Delay function approx 0.5 seconds
*/
void Wait()
{
  /* for(uint8_t i=0;i<5;i++)
   {
      _delay_loop_2(0);
   }
   */
  _delay_ms(100);
}
int main()
{
	
	shiftHandler anode;
	
   uint8_t led[11]={
                        0b00000001,
                        0b00000010,
					    0b00000100,
						0b00001000,
						0b00010000,
					    0b00100000,
						0b01000000,
						0b10011011,
						0b11111110,
                     };
					 
   shiftInit(&anode,DDRB,PORTB,PB0,PB2,PB1); //Initialise
   
   while(1)
   {
      for(uint8_t i=0;i<10;i++)
      {
         shiftWrite(&anode,led[i]);   //Write the data to shift register
         Wait();                 //Wait
	
      }
   }
   return 0;
}