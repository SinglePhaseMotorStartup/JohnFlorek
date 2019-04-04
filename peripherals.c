#include "peripherals.h"
#include <xc.h>

void init_PWM(void)
     {
     //_FPOR(RST_PWMPIN & PWMxH_ACT_HI & PWMxL_ACT_HI) //think pragma in main cover all this 
   
    //see example 14-1
       P1TCONbits.PTMOD = 0b00; //just added
       P1TCONbits.PTCKPS = 0b00; //just added
       P1TCONbits.PTOPS = 0b00; //just added
         
         PTPER = 2404;  //PTPER = ((1/400kHz)/1.04ns) = 2404, where 400kHz is desired switching frequency
       
        //PMOD values may need to be changed from 1 to 0. 
                 
         /*PWM 1 Configuration*/
         PWM1CON1bits.PEN1H = 1; //changed from0 to 1
         PWM1CON1bits.PEN1L = 1;
         PWM1CON1bits.PMOD1 = 1; //maybe try switching to 0 or 0b00 when testing later
         
         PDC1 = 640;     //initial duty cycle 640 og value
         //DTR1 = 64;      //Deadtime in example but not this one  
         //ALTDTR1 = 64;   //deadtime setting in example but not this one  
         
         //PHASE1 = 0;      //no phase shift
         
         /*PWM2 Configuration*/
         PWM1CON1bits.PEN2H = 1; //changed from 0 to 1
         PWM1CON1bits.PEN2L = 1;
         PWM1CON1bits.PMOD2 = 1;
         
         PDC2 = 640;
         //check DT commands
         // DTR2 = 64;
         //ALTDTR2 = 64;
         //PHASE2 = 240;
         PTCONbits.PTEN = 1;
         PWM1CON2bits.IUE = 1; //just added see 14-2 ex
   }
   
void delay(int d) //delay for LED light
{
    int i;
    
    while(d)
    {
        i = 100;
        while(i)
        {
            i--;
        }
        d--;
    }

}
