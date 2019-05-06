#include "peripherals.h"
#include <xc.h>
#define LOW 0
#define HIGH 1

void init_PWM()
     {
     //_FPOR(RST_PWMPIN & PWMxH_ACT_HI & PWMxL_ACT_HI) //think pragma in main cover all this 
    //see example 14-1
    int a = LOW;
    int b = HIGH;
   
    //while(1){
       P1TCONbits.PTMOD = 0b00; //just added
       P1TCONbits.PTCKPS = 0b00; //just added
       P1TCONbits.PTOPS = 0b00; //just added
         
         PTPER = 1944;  //PTPER = ((1/400kHz)/1.04ns) = 2404, where 400kHz is desired switching frequency
                        
        //PMOD values may need to be changed from 1 to 0. 
         
         /*PWM 1 Configuration*/
         PWM1CON1bits.PEN1H = a; //changed from0 to 1
         
         PWM1CON1bits.PEN1L = b;
         PWM1CON1bits.PMOD1 = HIGH; //maybe try switching to 0 or 0b00 when testing later
         
      
         /*PWM2 Configuration*/
         PWM1CON1bits.PEN2H = a; //changed from 0 to 1
         
         PWM1CON1bits.PEN2L = b;
         PWM1CON1bits.PMOD2 = HIGH;
        
         
         
         PTCONbits.PTEN = 1;
         PWM1CON2bits.IUE = 1; //just added see 14-2 ex}
         
      
         }
         
    
   
void delay(int d) //delay for LED light
{
    int i;
    
    while(d)
    {
        i = 50; //100 to 300
        while(i)
        {
            i--;
        }
        d--;
    }

}

