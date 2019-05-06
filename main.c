/* 
 * File:   main.c
 * Author: ginst
 *
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "peripherals.h"
#include "adcdrv.h"
#include <p33FJ128MC802.h>

#define EXIT_SUCCESS 0 //added for delay funct
// FBS
#pragma config BWRP = WRPROTECT_OFF     // Boot Segment Write Protect (Boot Segment may be written)
#pragma config BSS = NO_FLASH           // Boot Segment Program Flash Code Protection (No Boot program Flash segment)
#pragma config RBS = NO_RAM             // Boot Segment RAM Protection (No Boot RAM)

// FSS
#pragma config SWRP = WRPROTECT_OFF     // Secure Segment Program Write Protect (Secure segment may be written)
#pragma config SSS = NO_FLASH           // Secure Segment Program Flash Code Protection (No Secure Segment)
#pragma config RSS = NO_RAM             // Secure Segment Data RAM Protection (No Secure RAM)

// FGS
#pragma config GWRP = OFF               // General Code Segment Write Protect (User program memory is not write-protected)
#pragma config GSS = OFF                // General Segment Code Protection (User program memory is not code-protected)

// FOSCSEL
#pragma config FNOSC = FRCPLL          // Oscillator Mode (Internal Fast RC (FRC) w/ PLL)
#pragma config IESO = ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// FOSC
#pragma config POSCMD = HS              // Primary Oscillator Source (HS Oscillator Mode)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function (OSC2 pin has digital I/O function)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow Only One Re-configuration)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Both Clock Switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (1:128)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF              // Watchdog Timer Enable (Watchdog timer always enabled)

// FPOR
#pragma config FPWRT = PWR128           // POR Timer Value (128ms)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = ON                // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

// FICD
#pragma config ICS = PGD1               // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG is Disabled)
int sineTable2[301] = {
0,
41,
81,
122,
162,
203,
243,
284,
324,
365,
405,
445,
486,
526,
566,
606,
646,
686,
726,
766,
806,
845,
885,
924,
964,
1003,
1042,
1081,
1120,
1159,
1198,
1236,
1275,
1313,
1351,
1389,
1427,
1464,
1502,
1539,
1576,
1613,
1650,
1687,
1723,
1760,
1796,
1832,
1867,
1903,
1938,
1973,
2008,
2043,
2077,
2111,
2145,
2179,
2212,
2246,
2279,
2311,
2344,
2376,
2408,
2440,
2471,
2503,
2534,
2564,
2595,
2625,
2654,
2684,
2713,
2742,
2771,
2799,
2827,
2855,
2882,
2909,
2936,
2962,
2989,
3014,
3040,
3065,
3090,
3114,
3138,
3162,
3186,
3209,
3231,
3254,
3276,
3297,
3319,
3340,
3360,
3381,
3400,
3420,
3439,
3458,
3476,
3494,
3512,
3529,
3546,
3562,
3578,
3594,
3609,
3624,
3639,
3653,
3666,
3680,
3693,
3705,
3717,
3729,
3740,
3751,
3762,
3772,
3781,
3791,
3799,
3808,
3816,
3823,
3830,
3837,
3844,
3849,
3855,
3860,
3865,
3869,
3873,
3876,
3879,
3882,
3884,
3885,
3887,
3888,
3888,
3888,
3888,
3887,
3885,
3884,
3882,
3879,
3876,
3873,
3869,
3865,
3860,
3855,
3849,
3844,
3837,
3830,
3823,
3816,
3808,
3799,
3791,
3781,
3772,
3762,
3751,
3740,
3729,
3717,
3705,
3693,
3680,
3666,
3653,
3639,
3624,
3609,
3594,
3578,
3562,
3546,
3529,
3512,
3494,
3476,
3458,
3439,
3420,
3400,
3381,
3360,
3340,
3319,
3297,
3276,
3254,
3231,
3209,
3186,
3162,
3138,
3114,
3090,
3065,
3040,
3014,
2989,
2962,
2936,
2909,
2882,
2855,
2827,
2799,
2771,
2742,
2713,
2684,
2654,
2625,
2595,
2564,
2534,
2503,
2471,
2440,
2408,
2376,
2344,
2311,
2279,
2246,
2212,
2179,
2145,
2111,
2077,
2043,
2008,
1973,
1938,
1903,
1867,
1832,
1796,
1760,
1723,
1687,
1650,
1613,
1576,
1539,
1502,
1464,
1427,
1389,
1351,
1313,
1275,
1236,
1198,
1159,
1120,
1081,
1042,
1003,
964,
924,
885,
845,
806,
766,
726,
686,
646,
606,
566,
526,
486,
445,
405,
365,
324,
284,
243,
203,
162,
122,
81,
41,
};

int global_ctr = 0;
int global_delay_val = 3; //variables for led signal, 300 to 100

int n = 0;
int m = 0;

int main(){
    /*Configure Oscillator to operate the device at Fdev
     Fosc = Fin*M/(N1/N2), Fcy=Fosc/2
     * 
     */
    //configure PLL prescaler, PLL postscaler, PLL divisor
    
     PLLFBD = 32;                      //M = 32
     
     CLKDIVbits.PLLPOST= 0;           //N2= 2
     CLKDIVbits.PLLPRE= 0;            //N1= 2
     

    //Initiate Clock Switch to Primary Oscillator with PLL
    __builtin_write_OSCCONH(0x01);      //New Oscillator w/PLL
    __builtin_write_OSCCONL(0x01);      //Enable Switch
    
    
    //Wait for Clock Switch to occur
     while (OSCCONbits.COSC!= 0b001);   //Wait for new Oscillator to become FRC w/ PLL
     while (OSCCONbits.LOCK!=1);         //Wait for PLL to Lock
     

     
     ACLKCONbits.SELACLK = 1;           //Auxiliary Oscillator provides clock source for PWM and ADC
     ACLKCONbits.APSTSCLR = 7;          //Divide Auxiliary Clock by 1
     
     
     TRISAbits.TRISA4 = 0;              //set as digital output
     TRISBbits.TRISB13 = 0;           //added but hasn't been checked yet 
    
     LATAbits.LATA4 = 1;                
     LATBbits.LATB13 = 1;             //added but hasn't been checked yet
     
     //initadc1();   //ad converter 
    
     init_PWM();
     select_adc_ads8344 (1, 1);
     get_adc_channel_ads8344(1);
     start_read_ads8344 (1);
     read_channel_ads8344 (1);
             
     LATA = 0;  //for led switching
     TRISA = 0;
    
    int cnt = 0;
    int a = 0;
    int b = 1;
    while (1) {
         //loop to run LED
   
   
   delay(global_delay_val);
    LATA = 0x0001;
    PDC1 = sineTable2[cnt];
    PDC2 = (sineTable2[cnt]) / 2; //added division by 2
    
   // PWM1CON1bits.PEN1H = 0; 
    //PWM1CON1bits.PEN1L = 1;
    //PWM1CON1bits.PEN2H = 0; 
    //PWM1CON1bits.PEN2L = 1;
    
    if (cnt < 301){
        
        cnt = cnt + 1;}
    else{
        cnt = 0;
        
    }
    
    delay(100);
    PWM1CON1bits.PEN1H = a; 
    PWM1CON1bits.PEN1L = b;
    PWM1CON1bits.PEN2H = a; 
    PWM1CON1bits.PEN2L = b;
    
    if (a == 0)
        a = 1;
    else
        a = 0;
    if (b == 1)
        b = 0;
    else
        b = 1;
    
    LATA = 0x0000;   

    global_ctr++;
}
return(EXIT_SUCCESS);
   
     
     }
    
        

  