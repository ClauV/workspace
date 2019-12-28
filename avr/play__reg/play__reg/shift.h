/*
 * shift.h
 *
 * Created: 12/28/2019 13:23:11
 *  Author: Clau
 */ 


#ifndef SHIFT_H_
#define SHIFT_H_

#define HC595_PORT   PORTC
#define HC595_DDR    DDRC
#define HC595_DS_POS PC0      //Data pin (DS) pin location
#define HC595_SH_CP_POS PC1      //Shift Clock (SH_CP) pin location
#define HC595_ST_CP_POS PC2      //Store Clock (ST_CP) pin location

typedef struct {
	uint8_t DDR;
	uint8_t PORT;
	uint8_t DS;
	uint8_t ST_CP;
	uint8_t SH_CP;
	uint8_t MR;
	uint8_t OE;
	} shiftReg;
	
void shiftInit(shiftReg *handler, uint8_t DDR,uint8_t PORT,uint8_t DS,uint8_t ST_CP,uint8_t SH_CP,uint8_t MR,uint8_t OE)
{
	handler->DDR = DDR;
	handler->DS = DS;
	handler->PORT = PORT;
	handler->SH_CP = SH_CP;
	handler->ST_CP = ST_CP;
	handler->MR = MR;
	handler->OE = OE;
	
	handler->DDR = ((1<<handler->SH_CP)|(1<<handler->ST_CP)|(1<<handler->DS));
   //Make the Data(DS), Shift clock (SH_CP), Store Clock (ST_CP) lines output
   HC595_DDR|=((1<<HC595_SH_CP_POS)|(1<<HC595_ST_CP_POS)|(1<<HC595_DS_POS));
}
// change data (DS)lines
void HC595DataHigh(shiftReg *handler) {
	handler->PORT |= (1<<handler->DS);
}

void HC595DataLow(shiftReg *handler){
	handler->PORT &= ~(1<<handler->DS);
} 
//Sends a clock pulse on SH_CP line
void shiftPulse(shiftReg *handler)
{
   //Pulse the Shift Clock
   
   handler->PORT|=(1<<handler->SH_CP);//HIGH
   handler->PORT &=(~(1<<handler->SH_CP));//LOW
}
//Sends a clock pulse on ST_CP line
void shiftLatch(shiftReg *handler)
{
   //Pulse the Store Clock
   HC595_PORT|=(1<<handler->ST_CP);//HIGH
   _delay_loop_1(1);
   HC595_PORT &=(~(1<<handler->ST_CP));//LOW
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
void shiftWrite(shiftReg *handler, uint8_t data)
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
         HC595DataHigh(handler);
      }
      else
      {
         //MSB is 0 so output high
         HC595DataLow(handler);
      }
      shiftPulse(handler);  //Pulse the Clock line
      data=data<<1;  //Now bring next bit at MSB position
   }
   //Now all 8 bits have been transferred to shift register
   //Move them to output latch at one
   shiftLatch(handler);
}
/*
Simple Delay function approx 0.5 seconds
*/
void Wait()
{
   for(uint8_t i=0;i<10;i++)
   {
      _delay_loop_2(0);
   }
}


void clear(shiftReg *handler){
	handler->PORT |= (1 << handler->MR);
}

void unClear(shiftReg *handler){
	handler->PORT &= ~(1 << handler->MR);
}



#endif /* SHIFT_H_ */