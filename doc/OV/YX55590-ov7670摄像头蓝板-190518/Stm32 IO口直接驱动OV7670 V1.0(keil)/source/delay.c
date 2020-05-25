
#include "delay.h"

void delay_us(unsigned int i)
 {     
    while( i--)
       {	
        
        }
 }		  

//    ∫¡√Îº∂—” ±∫Ø ˝	 
void delay_ms(unsigned int time)
	 {
	  while(time--)
	  	  {	
		   delay_us(1000);
		  }
	 }

 __asm void wait()
{
	nop
	nop
	nop
	nop
	nop
    BX lr
}
void delay()
{
	wait(); 
}